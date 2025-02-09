#include "GameStructs.h"
#import "Macros.h"
#include <__config>
#include <cstdint>

#define offset_SuperRunVIPManager__IsActive "0x24BB334"
#define offset_IDreamSky_BagManager$$IsUnlockedCharacter "0x3065DF8"
#define offset_PlayerInfo__isHoverboardUnlockedm "0x1FBF558"
#define offset_IDreamSky_BagManager__IsUnlockedCharacterTheme "0x30660F8"
#define offset_CharacterStickerManager__isCharacterUnlocked "0x250D6D0"
#define offset_PlayerInfo__IsOrnamentUnlocked "0x1FE5018"
#define offset_HPFXBase___DefenseCheck "0x2F4BD4C"
#define offset_SubwayAdManager__VideoFailed "0x24AE11C"
#define offset_SYBO_Subway_Utilities_DebugSettings__get_IsAllowed "0x2342988"
#define offset_SYBO_Subway_Utilities_DebugSettings__get_CharacterInvincible    \
  "0x2342B74"

void Initialize() {
  [menu setFrameworkName:"UnityFramework"];
  patchOffset(
      ENCRYPTOFFSET("0x24AE224"),
      ENCRYPTHEX(
          "00 00 80 D2 C0 03 5F D6")); // 移除SubwayAdManager__ShowSplashAd
  patchOffset(
      ENCRYPTOFFSET("0x24AE448"),
      ENCRYPTHEX(
          "20 00 80 52 C0 03 5F D6")); // 移除SubwayAdManager__ShowSplashAdClosed
  patchOffset(
      ENCRYPTOFFSET("0x286D9D8"),
      ENCRYPTHEX(
          "C0 03 5F D6")); // 禁用货币反作弊CheatDetectorManager__CurrencyCheatDetect
  patchOffset(
      ENCRYPTOFFSET("0x286D224"),
      ENCRYPTHEX(
          "C0 03 5F D6")); // 禁用CheatDetectorManager__ObscuredDetectorCallback
  patchOffset(
      ENCRYPTOFFSET("0x286D91C"),
      ENCRYPTHEX(
          "C0 03 5F D6")); // 禁用CheatDetectorManager__SpeedHackDetectorCallback
  patchOffset(
      ENCRYPTOFFSET("0x286D504"),
      ENCRYPTHEX("C0 03 5F D6")); // 禁用CheatDetectorManager__ShieldUser
  patchOffset(
      ENCRYPTOFFSET("0x2E83464"),
      ENCRYPTHEX("C0 03 5F D6")); // 禁用FrontScreen__UploadCheaterPlayerLog
}
namespace hookFunctionAddress {
static uintptr_t PlayerInfo__set_amountOfCoins_Address = 0x1FABA74;
static uintptr_t PlayerInfo__set_amountOfKeys_Address = 0x1FABD88;
static uintptr_t GameStats__set_score_Address = 0x2EF197C;
static uintptr_t HPowerupEnergy___TriggerIn_Address = 0x2F6B370;
static uintptr_t HCharSpeed___ChangeState_Address = 0x2F348D8;
static uintptr_t CharacterModel__GetScale_Address = 0x22bd2bc;
static uintptr_t UnityEngine_Transform__set_position_Address = 0x435722C;
} // namespace hookFunctionAddress

namespace FunctionAddress {
static uintptr_t HPowerupManager__get_instance_funcaddr = 0x2F5747C;
static uintptr_t HPowerupManager__IncEnergy_funcaddr = 0x2F6B8F4;
static uintptr_t PlayerInfo__set_NewTreasureKey_funcaddr = 0x1fec5f8;
void initFunctionAddress(uintptr_t base) {
  HPowerupManager__IncEnergy_funcaddr += base;
  HPowerupManager__get_instance_funcaddr += base;
  PlayerInfo__set_NewTreasureKey_funcaddr += base;
}
} // namespace FunctionAddress
namespace GameFunction {
void *(*HPowerupManager__get_instance)(void *method);
void (*HPowerupManager__IncEnergy)(void *_this, void *method);
void (*PlayerInfo__set_NewTreasureKey)(void *_this, int32_t value,
                                       void *method);

void initFunctions() {
  HPowerupManager__get_instance =
      reinterpret_cast<decltype(HPowerupManager__get_instance)>(
          FunctionAddress::HPowerupManager__get_instance_funcaddr);
  HPowerupManager__IncEnergy =
      reinterpret_cast<decltype(HPowerupManager__IncEnergy)>(
          FunctionAddress::HPowerupManager__IncEnergy_funcaddr);
  PlayerInfo__set_NewTreasureKey =
      reinterpret_cast<decltype(PlayerInfo__set_NewTreasureKey)>(
          FunctionAddress::PlayerInfo__set_NewTreasureKey_funcaddr);
}
} // namespace GameFunction

