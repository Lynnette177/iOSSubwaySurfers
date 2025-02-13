#import "SubMenu.h"
#include <string>
bool showLogs = false;
bool lightTheme = true;
bool ToggleButtonWithOffset(std::map<std::string, bool> &childVisibilityMap,
                            const char *icon, const char *name, bool *v,
                            std::vector<uint64_t> addr_vec,
                            std::vector<std::string> patch_vec, bool isPage,
                            std::string description, bool shouldLoad) {
  if (Descriptions[name] != description)
    Descriptions[name] = description;
  bool result = false;
  if (shouldLoad) {
#ifdef JAILED
    for (int i = 0; i < addr_vec.size(); i++) {
      ADDSWITCHPATCH(addr_vec[i], (char *)patch_vec[i].c_str());
    }
#endif
    if (*v != loadBoolSettings(name, false)) {
      *v = !(*v);
      result = true;
    }
  }
  if (isPage) {
    bool newChildVisible = childVisibilityMap[name];
    result = ToggleWidget(icon, name, v, &newChildVisible);
    childVisibilityMap[name] = newChildVisible;
  }
  if (*v) {
    bool displayed = false;
    for (int i = 0; i < enabledFeatures.size(); i++) {
      if (name == enabledFeatures[i]) {
        displayed = true;
        break;
      }
    }
    if (!displayed) {
      enabledFeatures.push_back(std::string(name));
      // debug_log(@"Push back feature name");
    }
    bool enabledPatch = false;
    for (int j = 0; j < addr_vec.size(); j++) {
      uint64_t addr = addr_vec[j];
      for (int i = 0; i < Patches.size(); i++) {
        if (Patches[i].get_TargetAddress() == getRealOffset(addr)) {
          enabledPatch = true;
          break;
        }
      }
    }
    if (!enabledPatch)
      result = true;
  } else {
    for (int i = 0; i < enabledFeatures.size(); i++) {
      if (name == enabledFeatures[i]) {
        enabledFeatures.erase(enabledFeatures.begin() + i);
        break;
      }
    }
  }
  if (result) { // 如果状态发生变化了 要么要关掉，要么要开开
    debug_log(@"Toggle Status Changed.");
    saveBoolSettings(name, *v); // 保存配置
    if (addr_vec.size() != patch_vec.size()) {
      debug_log(@"%s Toggle offsets and patch count not match!");
    }
    for (int j = 0; j < addr_vec.size(); j++) {
      uint64_t addr = addr_vec[j];
      const char *patch = patch_vec[j].c_str();
      if (*v) { // 需要打开
#ifdef JAILED
        ACTIVATESWITCHPATCH(addr, (char *)patch)
#else
        bool inited = false;
        for (int i = 0; i < Patches.size(); i++) {
          if (Patches[i].get_TargetAddress() == getRealOffset(addr)) {
            Patches[i].Modify();
            inited = true;
            break;
          }
        }
        if (!inited) {
          MemoryPatch newPatch = patchOffset(addr, patch);
          Patches.push_back(newPatch);
        }
#endif
      } else { // 需要关闭
#ifdef JAILED
        DEACTIVATESWITCHPATCH(addr, (char *)patch)
#else
        debug_log(@"Patches Count: %d", Patches.size());
        for (int i = 0; i < Patches.size(); i++) {
          debug_log(@"%p %p", Patches[i].get_TargetAddress(),
                    getRealOffset(addr));
          if (Patches[i].get_TargetAddress() == getRealOffset(addr)) {
            Patches[i].Restore();
            break;
          }
        }
#endif
      }
    }
  }
  return result;
}

