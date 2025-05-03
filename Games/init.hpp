#include "../hooks/hooks.h"
#import "offsets.hpp"

bool InstallHooks()
{
     uintptr_t UnityFrameworkBaseAddr = NULL;
     uint32_t moduleCount = _dyld_image_count();
     for (uint32_t i = 0; i < moduleCount; i++)
     {
          const char *moduleName = _dyld_get_image_name(i);
          if (strstr(moduleName, EXCUTABLENAME))
          {
               UnityFrameworkBaseAddr = (uintptr_t)_dyld_get_image_header(i);
          }
     }
     if (UnityFrameworkBaseAddr)
     {
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
          HOOK(hookFunctionAddress_SYBO_Subway_Cameras_CameraData__get_CameraPositionOffset,
               hooks::new_SYBO_Subway_Cameras_CameraData__get_CameraPositionOffset,
               hooks::org_SYBO_Subway_Cameras_CameraData__get_CameraPositionOffset);
          HOOK(hookFunctionAddress_HRealPVPRoomManager__CommitGameChat_Address,
               hooks::new_HRealPVPRoomManager__CommitGameChat,
               hooks::org_HRealPVPRoomManager__CommitGameChat);
          HOOK(hookFunctionAddress_SYBO_Subway_Characters_Character__ApplyGravity,
               hooks::new_SYBO_Subway_Characters_Character__ApplyGravity,
               hooks::org_SYBO_Subway_Characters_Character__ApplyGravity);
          HOOK(hookFunctionAddress_HCharSpeed__get_speed,
               hooks::new_HCharSpeed__get_speed, hooks::org_HCharSpeed__get_speed);
          HOOK(hookFunctionAddress_PlayerInfo__get_playerNickName,
               hooks::new_PlayerInfo__get_playerNickName,
               hooks::org_PlayerInfo__get_playerNickName);
          HOOK(hookFunctionAddress_ReportPlayerManager__ReportPlayer,
               hooks::new_ReportPlayerManager__ReportPlayer,
               hooks::org_ReportPlayerManager__ReportPlayer);
          HOOK(hookFunctionAddress_PartyPvpManager__get_allRank,
               hooks::new_PartyPvpManager__get_allRank,
               hooks::org_PartyPvpManager__get_allRank);
          HOOK(hookFunctionAddress_RealPVPManager__get_allRank,
               hooks::new_RealPVPManager__get_allRank,
               hooks::org_RealPVPManager__get_allRank);
          HOOK(hookFunctionAddress_NetDirector__Rule_ReqItemByServer,
               hooks::new_NetDirector__Rule_ReqItemByServer, hooks::org_NetDirector__Rule_ReqItemByServer);
          // HOOK(hookFunctionAddress_EncrptUtil__AESEncrypt,
          //      hooks::new_EncrptUtil__AESEncrypt, hooks::org_EncrptUtil__AESEncrypt);

          return true;
     }
     return false;
}

void patch_at_start()
{
     ONETIMEPATCH(ENCRYPTOFFSET("0x249D138"),
                  PATCH_RET0) // 移除SubwayAdManager__ShowSplashAd
     ONETIMEPATCH(ENCRYPTOFFSET("0x249D35C"),
                  PATCH_RET1) // 移除SubwayAdManager__ShowSplashAdClosed
     ONETIMEPATCH(
         ENCRYPTOFFSET("0x27DA5CC"),
         PATCH_RET) // 禁用货币反作弊CheatDetectorManager__CurrencyCheatDetect
     ONETIMEPATCH(ENCRYPTOFFSET("0x27D9E18"),
                  PATCH_RET) // 禁用CheatDetectorManager__ObscuredDetectorCallback
     ONETIMEPATCH(ENCRYPTOFFSET("0x27DA510"),
                  PATCH_RET) // 禁用CheatDetectorManager__SpeedHackDetectorCallback
     ONETIMEPATCH(ENCRYPTOFFSET("0x27DA0F8"),
                  PATCH_RET) // 禁用CheatDetectorManager__ShieldUser
     ONETIMEPATCH(ENCRYPTOFFSET("0x2EBC37C"),
                  PATCH_RET) // 禁用FrontScreen__UploadCheaterPlayerLog
     ONETIMEPATCH(ENCRYPTOFFSET("0x334D5B8"),
                  PATCH_RET) // 禁用BindWeChatManager__OnLoginShield
     ONETIMEPATCH(ENCRYPTOFFSET("0x1FC0248"),
                  PATCH_RET0) // PlayerInfo__CheckCheaterByDeviceId
     ONETIMEPATCH(ENCRYPTOFFSET("0x1FC037C"),
                  PATCH_RET0) // PlayerInfo__CheckCheaterByCoins
     ONETIMEPATCH(ENCRYPTOFFSET("0x1FC0468"),
                  PATCH_RET0) // PlayerInfo__CheckCheaterByKeys
     ONETIMEPATCH(ENCRYPTOFFSET("0x2F45834"),
                  PATCH_RET0) // Globals__isCheater
     ONETIMEPATCH(ENCRYPTOFFSET("0x1EC2180"),
                  PATCH_RET0) // PVPModuleMgr__get_CheatState
     ONETIMEPATCH(ENCRYPTOFFSET("0x1EC2208"),
                  PATCH_RET) // PVPModuleMgr__set_CheatState
     ONETIMEPATCH(ENCRYPTOFFSET("0x3583BA4"),
                  PATCH_RET0) // OnlineSettings__get_CheckCheatAPP
     ONETIMEPATCH(ENCRYPTOFFSET("0x3584ED4"),
                  PATCH_RET0) // OnlineSettings__get_CheckCheatAccumulate
     ONETIMEPATCH(ENCRYPTOFFSET("0x2C621D8"),
                  PATCH_RET0) // AdditionManager__CheckDefenseCheat
     ONETIMEPATCH(ENCRYPTOFFSET("0x23C8C9C"),
                  PATCH_RET1) // SkyNet__IsRealApp
}

void Initialize()
{ //[menu setFrameworkName:EXCUTABLENAME];
     while (!InstallHooks())
     {
     } // 在这里拿到UnityFramework基地址，确保加载过了
     patch_at_start();
}