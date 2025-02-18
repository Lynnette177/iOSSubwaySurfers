#include "Menu.h"
#include "SubMenu.h"
#import <AdSupport/AdSupport.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <map>
#include <string>
#include <vector>

#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^

// Color Scheme
int ChildColor[4] = {22, 21, 26, 255};
int BGColor[4] = {17, 17, 19, 255};
int IconChildColor[4] = {25, 26, 31, 255};
int InactiveTextColor[4] = {84, 82, 89, 255};
int ActiveTextColor[4] = {255, 106, 106};
int GrabColor[4] = {72, 71, 78, 255};

// Tab Vars
static int PageNumber = 0;
static bool sidebarTab0 = true, sidebarTab1 = false, sidebarTab2 = false,
            sidebarTab3 = false, sidebarTab4 = false;

// Child Tabs
std::map<std::string, bool> childVisibilityMap;

static int deepFadeAnimation = 255;
static bool animationEx = false;
static float animationButton = 25;
static float position = 25;
int animation_text = 255;
int speed = 10;

// Content Slide
static float columnOffset = 60.0f;
static float targetOffset = 60.0f;
float animationSpeed = 130.0f;
bool newChildVisible;
bool ToggleAnimations = false;

// Menu Icon
NSString *baseimage =
    @"iVBORw0KGgoAAAANSUhEUgAAADIAAAAyCAYAAAAeP4ixAAAAAXNSR0IArs4c6QAAAIRlWElmT"
    @"U0AKgAAAAgABQESAAMAAAABAAEAAAEaAAUAAAABAAAASgEbAAUAAAABAAAAUgEoAAMAAAABAA"
    @"IAAIdpAAQAAAABAAAAWgAAAAAAAABIAAAAAQAAAEgAAAABAAOgAQADAAAAAQABAACgAgAEAAA"
    @"AAQAAADKgAwAEAAAAAQAAADIAAAAAhvHCqAAAAAlwSFlzAAALEwAACxMBAJqcGAAAAVlpVFh0"
    @"WE1MOmNvbS5hZG9iZS54bXAAAAAAADx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0Y"
    @"S8iIHg6eG1wdGs9IlhNUCBDb3JlIDYuMC4wIj4KICAgPHJkZjpSREYgeG1sbnM6cmRmPSJodH"
    @"RwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4KICAgICAgPHJkZjp"
    @"EZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIKICAgICAgICAgICAgeG1sbnM6dGlmZj0iaHR0cDov"
    @"L25zLmFkb2JlLmNvbS90aWZmLzEuMC8iPgogICAgICAgICA8dGlmZjpPcmllbnRhdGlvbj4xP"
    @"C90aWZmOk9yaWVudGF0aW9uPgogICAgICA8L3JkZjpEZXNjcmlwdGlvbj4KICAgPC9yZGY6Uk"
    @"RGPgo8L3g6eG1wbWV0YT4KGV7hBwAACNJJREFUaAXtWGtMHNcVPndm9sXuLAvs8jLhETDeGJv"
    @"awUFNDYnTxnGkyKoUY6xWlSK5Stuo6g+nitTmR4XUyv2T5Gdl+qeV0x+"
    @"tY9dWFKup3VgYW00jJy6OA5iHiTEOCwsYWPa9M3N7zuzOhuJ98LDatOLCzL1z7j2P75xzXwuw"
    @"WTY9sOmBTQ9seuC/"
    @"4AG2AZ25eHkeuRvhzSP6f7w7l2dyQjt69Kg8Pj5ujsVimjFQVVVmsVjiPT09QYOWqT58+"
    @"LAjEAiYQ6GQHjlJkjjKEVbDm0neemkiMe7cvv0PhQVWtVh2TLscBXMue8G03Swp2xoa3k4J1s"
    @"etUKLTGnGM02pRiQef+/hM2U2S0lhffzI1XlrB9/A/T506lTTQU/"
    @"FnlE4epYh8WVdWER045w9Eu4tzgfqgNM1LfGleubb+HHV3dXUlx9HHKstakItoCO9+"
    @"fPcZKCx97OpzO9x1zj0QUzVNYIxhFzeLgjgWiDzdfj4+9PTOHf0I+nBnZ6duCrbhN7ubT0Nx+"
    @"farzza56wr3QFzVVGRlGvJadN7oU+"
    @"1zi7d6z54eRF2HurAPmdXVYFkLEBUFA8huLyzNNtpFzisdVh5WVFFEOhoDNpPE/"
    @"aFIESz4i3sTmtbb2Zk2QgdkK/"
    @"FCZK7RIe5AXhuPIC86AVTkLTCJgLwulF10yW8TLiG+1QAwxjwQfqMjVVOI+Qttba5YPNa9FI/"
    @"Z32wq+zqCKKpwuTSHxSySEQz/uJYAUVNhKa6oU8GwEFTZwk/7JnvtFkSHKAnucW/"
    @"xN2SJucrsNk02S1/yYnaRMwJxRUMwsKSywGv9sx9aNWURmPBKT1/"
    @"fItpBtmYFlwsI9VH+GiWODdPED1+AKpfMg/"
    @"7PmRb2AROtGPwoMGcdcIcHBK4BTno+EQiz6hPvGbx6PfEj5HXaeSiu6O5eqZy+"
    @"kRcmFkNQ3X2eeBR8TNRIlZU2GXQdZfpjWYMiob144EDFDd/"
    @"0sW2CKv2kwfV9EZi9ucLNCuKLgvjtV0DcUgMQjQA3W0AbvsnVv73NQC4FhpEJJVTthv++"
    @"IgDlY9KVu0qLREwhAYOYoi7TiE2DTryfTs9rCueRE3dDJwcTEHlUtr/"
    @"11ytXfDhMt+3fOQGyzRFduf/evdLb/QOv1VQ4YO++/"
    @"WCXRIggi7o4A6bmJ8C0pTotL261gXr658CKqgDiEXCYJeGbNeXm5TGNaRoai6moS0+"
    @"zphsG3YFgv1VXLgQTCfmNv/"
    @"f9eMS3BG6v9yQOJCAZubMB0YVziWNoBUXhwMMJRcKZwLiIPhbQvkhYH5MYG+"
    @"La3CzT7owAuLZjMiR0Ok1+5NHbxosWoYxWGANStYYRI95IQkUDGApkHLRoUvCKscYnhSlrQe+"
    @"hXkZgTWQDrTDkTq6heEwnKuqtmxB9uQ3Uy+8whnMEVNSHwHEkp/HLn9WA0IXiwCSf/"
    @"kVzxKy3crxyRiTJt3y+"
    @"IwXTg1kKQb17G2sL8KUFEJ7cj7O0CCCGUcItBTFjPB7cEHPYkbGLplKqA32aW14eIOkFg9CgU"
    @"PxHjzOHGxInfwXx6BwwuYoxmxPnRRIEzQkdxOqyKCMAg4jaUnrJP5heOUoeIHpakgBav2m1Qf"
    @"NIPDZodXKWYw/uebjkppxH5qeV59Cbt4sWBfwnKCScTg/rB5IMJ6c5qu/"
    @"eksAgQTORCgFIH7N0ivFCpBsrJEASBKBtH1WS5wRFVTMdQtOKckbExCUFBOk+"
    @"7np0nChErwsSwiIFSbfndFJayWobSZmYvbjkxVSFdKLbhEUQrVwSbenjTiZ52YDoTILbPQJbE"
    @"7UxxkpeevfD65FYrOiPh/ZpZXYri6s4hNLsYRZEglsIzEUi/"
    @"MiZy4LdYgnELK49Hq991uTxRGFoiLRlBJQNiG4eXpBoI1gKNzdr/"
    @"5gKaXQUQWdR6urpizAeKhKaFbT/qKjgo1m8m0kK92wrn53p7w/"
    @"26BZlf+UzhPrZD1pa8Hg+22CvbmA1wekzUzN+7y/27VYaXLIUw8jQmr+RQsZb8NQwOr+k/"
    @"LKnT/"
    @"K4PYMTcllHfGoKHrFaR377ySfGzkrZl7HkjAhyECNHQbRyDMLIOEBllQCTfnj9KS7hHYLHNW1"
    @"jKFAwrSYkC49Y4p/GpgECSJz9bADfqy45V4IVUkS8uTF5bqpffqTmHbxw11wY/"
    @"rzaXWCLlzusIq1ma40MXQHwMgYDM4F498e3pLtR3jMou7/"
    @"7bHnJ+zuf3HtvYGCATh5Zo7DcvvV7s6TsXZibPnihox3212/h4XiCbnrLZedtE/"
    @"ACi8QvjE6yA6evADhcZyG48GJexgwD1hIRnb2lpcXk8/m0I3tbw7GyiqtbrWZr/"
    @"xe+RzXO9Mjg0TtvZCgStE/cmFmIfTDmk/"
    @"yKcO68pfj493Y0fvTp6NiQoSODvVlJ649ISqRt59fejNy88ervn2+"
    @"Bl3Zt5VGMjGJsmlnU0sZqNZv4764Ps6MXrgPUNvwa7oy+nhpONq0ttMiQ8/"
    @"SbxQ6dTF6jxkGn4wOoqT8eMcsXL2KKfDazGCN6pjQzaDf9i/"
    @"GLtydZ1Oz4CwjyzzoqS3qIpyV5G1wzCOJdc2oRExVKL6xY/"
    @"8TECCzOX7pTWlvy1vuXn6+0SdJzOGdwh3lgzuA1nX5k4N0fD0ovX/"
    @"wn3C2tPeEfH35jYOKL2yQLb00ZNzvSl6+sOyIpwdyITLMZ7oCj+KzN7uzt888z3BNwIcMTH/"
    @"qXHtpHaZ/"
    @"om55nBQ5nL7jc55pswijJSclYVyTyAVxrf3quPd7WdhCZ+"
    @"XfqPDxyrEOLvtrB6YkcO6QdqS0lY3lTa+"
    @"uBZQrSvMtoa25uNCKGwnRkqgUtBhVbRko9ZYNToag2GQxrvmBE82Hb43EP4K+"
    @"MQ16zoKfQVykSBpB0bfzc+cQzzzThfViPAHZiLfGm9na81K/"
    @"vJ9G0gv9gQ19AttbUPFYiy3NOkzRLj9sp3ydayo51LzLZcOQ7a2Xjy0XX02ZXa+"
    @"vwtWvX6o2Bsiwzr9cbGBkfJ9K6VydD3v9t/VBWjBzeWSn/"
    @"K7HE5rB3s2vTA5se2PTApgfW5oF/AYQTn35224ReAAAAAElFTkSuQmCC";
