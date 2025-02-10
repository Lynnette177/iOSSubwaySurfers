#include "../hooks/hooks.h"
#import "offsets.hpp"

bool InstallHooks() {
  uintptr_t UnityFrameworkBaseAddr = NULL;
  uint32_t moduleCount = _dyld_image_count();
  for (uint32_t i = 0; i < moduleCount; i++) {
    const char *moduleName = _dyld_get_image_name(i);
    if (strstr(moduleName, EXCUTABLENAME)) {
      UnityFrameworkBaseAddr = (uintptr_t)_dyld_get_image_header(i);
    }
  }
  if (UnityFrameworkBaseAddr) {
    FunctionAddress::initFunctionAddress(UnityFrameworkBaseAddr);
    GameFunction::initFunctions();
    HOOK(hookFunctionAddress_PlayerInfo__set_amountOfCoins_Address,
         hooks::new_PlayerInfo__set_amountOfCoins,
         hooks::org_PlayerInfo__set_amountOfCoins);
    HOOK(hookFunctionAddress_PlayerInfo__set_amountOfKeys_Address,
         hooks::new_PlayerInfo__set_amountOfKeys,
         hooks::org_PlayerInfo__set_amountOfKeys);
    HOOK(hookFunctionAddress_GameStats__set_score_Address,
         hooks::new_GameStats__set_score, hooks::org_GameStats__set_score);
    HOOK(hookFunctionAddress_HPowerupEnergy___TriggerIn_Address,
         hooks::new_HPowerupEnergy___TriggerIn,
         hooks::org_HPowerupEnergy___TriggerIn);
    HOOK(hookFunctionAddress_HCharSpeed___ChangeState_Address,
         hooks::new_HCharSpeed___ChangeState,
         hooks::org_HCharSpeed___ChangeState);
    HOOK(hookFunctionAddress_CharacterModel__GetScale_Address,
         hooks::new_CharacterModel__GetScale,
         hooks::org_CharacterModel__GetScale);
    HOOK(hookFunctionAddress_UnityEngine_Transform__set_position_Address,
         hooks::new_UnityEngine_Transform__set_position,
         hooks::org_UnityEngine_Transform__set_position);
    return true;
  }
  return false;
}
#define PATCH_RET ENCRYPTHEX("C0 03 5F D6")
#define PATCH_RET0 ENCRYPTHEX("00 00 80 D2 C0 03 5F D6")
#define PATCH_RET1 ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
#define PATCH_FROM_FAILED_TO_FINSH_ADS ENCRYPTHEX("C8 FF FF 17") //这里是跳转到finish的位置

void Initialize() { [menu setFrameworkName:EXCUTABLENAME]; }

void patch_at_start() {
  /*ONETIMEPATCH(ENCRYPTOFFSET("0x24AE224"),
               PATCH_RET0) // 移除SubwayAdManager__ShowSplashAd
  ONETIMEPATCH(ENCRYPTOFFSET("0x24AE448"),
               PATCH_RET1) // 移除SubwayAdManager__ShowSplashAdClosed
     */
  ONETIMEPATCH(
      ENCRYPTOFFSET("0x286D9D8"),
      PATCH_RET) // 禁用货币反作弊CheatDetectorManager__CurrencyCheatDetect
  ONETIMEPATCH(ENCRYPTOFFSET("0x286D224"),
               PATCH_RET) // 禁用CheatDetectorManager__ObscuredDetectorCallback
  ONETIMEPATCH(ENCRYPTOFFSET("0x286D91C"),
               PATCH_RET) // 禁用CheatDetectorManager__SpeedHackDetectorCallback
  ONETIMEPATCH(ENCRYPTOFFSET("0x286D504"),
               PATCH_RET) // 禁用CheatDetectorManager__ShieldUser
  ONETIMEPATCH(ENCRYPTOFFSET("0x2E83464"),
               PATCH_RET) // 禁用FrontScreen__UploadCheaterPlayerLog
  ONETIMEPATCH(ENCRYPTOFFSET("0x33323F8"),
               PATCH_RET) // 禁用BindWeChatManager__OnLoginShield
}