#import "ImGuiDrawViewX.h"
#include "../Menu/Menu.h"
#include "Fonts.hpp"
#include "MenuUtils.h"
#include "SmilySansFont.h"
#include "imgui.h"

@interface ImGuiDrawViewX () <MTKViewDelegate, UITextFieldDelegate>
@property(nonatomic, strong) id<MTLDevice> device;
@property(nonatomic, strong) id<MTLCommandQueue> commandQueue;

@end

@implementation ImGuiDrawViewX

static BOOL menuVisible = YES;
extern MenuInteraction *menuTouchView;

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil
                         bundle:(nullable NSBundle *)nibBundleOrNil {
  self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];

  if (self) {
    _device = MTLCreateSystemDefaultDevice();
    _commandQueue = [_device newCommandQueue];

    if (!_device) {
      abort();
    }

    [self setupImGuiContext];
  }

  return self;
}

- (void)setupImGuiContext {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGuiIO &io = ImGui::GetIO();
  io.KeyMap[ImGuiKey_Backspace] = 8;

  [self addFontsToImGui:io];
  ImGui_ImplMetal_Init(_device);
}

- (void)addFontsToImGui:(ImGuiIO &)io {
  io.Fonts->Clear();

  ImFontConfig SmilySansConfig;
  SmilySansConfig.FontDataOwnedByAtlas = NO;
  io.Fonts->AddFontFromMemoryTTF((void *)SmilySans, sizeof(SmilySans), 18,
                                 &SmilySansConfig,
                                 io.Fonts->GetGlyphRangesChineseFull());

  static const ImWchar iconsRanges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
  ImFontConfig iconsConfig;
  iconsConfig.MergeMode = YES;
  iconsConfig.PixelSnapH = YES;
  iconsConfig.FontDataOwnedByAtlas = NO;
  io.Fonts->AddFontFromMemoryTTF((void *)fontAwesome, sizeof(fontAwesome), 18,
                                 &iconsConfig, iconsRanges);
}

+ (void)showChange:(BOOL)open {
  menuVisible = open;
}

+ (BOOL)isMenuShowing {
  return menuVisible;
}

- (MTKView *)mtkView {
  return (MTKView *)self.view;
}

- (void)loadView {
  CGRect frame = [UIScreen mainScreen].nativeBounds;
  MTKView *mtkView = [[MTKView alloc] initWithFrame:frame];
  mtkView.contentScaleFactor = UIScreen.mainScreen.nativeScale;
  self.view = mtkView;
}

- (void)viewDidLoad {
  [super viewDidLoad];

  self.mtkView.device = self.device;
  self.mtkView.delegate = self;
  self.mtkView.clearColor = MTLClearColorMake(0, 0, 0, 0);
  self.mtkView.backgroundColor = [UIColor clearColor];
  self.mtkView.clipsToBounds = YES;
  self.textField =
      [[UITextField alloc] initWithFrame:CGRectMake(50, 100, 300, 40)];
  self.textField.hidden = YES;
  self.textField.borderStyle = UITextBorderStyleRoundedRect;
  self.textField.delegate = self; // 设置代理
  [self.view addSubview:self.textField];
  // Add keyboard notifications
  [[NSNotificationCenter defaultCenter]
      addObserver:self
         selector:@selector(keyboardWillShow:)
             name:UIKeyboardWillShowNotification
           object:nil];
  [[NSNotificationCenter defaultCenter]
      addObserver:self
         selector:@selector(keyboardWillHide:)
             name:UIKeyboardWillHideNotification
           object:nil];
}
- (void)textFieldDidBeginEditing:(UITextField *)textField {
  debug_log(@"Start editing: %@", textField.text);
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
  debug_log(@"End editing: %@", textField.text);
}

- (void)textFieldShouldDelete:(UITextField *)textField {
  debug_log(@"Backspace detected!");
  ImGuiIO &io = ImGui::GetIO();

  io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = true;
  io.KeysDown[8] = true;

  dispatch_after(
      dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.016 * NSEC_PER_SEC)),
      dispatch_get_main_queue(), ^{
        io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = false;
        io.KeysDown[8] = false;
      });
}

- (BOOL)textField:(UITextField *)textField
    shouldChangeCharactersInRange:(NSRange)range
                replacementString:(NSString *)string {
  // 如果按下回车，隐藏键盘

  if ([string isEqualToString:@"\n"]) {
    // 打印键盘输入的内容
    NSString *newText =
        [textField.text stringByReplacingCharactersInRange:range
                                                withString:string];
    if ([newText hasSuffix:@"\n"]) {
      newText = [newText substringToIndex:newText.length - 1];
    }
    debug_log(@"All content: %@", newText);
    // 清空当前输入
    ImGuiIO &io = ImGui::GetIO();
    io.ClearInputCharacters(); // 清空缓存中的字符
    [newText
        enumerateSubstringsInRange:NSMakeRange(0, newText.length)
                           options:
                               NSStringEnumerationByComposedCharacterSequences
                        usingBlock:^(NSString *substring,
                                     NSRange substringRange,
                                     NSRange enclosingRange, BOOL *stop) {
                          // substring 是每个字符
                          NSData *data = [substring
                              dataUsingEncoding:NSUTF8StringEncoding];
                          io.AddInputCharactersUTF8((const char *)[data bytes]);
                        }];

    dispatch_after(
        dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1 * NSEC_PER_SEC)),
        dispatch_get_main_queue(), ^{
          [self.textField resignFirstResponder];
          self.isKeyboardVisible = NO;

          ImGui::SetWindowFocus(NULL);
        });
    return NO;
  }
  return YES; // 返回 YES，允许文本框修改
}