namespace CustomFunctions {
void addHoverboardEnergy() {
  void *HPowerupManager = GameFunction::HPowerupManager__get_instance(0);
  GameFunction::HPowerupManager__IncEnergy(HPowerupManager, 0);
}
void setNewTreasureKey(void *PlayerInfoInstance, int32_t value) {
  GameFunction::PlayerInfo__set_NewTreasureKey(PlayerInfoInstance, value, 0);
}
} // namespace CustomFunctions

namespace hooks {
void (*org_PlayerInfo__set_amountOfCoins)(void *_this, int32_t value,
                                          void *method);
void new_PlayerInfo__set_amountOfCoins(void *_this, int32_t value,
                                       void *method) {
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("修改金币")];
  if (isOn) {
    value = [[switches getValueFromSwitch:NSSENCRYPT("修改金币")] intValue];
  }
  org_PlayerInfo__set_amountOfCoins(_this, value, method);
  isOn = [switches isSwitchOn:NSSENCRYPT("修改宝物钥匙")];
  if (isOn) {
    int32_t TreasureKeyvalue =
        [[switches getValueFromSwitch:NSSENCRYPT("修改宝物钥匙")] intValue];
    CustomFunctions::setNewTreasureKey(_this, TreasureKeyvalue);
  }
}
void (*org_PlayerInfo__set_amountOfKeys)(void *_this, int32_t value,
                                         void *method);
void new_PlayerInfo__set_amountOfKeys(void *_this, int32_t value,
                                      void *method) {
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("修改钥匙")];
  if (isOn) {
    value = [[switches getValueFromSwitch:NSSENCRYPT("修改钥匙")] intValue];
  }
  org_PlayerInfo__set_amountOfKeys(_this, value, method);
}
void (*org_GameStats__set_score)(void *_this, int32_t value, void *method);
void new_GameStats__set_score(void *_this, int32_t value, void *method) {
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("修改分数")];
  if (isOn) {
    value = [[switches getValueFromSwitch:NSSENCRYPT("修改分数")] intValue];
  }
  org_GameStats__set_score(_this, value, method);
}
bool (*org_SuperRunVIPManager__IsActive)(void *_this, void *method);
bool new_SuperRunVIPManager__IsActive(void *_this, void *method) {
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("强开炫跑卡")];
  if (isOn) {
    return true;
  }
  return org_SuperRunVIPManager__IsActive(_this, method);
}

void (*org_HPowerupEnergy___TriggerIn)(void *_this, void *method);
void new_HPowerupEnergy___TriggerIn(void *_this, void *method) {
  org_HPowerupEnergy___TriggerIn(_this, method);
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("PVP双倍滑板能量")];
  if (isOn) {
    CustomFunctions::addHoverboardEnergy();
  }
}

void (*org_HCharSpeed___ChangeState)(void *_this, uint8_t state,
                                     float bumpSpeedLossPercentage,
                                     int32_t accLevel, bool forceChange,
                                     void *method);
void new_HCharSpeed___ChangeState(void *_this, uint8_t state,
                                  float bumpSpeedLossPercentage,
                                  int32_t accLevel, bool forceChange,
                                  void *method) {
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("PVP疯狂加速")];
  if (isOn) {
    accLevel = 3;
    if (state == 3LL || bumpSpeedLossPercentage != 0.0) {
      state = 2;
      bumpSpeedLossPercentage = 0.0;
      forceChange = 1;
    }
  }
  org_HCharSpeed___ChangeState(_this, state, bumpSpeedLossPercentage, accLevel,
                               forceChange, method);
}

UnityEngine_Vector3_o (*org_CharacterModel__GetScale)(void *_this,
                                                      int32_t characterType,
                                                      void *method);
UnityEngine_Vector3_o
new_CharacterModel__GetScale(void *_this, int32_t characterType, void *method) {
  auto result = org_CharacterModel__GetScale(_this, characterType, method);
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("修改模型大小")];
  if (isOn) {
    float value =
        [[switches getValueFromSwitch:NSSENCRYPT("修改模型大小")] floatValue];
    result.fields.x *= value;
    result.fields.y *= value;
    result.fields.z *= value;
  }
  return result;
}

void (*org_UnityEngine_Transform__set_position)(
    void *_this, // UnityEngine_Transform_o
    UnityEngine_Vector3_o value, void *method);

void new_UnityEngine_Transform__set_position(
    void *_this, // UnityEngine_Transform_o
    UnityEngine_Vector3_o value, void *method) {
  BOOL isOn = [switches isSwitchOn:NSSENCRYPT("上帝视角")];
  if (isOn) {
    value.fields.y = 100;
  }
  org_UnityEngine_Transform__set_position(_this, value, method);
}
} // namespace hooks