bool SimpleToggleButton(std::map<std::string, bool> &childVisibilityMap,
                        const char *icon, const char *name, bool *v,
                        bool isPage, std::string description, bool shouldLoad) {
  bool result = false;
  if (Descriptions[name] != description)
    Descriptions[name] = description;
  if (shouldLoad) {
    if (*v != loadBoolSettings(name, false)) {
      *v = !(*v);
      result = true;
    }
  }
  if (*v) {
    bool displayed = false;
    for (int i = 0; i < enabledFeatures.size(); i++) {
      if (name == enabledFeatures[i] ||
          enabledFeatures[i] == WATERMARK &&
              strcmp(name, "显示已开启功能") == 0) {
        displayed = true;
        break;
      }
    }
    if (!displayed) {
      if ((strcmp(name, "显示已开启功能")) == 0) {
        enabledFeatures.insert(enabledFeatures.begin(), std::string(WATERMARK));
      } else
        enabledFeatures.push_back(std::string(name));
      // debug_log(@"Push back feature name");
    }
  } else {
    for (int i = 0; i < enabledFeatures.size(); i++) {
      if (name == enabledFeatures[i]) {
        enabledFeatures.erase(enabledFeatures.begin() + i);
        break;
      }
    }
  }
  if (isPage) {
    bool newChildVisible = childVisibilityMap[name];
    result = ToggleWidget(icon, name, v, &newChildVisible);
    if (result) {
      saveBoolSettings(name, *v);
    }
    childVisibilityMap[name] = newChildVisible;
    return result;
  }
  return result;
}
void Submenu0_Personal(std::map<std::string, bool> &childVisibilityMap,
                       bool isPage, bool shouldLoad) {
  if (isPage)
    ImGui::Text("信息选项");
  SimpleToggleButton(childVisibilityMap, ICON_FA_COINS, u8"重新登录",
                     &Config ::重新登录, isPage,
                     "开启后，重启游戏进行重新登录，避免因为外挂导致登录弹窗消失", shouldLoad);
  ToggleButtonWithOffset(
      childVisibilityMap, ICON_FA_ID_CARD, u8"跳过实名认证", &Config ::实名认证,
      {offset_AntiAddictionManager_HasVerifid}, {(char *)PATCH_RET1}, isPage,
      "开启后点击按钮即可强制判定实名认证已经通过", shouldLoad);
  ToggleButtonWithOffset(
      childVisibilityMap, ICON_FA_RUNNING, u8"强制开启炫跑卡", &Config ::炫跑卡,
      {offset_SuperRunVIPManager__IsActive}, {(char *)PATCH_RET1}, isPage,
      "在本地强制开启炫跑卡。注意：无法领取炫跑卡专属奖励，但是可多一次免费复"
      "活",
      shouldLoad);
  ToggleButtonWithOffset(childVisibilityMap, ICON_FA_AD, u8"广告退出即奖励",
                         &Config ::广告奖励,
                         {offset_SubwayAdManager__VideoFailed},
                         {(char *)PATCH_FROM_FAILED_TO_FINSH_ADS}, isPage,
                         "开启后，观看广告立即退出就可以获得奖励", shouldLoad);
  ToggleButtonWithOffset(
      childVisibilityMap, ICON_FA_MALE, u8"解锁所有角色", &Config ::解锁角色,
      {offset_IDreamSky_BagManager$$IsUnlockedCharacter}, {(char *)PATCH_RET1},
      isPage, "开启后，自动解锁全部角色", shouldLoad);
  ToggleButtonWithOffset(
      childVisibilityMap, ICON_FA_SNOWBOARDING, u8"解锁所有滑板",
      &Config ::解锁滑板, {offset_PlayerInfo__isHoverboardUnlockedm},
      {(char *)PATCH_RET1}, isPage, "开启后，自动解锁全部滑板", shouldLoad);
  ToggleButtonWithOffset(
      childVisibilityMap, ICON_FA_MASK, u8"解锁角色装扮", &Config ::解锁主题,
      {offset_IDreamSky_BagManager__IsUnlockedCharacterTheme},
      {(char *)PATCH_RET1}, isPage, "开启后自动解锁角色的全部装扮", shouldLoad);
  ToggleButtonWithOffset(childVisibilityMap, ICON_FA_STICKY_NOTE,
                         u8"解锁所有Sticker", &Config ::解锁sticker,
                         {offset_CharacterStickerManager__isCharacterUnlocked},
                         {(char *)PATCH_RET1}, isPage,
                         "开启后，自动解锁角色全部Sticker", shouldLoad);
  ToggleButtonWithOffset(
      childVisibilityMap, ICON_FA_GEM, u8"解锁所有背饰", &Config ::解锁背饰,
      {offset_PlayerInfo__IsOrnamentUnlocked}, {(char *)PATCH_RET1}, isPage,
      "解锁所有背饰品", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_COINS, u8"修改金币",
                     &Config ::修改金币, isPage,
                     "开启后，当金币数量发生变化时，将修改其数目", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_KEY, u8"修改钥匙",
                     &Config ::修改钥匙, isPage,
                     "开启后，当钥匙数量发生变化时，将修改其数目", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_KEY, u8"修改宝物钥匙",
                     &Config ::修改宝物钥匙, isPage,
                     "开启后，当金币数量发生变化时，也会连带修改宝物钥匙数目",
                     shouldLoad);
}
void Submenu1_Aim(std::map<std::string, bool> &childVisibilityMap, bool isPage,
                  bool shouldLoad) {
  if (isPage)
    ImGui::Text("控制选项");
  ToggleButtonWithOffset(
      childVisibilityMap, ICON_FA_YIN_YANG, u8"无视碰撞", &Config ::无视碰撞,
      {offset_SYBO_Subway_Utilities_DebugSettings__get_IsAllowed,
       offset_SYBO_Subway_Utilities_DebugSettings__get_CharacterInvincible},
      {(char *)PATCH_RET1, (char *)PATCH_RET1}, isPage,
      "开启后，碰撞不会死亡，而是在原地等待操作", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_CALCULATOR, u8"修改分数",
                     &Config ::修改分数, isPage,
                     "开启后，当分数发生变化时将修改分数。适用于单机和分数赛。"
                     "分数赛内开局修改过高会导致封号，请注意。",
                     shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_GLOBE_ASIA, u8"修改重力",
                     &Config ::修改重力, isPage, "开启后，修改本地角色重力",
                     shouldLoad);
}

