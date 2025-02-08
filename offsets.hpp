#import "Macros.h"
#include <__config>
#include <cstdint>

namespace FunctionAddress {
static uintptr_t HPowerupManager__get_instance_funcaddr = 0x2F5747C;
static uintptr_t HPowerupManager__IncEnergy_funcaddr = 0x2F6B8F4;
void initFunctionAddress(uintptr_t base) {
  HPowerupManager__IncEnergy_funcaddr += base;
  HPowerupManager__get_instance_funcaddr += base;
}
} // namespace FunctionAddress
namespace GameFunction {
void *(*HPowerupManager__get_instance)(void *method);
void (*HPowerupManager__IncEnergy)(void *_this, void *method);
void initFunctions() {
  HPowerupManager__get_instance =
      reinterpret_cast<decltype(HPowerupManager__get_instance)>(
          FunctionAddress::HPowerupManager__get_instance_funcaddr);
  HPowerupManager__IncEnergy =
      reinterpret_cast<decltype(HPowerupManager__IncEnergy)>(
          FunctionAddress::HPowerupManager__IncEnergy_funcaddr);
}
} // namespace GameFunction

namespace CustomFunctions {
void addHoverboardEnergy() {
  void *HPowerupManager = GameFunction::HPowerupManager__get_instance(0);
  GameFunction::HPowerupManager__IncEnergy(HPowerupManager, 0);
}
} // namespace CustomFunctions

#define offset_SuperRunVIPManager__IsActive "0x24BB334"
#define offset_IDreamSky_BagManager$$IsUnlockedCharacter "0x3065DF8"
#define offset_PlayerInfo__isHoverboardUnlockedm "0x1FBF558"
#define offset_IDreamSky_BagManager__IsUnlockedCharacterTheme "0x30660F8"
#define offset_CharacterStickerManager__isCharacterUnlocked "0x250D6D0"
#define offset_PlayerInfo__IsOrnamentUnlocked "0x1FE5018"
#define offset_HPFXBase___DefenseCheck "0x2F4BD4C"

namespace hookFunctionAddress {
static uintptr_t PlayerInfo__set_amountOfCoins_Address = 0x1FABA74;
static uintptr_t PlayerInfo__set_amountOfKeys_Address = 0x1FABD88;
static uintptr_t GameStats__set_score_Address = 0x2EF197C;
static uintptr_t HPowerupEnergy___TriggerIn_Address = 0x2F6B370;
static uintptr_t HCharSpeed___ChangeState_Address = 0x2F348D8;
} // namespace hookFunctionAddress

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
} // namespace hooks