void SetStyles() {
  ImGuiStyle *style = &ImGui::GetStyle();

  style->WindowBorderSize = 0;
  style->WindowMinSize = ImVec2(400, 260);
  style->FrameRounding = 5.0f;
  style->GrabRounding = 5.0f;
  style->WindowRounding = 5.0f;
  style->PopupRounding = 5.0f;
  style->ChildRounding = 5.0f;
  style->ScrollbarSize = 15;

  style->Colors[ImGuiCol_SeparatorHovered] = ImColor(0, 0, 0, 0);
  style->Colors[ImGuiCol_SeparatorActive] = ImColor(0, 0, 0, 0);
  style->Colors[ImGuiCol_Separator] = ImColor(0, 0, 0, 0);
  style->Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0, 0);
  style->Colors[ImGuiCol_ButtonHovered] = ImColor(0, 0, 0, 0);
  style->Colors[ImGuiCol_Button] = ImColor(0, 0, 0, 0);

  style->Colors[ImGuiCol_WindowBg] =
      ImColor(BGColor[0], BGColor[1], BGColor[2], 255);
  style->Colors[ImGuiCol_FrameBg] =
      ImColor(IconChildColor[0], IconChildColor[1], IconChildColor[2], 255);
  style->Colors[ImGuiCol_FrameBgHovered] =
      ImColor(IconChildColor[0], IconChildColor[1], IconChildColor[2], 255);
  style->Colors[ImGuiCol_FrameBgActive] =
      ImColor(IconChildColor[0], IconChildColor[1], IconChildColor[2], 255);

  style->Colors[ImGuiCol_TitleBg] =
      ImColor(ChildColor[0], ChildColor[1], ChildColor[2], 255);
  style->Colors[ImGuiCol_TitleBgActive] =
      ImColor(ChildColor[0], ChildColor[1], ChildColor[2], 255);
  style->Colors[ImGuiCol_Header] =
      ImColor(ChildColor[0], ChildColor[1], ChildColor[2], 255);
  style->Colors[ImGuiCol_HeaderHovered] =
      ImColor(ChildColor[0], ChildColor[1], ChildColor[2], 255);
  style->Colors[ImGuiCol_HeaderActive] =
      ImColor(ChildColor[0], ChildColor[1], ChildColor[2], 255);
  style->Colors[ImGuiCol_ChildBg] =
      ImColor(ChildColor[0], ChildColor[1], ChildColor[2], 255);

  ImGui::PushStyleColor(ImGuiCol_WindowBg,
                        IM_COL32(BGColor[0], BGColor[1], BGColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_FrameBg,
      IM_COL32(IconChildColor[0], IconChildColor[1], IconChildColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_FrameBgHovered,
      IM_COL32(IconChildColor[0], IconChildColor[1], IconChildColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_FrameBgActive,
      IM_COL32(IconChildColor[0], IconChildColor[1], IconChildColor[2], 255));
  ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(ChildColor[0], ChildColor[1],
                                                  ChildColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_HeaderHovered,
      IM_COL32(ChildColor[0], ChildColor[1], ChildColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_HeaderActive,
      IM_COL32(ChildColor[0], ChildColor[1], ChildColor[2], 255));
  ImGui::PushStyleColor(ImGuiCol_TitleBg, IM_COL32(ChildColor[0], ChildColor[1],
                                                   ChildColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_TitleBgActive,
      IM_COL32(ChildColor[0], ChildColor[1], ChildColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_SliderGrab,
      IM_COL32(GrabColor[0], GrabColor[1], GrabColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_SliderGrabActive,
      IM_COL32(GrabColor[0], GrabColor[1], GrabColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_ScrollbarGrab,
      IM_COL32(GrabColor[0], GrabColor[1], GrabColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_ScrollbarBg,
      IM_COL32(ChildColor[0], ChildColor[1], ChildColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_ScrollbarGrabActive,
      IM_COL32(GrabColor[0], GrabColor[1], GrabColor[2], 255));
  ImGui::PushStyleColor(
      ImGuiCol_ScrollbarGrabHovered,
      IM_COL32(GrabColor[0], GrabColor[1], GrabColor[2], 255));
}
void LoadMenu() {
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    Console::addLog("Welcome to Rigel iOS");
  });

  ImVec2 P1, P2;
  ImDrawList *pDrawList;
  const auto &CurrentWindowPos = ImGui::GetWindowPos();
  const auto &pWindowDrawList = ImGui::GetWindowDrawList();
  ImDrawList *menuDrawList = ImGui::GetWindowDrawList();

  if (ToggleAnimations) {
    targetOffset = 0.0f;
  } else {
    targetOffset = 60.0f;
  }

  if (columnOffset != targetOffset) {
    float deltaTime = ImGui::GetIO().DeltaTime;
    if (columnOffset < targetOffset) {
      columnOffset += animationSpeed * deltaTime;
      if (columnOffset > targetOffset)
        columnOffset = targetOffset;
    } else {
      columnOffset -= animationSpeed * deltaTime;
      if (columnOffset < targetOffset)
        columnOffset = targetOffset;
    }
  }
  ImGui::Columns(2);
  ImGui::SetColumnOffset(1, columnOffset);

  ImGui::BeginChild("##SideBar", ImVec2(50, 255), true);
  {
    ImGui::SetCursorPos(ImVec2(13, 17));
    ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.f, 0.f));

    if (sidebarTab0)
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(ActiveTextColor[0], ActiveTextColor[1],
                                     ActiveTextColor[2], animation_text));
    else
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(InactiveTextColor[0], InactiveTextColor[1],
                                     InactiveTextColor[2], 255));

    if (ImGui::Button(ICON_FA_USER "##Player", ImVec2(50, 30))) {
      PageNumber = 0;
      position = 25;
      if (!sidebarTab0)
        animationEx = true;
      if (!sidebarTab0)
        animation_text = 0;
      sidebarTab0 = true;
      sidebarTab1 = false;
      sidebarTab2 = false;
      sidebarTab3 = false;
      sidebarTab4 = false;
    };
    ImGui::PopStyleColor(1);

    ImGui::SetCursorPos(ImVec2(13, 68));
    if (sidebarTab1)
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(ActiveTextColor[0], ActiveTextColor[1],
                                     ActiveTextColor[2], animation_text));
    else
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(InactiveTextColor[0], InactiveTextColor[1],
                                     InactiveTextColor[2], 255));

    if (ImGui::Button(ICON_FA_CROSSHAIRS "##Weapons", ImVec2(50, 30))) {
      PageNumber = 1;
      position = 75;
      if (!sidebarTab1)
        animationEx = true;
      if (!sidebarTab1)
        animation_text = 0;
      sidebarTab0 = false;
      sidebarTab1 = true;
      sidebarTab2 = false;
      sidebarTab3 = false;
      sidebarTab4 = false;
    };
    ImGui::PopStyleColor(1);

    ImGui::SetCursorPos(ImVec2(12, 118));
    if (sidebarTab2)
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(ActiveTextColor[0], ActiveTextColor[1],
                                     ActiveTextColor[2], animation_text));
    else
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(InactiveTextColor[0], InactiveTextColor[1],
                                     InactiveTextColor[2], 255));

    if (ImGui::Button(ICON_FA_EYE "##Visual", ImVec2(50, 30))) {
      PageNumber = 2;
      position = 125;
      if (!sidebarTab2)
        animationEx = true;
      if (!sidebarTab2)
        animation_text = 0;
      sidebarTab0 = false;
      sidebarTab1 = false;
      sidebarTab2 = true;
      sidebarTab3 = false;
      sidebarTab4 = false;
    };
    ImGui::PopStyleColor(1);

    ImGui::SetCursorPos(ImVec2(12, 168));
    if (sidebarTab3)
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(ActiveTextColor[0], ActiveTextColor[1],
                                     ActiveTextColor[2], animation_text));
    else
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(InactiveTextColor[0], InactiveTextColor[1],
                                     InactiveTextColor[2], 255));

    if (ImGui::Button(ICON_FA_SERVER "##Server", ImVec2(50, 30))) {
      PageNumber = 3;
      position = 175;
      if (!sidebarTab3)
        animationEx = true;
      if (!sidebarTab3)
        animation_text = 0;
      sidebarTab0 = false;
      sidebarTab1 = false;
      sidebarTab2 = false;
      sidebarTab3 = true;
      sidebarTab4 = false;
    };
    ImGui::PopStyleColor(1);

    ImGui::SetCursorPos(ImVec2(12, 218));
    if (sidebarTab4)
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(ActiveTextColor[0], ActiveTextColor[1],
                                     ActiveTextColor[2], animation_text));
    else
      ImGui::PushStyleColor(ImGuiCol_Text,
                            IM_COL32(InactiveTextColor[0], InactiveTextColor[1],
                                     InactiveTextColor[2], 255));

    if (ImGui::Button(ICON_FA_COG "##Settings", ImVec2(50, 30))) {
      PageNumber = 4;
      position = 225;
      if (!sidebarTab4)
        animationEx = true;
      if (!sidebarTab4)
        animation_text = 0;
      sidebarTab0 = false;
      sidebarTab1 = false;
      sidebarTab2 = false;
      sidebarTab3 = false;
      sidebarTab4 = true;
    };
    ImGui::PopStyleColor(1);

    if (animationEx && deepFadeAnimation > 0) {
      deepFadeAnimation -= 8;
      if (deepFadeAnimation < 1) {
        animationButton = position;
        animationEx = false;
      }
    }

    if (!animationEx) {
      if (deepFadeAnimation < 255)
        deepFadeAnimation += 8;
    }

    if (animation_text <= 250)
      animation_text += 3;

    ImVec2 P1 = ImVec2(13, animationButton + 15);
    P1.x += CurrentWindowPos.x;
    P1.y += CurrentWindowPos.y;

    ImVec2 P2 = ImVec2(P1.x + 40, P1.y + 40);

    pDrawList = pWindowDrawList;
    pDrawList->AddRectFilled(P1, P2,
                             IM_COL32(IconChildColor[0], IconChildColor[1],
                                      IconChildColor[2], deepFadeAnimation),
                             4.0f);
  }
  ImGui::EndChild();

  ImGui::NextColumn();
  ImGui::PushStyleColor(ImGuiCol_ChildBg,
                        IM_COL32(BGColor[0], BGColor[1], BGColor[2], 255));

  static float currentWidth = 0.0f;
  float targetWidth = ToggleAnimations ? ImGui::GetContentRegionAvail().x * 0.5f
                                       : ImGui::GetContentRegionAvail().x + 5;
  float animationSpeed = 5.0f;
  float deltaTime = ImGui::GetIO().DeltaTime;

  currentWidth += (targetWidth - currentWidth) * animationSpeed * deltaTime;

  if (fabs(targetWidth - currentWidth) < 0.01f) {
    currentWidth = targetWidth;
  }

  ImVec2 mainContentSize = ImVec2(currentWidth, 255);
  bool begunedPage = false;
  if (PageNumber >= 0 && PageNumber <= 4) {
    begunedPage = true;
    ImGui::BeginChild("##MainContent", mainContentSize, true);
  }
  Submenu0_Personal(childVisibilityMap, PageNumber == 0 ||!Config::加载一次参数,!Config::加载一次参数);
  Submenu1_Aim(childVisibilityMap, PageNumber == 1||!Config::加载一次参数,!Config::加载一次参数);
  Submenu2_Visual(childVisibilityMap, PageNumber == 2||!Config::加载一次参数,!Config::加载一次参数);
  Submenu3_Server(childVisibilityMap, PageNumber == 3||!Config::加载一次参数,!Config::加载一次参数);
  Submenu4_Settings(childVisibilityMap, PageNumber == 4||!Config::加载一次参数,!Config::加载一次参数);
  #ifdef DUMP_HOOK
  saveMacho(EXCUTABLEPATH);//当dumphook的时候，需要在所有菜单执行完之后，才保存macho
  #endif
  
  if (begunedPage)
    ImGui::EndChild();
  ChildView(childVisibilityMap,!Config::加载一次参数);
  ImGui::Columns(1);
  LightTheme();
  if (!Config::加载一次参数){
    Config::加载一次参数 = true;
  }
}