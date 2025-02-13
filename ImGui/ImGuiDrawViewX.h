#import <UIKit/UIKit.h>
#import <MetalKit/MetalKit.h>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../ImGui/imgui_impl_metal.h"
#include "../Config/Config.h"

@interface ImGuiDrawViewX : UIViewController <MTKViewDelegate, UITextFieldDelegate>

+ (void)showChange:(BOOL)open;
+ (BOOL)isMenuShowing;
- (void)updateIOWithTouchEvent:(UIEvent *)event;
@property (nonatomic, strong) UITextField *textField;
@property (nonatomic, assign) BOOL isKeyboardVisible;

@end