#pragma mark - Interaction

- (void)updateIOWithTouchEvent:(UIEvent *)event {
  UITouch *touch = event.allTouches.anyObject;
  CGPoint touchLocation = [touch locationInView:self.view];

  ImGuiIO &io = ImGui::GetIO();
  io.MousePos = ImVec2(touchLocation.x, touchLocation.y);
  io.MouseDown[0] = (touch.phase != UITouchPhaseEnded &&
                     touch.phase != UITouchPhaseCancelled);

  if (touch.phase == UITouchPhaseBegan && self.isKeyboardVisible) {
    if (!io.WantTextInput) {
      [self resignFirstResponder];
      self.isKeyboardVisible = NO;
    }
  }

  if (io.WantTextInput && !self.isKeyboardVisible) {
    [self.textField becomeFirstResponder];
  }
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
  [self updateIOWithTouchEvent:event];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
  [self updateIOWithTouchEvent:event];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches
               withEvent:(UIEvent *)event {
  [self updateIOWithTouchEvent:event];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
  [self updateIOWithTouchEvent:event];
}

- (void)drawInMTKView:(MTKView *)view {
  ImGuiIO &io = ImGui::GetIO();

  static bool inited = false;
  CGSize screenSize = [UIScreen mainScreen].nativeBounds.size;
  CGFloat screenScale =
      view.window.screen.nativeScale ?: UIScreen.mainScreen.nativeScale;
  debug_log(@"Screen Size %f %f, Scale: %f", screenSize.width,
            screenSize.height, screenScale);
  if (!inited) {
    inited = true;
    hideRecordTextfield.secureTextEntry = StreamerMode;
    Config::screenScale = screenScale;
    io.DisplaySize = ImVec2(screenSize.width, screenSize.height);
    io.DisplayFramebufferScale = ImVec2(screenScale, screenScale);
    io.DeltaTime = 1.0f / (float)(view.preferredFramesPerSecond ?: 60);
  }

  id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];

  [self updateUserInteractionEnabled];

  MTLRenderPassDescriptor *renderPassDescriptor =
      view.currentRenderPassDescriptor;
  if (renderPassDescriptor) {
    id<MTLRenderCommandEncoder> renderEncoder =
        [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    [renderEncoder pushDebugGroup:@"iOSImGui"];

    ImGui_ImplMetal_NewFrame(renderPassDescriptor);
    ImGui::NewFrame();
    SetStyles();
    // SetRigelStyle();
    if (menuVisible || !Config::加载一次参数) {

      ImGui::Begin(
          WATERMARK, NULL,
          ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
              ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
      MenuOrigin = ImGui::GetWindowPos();
      MenuSize = ImGui::GetWindowSize();
      LoadMenu();
      ImGui::End();
      // ImGui::ShowDemoWindow();
    }
    ESP();
    ImGui::EndFrame();
    ImGui::Render();
    ImDrawData *drawData = ImGui::GetDrawData();
    // drawData->DisplaySize = ImVec2(screenSize.width * screenScale,
    // screenSize.//height*screenScale);
    drawData->FramebufferScale = ImVec2(screenScale, screenScale);
    ImGui_ImplMetal_RenderDrawData(drawData, commandBuffer, renderEncoder);

    [renderEncoder popDebugGroup];
    [renderEncoder endEncoding];
    [commandBuffer presentDrawable:view.currentDrawable];
  }

  [commandBuffer commit];
}

- (void)updateUserInteractionEnabled {
  BOOL isEnabled = menuVisible;
  [self.view setUserInteractionEnabled:isEnabled];
  [self.view.superview setUserInteractionEnabled:isEnabled];
  [menuTouchView setUserInteractionEnabled:isEnabled];
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size {
}

- (BOOL)hasText {
  return YES;
}

- (void)insertText:(NSString *)text {
  if ([text isEqualToString:@"\n"]) {
    [self resignFirstResponder];
    self.isKeyboardVisible = NO;

    ImGui::SetWindowFocus(NULL);
    return;
  }

  ImGuiIO &io = ImGui::GetIO();
  NSData *data = [text dataUsingEncoding:NSUTF8StringEncoding];
  io.AddInputCharactersUTF8((const char *)[data bytes]);
}

- (void)deleteBackward {
  ImGuiIO &io = ImGui::GetIO();

  io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = true;
  io.KeysDown[8] = true;

  dispatch_after(
      dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.016 * NSEC_PER_SEC)),
      dispatch_get_main_queue(), ^{
        io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = false;
        io.KeysDown[8] = false;
      });
}

- (BOOL)canBecomeFirstResponder {
  return YES;
}

- (void)keyboardWillShow:(NSNotification *)notification {
  self.textField.hidden = NO;
  self.isKeyboardVisible = YES;
}

- (void)keyboardWillHide:(NSNotification *)notification {
  self.textField.hidden = YES;
  self.isKeyboardVisible = NO;
}

/*

- (BOOL)textField:(UITextField *)textField
shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString
*)string { if ([string isEqualToString:@"\n"]) { [self resignFirstResponder];
        self.isKeyboardVisible = NO;
        return NO;
    }
    return YES;
}
*/
- (void)dealloc {
  [[NSNotificationCenter defaultCenter] removeObserver:self];
}
@end