void Submenu2_Visual(std::map<std::string, bool> &childVisibilityMap,
                     bool isPage, bool shouldLoad) {
  if (isPage)
    ImGui::Text("视觉选项");
  SimpleToggleButton(
      childVisibilityMap, ICON_FA_DOVE, u8"鸟瞰视角", &Config ::上帝视角,
      isPage,
      "开启后俯视赛道。注意会导致下一步的地图加载未知错误，请及时关闭。",
      shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_PEN, u8"方框绘制",
                     &Config ::显示方框, isPage,
                     "开启后会在玩家实体上显示方框。", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_USER_ALT_SLASH,
                     u8"修改模型大小", &Config ::修改模型大小, isPage,
                     "开启后在下一次加载模型的时候将改变模型的大小倍率",
                     shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_LIST, u8"显示已开启功能",
                     &Config ::显示已开启功能, isPage,
                     "开启后将在左上角展示已启用的功能", shouldLoad);
}
void Submenu3_Server(std::map<std::string, bool> &childVisibilityMap,
                     bool isPage, bool shouldLoad) {
  if (isPage)
    ImGui::Text("PVP选项");
  SimpleToggleButton(childVisibilityMap, ICON_FA_BATTERY_FULL, u8"修改昵称",
                     &Config ::修改昵称, isPage, "开启后修改匹配时本人昵称",
                     shouldLoad);
  ToggleButtonWithOffset(childVisibilityMap, ICON_FA_SHIELD_ALT, u8"无视道具",
                         &Config ::无视道具, {offset_HPFXBase___DefenseCheck},
                         {(char *)PATCH_RET1}, isPage,
                         "开启后，无视敌方对你使用的道具", shouldLoad);
  SimpleToggleButton(
      childVisibilityMap, ICON_FA_BATTERY_FULL, u8"滑板双倍充能",
      &Config ::双倍充能, isPage,
      "开启后拾取滑板能量翻倍。注意使用太多速度太快可能被判定作弊", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_PLUG, u8"滑板自动充能",
                     &Config ::自动充能, isPage, "开启后滑板能量自动增加",
                     shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_ROCKET, u8"疯狂加速",
                     &Config ::疯狂加速, isPage,
                     "开启后，无论是碰撞/磕绊/"
                     "踩到加速减速板，都会直接开启最高等级的加速。PVP下的无视碰"
                     "撞并且可以不掉滑板",
                     shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_COMMENT, u8"自定义消息内容",
                     &Config ::自定义消息内容, isPage,
                     "开启后，在PVP中随意发送任何消息将被替换为此内容",
                     shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_TACHOMETER_ALT, u8"修改速度",
                     &Config ::修改速度, isPage, "开启后，在PVP中修改人物速度",
                     shouldLoad);
}
void Submenu4_Settings(std::map<std::string, bool> &childVisibilityMap,
                       bool isPage, bool shouldLoad) {
  if (isPage)
    ImGui::Text("设置");
  SimpleToggleButton(childVisibilityMap, ICON_FA_LIGHTBULB, u8"亮色主题",
                     &lightTheme, isPage, "显示亮色主题", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_PODCAST, u8"主播模式",
                     &StreamerMode, isPage, "开启后录屏看不见绘制", shouldLoad);
  SimpleToggleButton(childVisibilityMap, ICON_FA_TERMINAL, u8"显示日志",
                     &showLogs, isPage, "显示控制台", shouldLoad);
  if (isPage && showLogs) {
    Console::render();
  }
}
void ChildView(const std::map<std::string, bool> &childVisibilityMap,
               bool shouldLoad) {
  for (const auto &pair : childVisibilityMap) {
    const std::string &widgetName = pair.first;
    bool isVisible = pair.second;

    if (isVisible || shouldLoad) {
      ImGui::SameLine();
      ImGui::PushStyleColor(ImGuiCol_ChildBg,
                            IM_COL32(ChildColor[0], ChildColor[1],
                                     ChildColor[2], animation_text));

      ImGui::BeginChild(("##newChild_" + widgetName).c_str(),
                        ImVec2(ImGui::GetContentRegionAvail().x + 5,
                               ImGui::GetContentRegionAvail().y),
                        true);
      {
        ImVec2 titleBarSize = ImVec2(ImGui::GetContentRegionAvail().x, 25);
        ImVec2 titleBarPos = ImGui::GetCursorScreenPos();

        float rounding = 5.0f;
        ImGui::GetWindowDrawList()->AddRectFilled(
            titleBarPos,
            ImVec2(titleBarPos.x + titleBarSize.x,
                   titleBarPos.y + titleBarSize.y),
            IM_COL32(IconChildColor[0], IconChildColor[1], IconChildColor[2],
                     animation_text),
            rounding, ImDrawFlags_RoundCornersTop);

        std::string titleText = widgetName + u8"选项";
        ImVec2 textSize = ImGui::CalcTextSize(titleText.c_str());
        float textX = titleBarPos.x + (titleBarSize.x - textSize.x) / 2.0f;

        ImGui::SetCursorScreenPos(ImVec2(
            textX, titleBarPos.y + (titleBarSize.y - textSize.y) / 2.0f));
        ImGui::PushStyleColor(
            ImGuiCol_Text, IM_COL32(InactiveTextColor[0], InactiveTextColor[1],
                                    InactiveTextColor[2], 255));
        ImGui::Text("%s", titleText.c_str());
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5);
        ImGui::SetWindowFontScale(0.8f);

        ImGui::Text(ICON_FA_INFO_CIRCLE);
        ImGui::SameLine();
        ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x + 5);
        ImGui::Text(("帮助：" + Descriptions[widgetName]).c_str());
        ImGui::PopTextWrapPos();
        if (widgetName == "修改金币") {
          SliderIntMini("将金币修改为", &Config::修改成多少金币, 0, 100000,
                        shouldLoad);
        } else if (widgetName == "修改钥匙") {
          SliderIntMini("将钥匙修改为", &Config::修改成多少钥匙, 0, 10000,
                        shouldLoad);
        } else if (widgetName == "修改宝物钥匙") {
          SliderIntMini("将宝物钥匙修改为", &Config::修改成多少宝物钥匙, 0,
                        1000, shouldLoad);
        } else if (widgetName == "修改模型大小") {
          SliderFloatMini("将模型大小修改为", &Config::模型大小倍率, 0.1, 10,
                          shouldLoad);
        } else if (widgetName == "修改分数") {
          static std::string scoreText = "";
          if (Config::修改成多少分 != 0)
            scoreText = std::to_string(Config::修改成多少分);
          TextInputMini("将分数修改为", scoreText, true);
          if (scoreText == "")
            Config::修改成多少分 = 0;
          else
            Config::修改成多少分 = std::stoll(scoreText.c_str());

        } else if (widgetName == "修改昵称") {
          TextInputMini("将昵称修改为", Config::修改昵称为, false);
        } else if (widgetName == "自定义消息内容") {
          TextInputMini("将内容修改为", Config::要发送的消息内容, false);
        } else if (widgetName == "修改重力") {
          SliderFloatMini("重力修改为", &Config::重力修改为, 0.01f, 300.f,
                          shouldLoad);
        } else if (widgetName == "修改速度") {
          SliderFloatMini("速度修改为", &Config::速度修改为, 0.01f, 1700.f,
                          shouldLoad);
        } else if (widgetName == "显示日志") {
          ImGui::Text(ICON_FA_INFO_CIRCLE);
          ImGui::SameLine();
          ImGui::PushTextWrapPos(ImGui::GetContentRegionAvail().x + 5);
          ImGui::Text("ClientX debug logs");
          ImGui::PopTextWrapPos();
        }
        ImGui::SetWindowFontScale(1.0f);
        ImGui::PopStyleColor();
      }
      ImGui::EndChild();
      ImGui::PopStyleColor();
    }
  }
}
void ESP() {

  static dispatch_once_t onceToken;
  static uint64_t loopTimer = mach_absolute_time();

  mainFunction();
  if (Config::自动充能) {
    uint64_t currentTimer = mach_absolute_time();
    if (Entities.size() > 0) {                // 确保在游戏中
      if (currentTimer - loopTimer > 5.0e6) { // 5毫秒
        loopTimer = currentTimer;
        CustomFunctions::addHoverboardEnergy();
      }
    }
  }
  dispatch_once(&onceToken, ^{
    Console::addLog("Rigel ESP Activated.");
  });
  ImDrawList *Draw = ImGui::GetBackgroundDrawList();
  ImVec2 screenSize = ImGui::GetIO().DisplaySize;

  if (Config::显示已开启功能) {
    int textw = 0;
    int texth = 0;
    for (int i = 0; i < enabledFeatures.size(); i++) {
      ImVec2 textSize = ImGui::CalcTextSize(enabledFeatures[i].c_str());
      if (textSize.x > textw)
        textw = textSize.x;
      if (textSize.y > texth)
        texth = textSize.y;
    }
    /*绘制一个矩形在左上角并在其中显示所有启用的功能*/
    ImVec2 rectSize = ImVec2(textw + 10, texth * enabledFeatures.size() + 10);
    ImVec2 rectPos = ImVec2(10, 10); // 矩形的位置在左上角

    // 绘制矩形背景
    Draw->AddRectFilled(rectPos,
                        ImVec2(rectPos.x + rectSize.x, rectPos.y + rectSize.y),
                        IM_COL32(0, 0, 0, 150), 4);

    // 在矩形内显示所有启用的功能
    for (int i = 0; i < enabledFeatures.size(); i++) {
      ImVec2 textPos = ImVec2(rectPos.x + 5, rectPos.y + 5 + i * texth);
      Draw->AddText(textPos, IM_COL32(255, 255, 255, 255),
                    enabledFeatures[i].c_str());
    }
  }

  for (const auto &entity : Entities) {
    if (Config::显示方框) {
      auto Camera = GameFunction::UnityEngine_Camera__get_main(NULL);
      if (Camera) {
        UnityEngine_Vector3_o centerPos = entity.TransformPosition;
        debug_log(@"Position %f %f %f", centerPos.fields.x, centerPos.fields.y,
                  centerPos.fields.z);
        UnityEngine_Vector3_o buttom1 =
            centerPos + UnityEngine_Vector3_o(-4, 0, -4);
        UnityEngine_Vector3_o buttom2 =
            centerPos + UnityEngine_Vector3_o(-4, 0, 4);
        UnityEngine_Vector3_o buttom3 =
            centerPos + UnityEngine_Vector3_o(4, 0, 4);
        UnityEngine_Vector3_o buttom4 =
            centerPos + UnityEngine_Vector3_o(4, 0, -4);
        UnityEngine_Vector3_o top1 = buttom1 + UnityEngine_Vector3_o(0, 12, 0);
        UnityEngine_Vector3_o top2 = buttom2 + UnityEngine_Vector3_o(0, 12, 0);
        UnityEngine_Vector3_o top3 = buttom3 + UnityEngine_Vector3_o(0, 12, 0);
        UnityEngine_Vector3_o top4 = buttom4 + UnityEngine_Vector3_o(0, 12, 0);

        buttom1 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(
            Camera, buttom1, 2, 0);
        buttom2 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(
            Camera, buttom2, 2, 0);
        buttom3 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(
            Camera, buttom3, 2, 0);
        buttom4 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(
            Camera, buttom4, 2, 0);
        top1 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(Camera,
                                                                    top1, 2, 0);
        top2 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(Camera,
                                                                    top2, 2, 0);
        top3 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(Camera,
                                                                    top3, 2, 0);
        top4 = GameFunction::UnityEngine_Camera__WorldToScreenPoint(Camera,
                                                                    top4, 2, 0);
        bool result = false;
        ImVec2 screen_buttom1 = {};
        ImVec2 screen_buttom2 = {};
        ImVec2 screen_buttom3 = {};
        ImVec2 screen_buttom4 = {};
        ImVec2 screen_top1 = {};
        ImVec2 screen_top2 = {};
        ImVec2 screen_top3 = {};
        ImVec2 screen_top4 = {};
        result &= UVector3toScreenPos(buttom1, screenSize.y, screen_buttom1);
        result &= UVector3toScreenPos(buttom2, screenSize.y, screen_buttom2);
        result &= UVector3toScreenPos(buttom3, screenSize.y, screen_buttom3);
        result &= UVector3toScreenPos(buttom4, screenSize.y, screen_buttom4);
        result &= UVector3toScreenPos(top1, screenSize.y, screen_top1);
        result &= UVector3toScreenPos(top2, screenSize.y, screen_top2);
        result &= UVector3toScreenPos(top3, screenSize.y, screen_top3);
        result &= UVector3toScreenPos(top4, screenSize.y, screen_top4);
        debug_log(@"ScreenPos:%f %f", screen_buttom1.x, screen_buttom1.y);
        if (1) {
          Draw->AddLine(screen_buttom1, screen_buttom2, 0xffffffff, 2);
          Draw->AddLine(screen_buttom2, screen_buttom3, 0xffffffff, 2);
          Draw->AddLine(screen_buttom3, screen_buttom4, 0xffffffff, 2);
          Draw->AddLine(screen_buttom4, screen_buttom1, 0xffffffff, 2);
          Draw->AddLine(screen_top1, screen_top2, 0xffffffff, 2);
          Draw->AddLine(screen_top2, screen_top3, 0xffffffff, 2);
          Draw->AddLine(screen_top3, screen_top4, 0xffffffff, 2);
          Draw->AddLine(screen_top4, screen_top1, 0xffffffff, 2);
          Draw->AddLine(screen_buttom1, screen_top1, 0xffffffff, 2);
          Draw->AddLine(screen_buttom2, screen_top2, 0xffffffff, 2);
          Draw->AddLine(screen_buttom3, screen_top3, 0xffffffff, 2);
          Draw->AddLine(screen_buttom4, screen_top4, 0xffffffff, 2);
        } else
          continue;
      }
    }
  }
}