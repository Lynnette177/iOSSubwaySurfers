#pragma once
#include "../Config/Config.h"
#import "../Utils/Macros.h"
#include "GameStructs.h"
#include <__config>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

#define offset_SuperRunVIPManager__IsActive ENCRYPTOFFSET("0x24BB334")
#define offset_IDreamSky_BagManager$$IsUnlockedCharacter                       \
  ENCRYPTOFFSET("0x3065DF8")
#define offset_PlayerInfo__isHoverboardUnlockedm ENCRYPTOFFSET("0x1FBF558")
#define offset_IDreamSky_BagManager__IsUnlockedCharacterTheme                  \
  ENCRYPTOFFSET("0x30660F8")
#define offset_CharacterStickerManager__isCharacterUnlocked                    \
  ENCRYPTOFFSET("0x250D6D0")
#define offset_PlayerInfo__IsOrnamentUnlocked ENCRYPTOFFSET("0x1FE5018")
#define offset_HPFXBase___DefenseCheck ENCRYPTOFFSET("0x2F4BD4C")
#define offset_SubwayAdManager__VideoFailed ENCRYPTOFFSET("0x24AE11C")
#define offset_SYBO_Subway_Utilities_DebugSettings__get_IsAllowed              \
  ENCRYPTOFFSET("0x2342988")
#define offset_SYBO_Subway_Utilities_DebugSettings__get_CharacterInvincible    \
  ENCRYPTOFFSET("0x2342B74")
#define offset_AntiAddictionManager_HasVerifid ENCRYPTOFFSET("0x2EA0058")
#define offset_ReportPlayerManager__CanReportPlayer ENCRYPTOFFSET("0x2142CD0")
#define offset_ReportPlayerManager__ReportPlayerManager__CanShowReportPlayer   \
  ENCRYPTOFFSET("0x2142DD8")
#define offset_PlayerInfo__get_ReportPlayerDayTimes ENCRYPTOFFSET("0x1FF19E0")

#define hookFunctionAddress_PlayerInfo__set_amountOfCoins_Address              \
  ENCRYPTOFFSET("0x1FABA74")
#define hookFunctionAddress_PlayerInfo__set_amountOfKeys_Address               \
  ENCRYPTOFFSET("0x1FABD88")
#define hookFunctionAddress_GameStats__set_score_Address                       \
  ENCRYPTOFFSET("0x2EF197C")
#define hookFunctionAddress_HPowerupEnergy___TriggerIn_Address                 \
  ENCRYPTOFFSET("0x2F6B370")
#define hookFunctionAddress_HCharSpeed___ChangeState_Address                   \
  ENCRYPTOFFSET("0x2F348D8")
#define hookFunctionAddress_HCharSpeed__get_speed ENCRYPTOFFSET("0x2F3451C")
#define hookFunctionAddress_CharacterModel__GetScale_Address                   \
  ENCRYPTOFFSET("0x22bd2bc")
#define hookFunctionAddress_UnityEngine_Transform__set_position_Address        \
  ENCRYPTOFFSET("0x435722C")
#define hookFunctionAddress_HRealPVPRoomManager__CommitGameChat_Address        \
  ENCRYPTOFFSET("0x2F8C5DC")
#define hookFunctionAddress_SYBO_Subway_Characters_Character__ApplyGravity     \
  ENCRYPTOFFSET("0x224154C")
#define hookFunctionAddress_PlayerInfo__get_playerNickName                     \
  ENCRYPTOFFSET("0x1FC77D8")
#define hookFunctionAddress_ReportPlayerManager__ReportPlayer                  \
  ENCRYPTOFFSET("0x2142A20")
#define hookFunctionAddress_RealPVPManager__get_allRank                        \
  ENCRYPTOFFSET("0x1F52D2C")
#define hookFunctionAddress_PartyPvpManager__get_allRank                       \
  ENCRYPTOFFSET("0x20BFF90")

namespace FunctionAddress {
inline uintptr_t HPowerupManager__get_instance_funcaddr = 0x2F5747C;
inline uintptr_t HPowerupManager__IncEnergy_funcaddr = 0x2F6B8F4;
inline uintptr_t PlayerInfo__set_NewTreasureKey_funcaddr = 0x1fec5f8;
inline uintptr_t SYBO_Subway_Characters_Character__get_Instance_Addr =
    0x2235eb4;
inline uintptr_t UnityEngine_Camera__get_main_funcaddr = 0x430BC54;
inline uintptr_t UnityEngine_Camera__WorldToScreenPoint_addr = 0x430ADD4;
inline uintptr_t DummyMgr__get_allDummy_addr = 0x2DED138;
inline uintptr_t DummyMgr__get_Instance_addr = 0x2DECF78;
inline void initFunctionAddress(uintptr_t base) {
  HPowerupManager__IncEnergy_funcaddr += base;
  HPowerupManager__get_instance_funcaddr += base;
  PlayerInfo__set_NewTreasureKey_funcaddr += base;
  SYBO_Subway_Characters_Character__get_Instance_Addr += base;
  UnityEngine_Camera__get_main_funcaddr += base;
  UnityEngine_Camera__WorldToScreenPoint_addr += base;
  DummyMgr__get_Instance_addr += base;
  DummyMgr__get_allDummy_addr += base;
}
} // namespace FunctionAddress

#define PATCH_RET ENCRYPTHEX("C0 03 5F D6")
#define PATCH_RET0 ENCRYPTHEX("00 00 80 D2 C0 03 5F D6")
#define PATCH_RET1 ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
#define PATCH_FROM_FAILED_TO_FINSH_ADS                                         \
  ENCRYPTHEX("C8 FF FF 17") // 这里是跳转到finish的位置

namespace GameFunction {
inline void *(*HPowerupManager__get_instance)(void *method);
inline void (*HPowerupManager__IncEnergy)(void *_this, void *method);
inline void (*PlayerInfo__set_NewTreasureKey)(void *_this, int32_t value,
                                              void *method);
inline void *(*SYBO_Subway_Characters_Character__get_Instance)(
    void *method); // SYBO_Subway_Characters_Character_o
inline void *(*UnityEngine_Camera__get_main)(void *method);
inline UnityEngine_Vector3_o (*UnityEngine_Camera__WorldToScreenPoint)(
    void *_this, // UnityEngine_Camera_o
    UnityEngine_Vector3_o position, int32_t eye, void *method);
inline void *(*DummyMgr__get_Instance)(void *method);
inline System_Collections_Generic_Dictionary_int__Dummy__o *(
    *DummyMgr__get_allDummy)(void *_this, void *method);
inline UnityEngine_Vector3_o (
    *SYBO_Subway_Characters_CharacterBase__get_WorldBodyCenterPosition)(
    void *_this, // SYBO_Subway_Characters_CharacterBase_o
    void *method);
;

inline void initFunctions() {
  HPowerupManager__get_instance =
      reinterpret_cast<decltype(HPowerupManager__get_instance)>(
          FunctionAddress::HPowerupManager__get_instance_funcaddr);
  HPowerupManager__IncEnergy =
      reinterpret_cast<decltype(HPowerupManager__IncEnergy)>(
          FunctionAddress::HPowerupManager__IncEnergy_funcaddr);
  PlayerInfo__set_NewTreasureKey =
      reinterpret_cast<decltype(PlayerInfo__set_NewTreasureKey)>(
          FunctionAddress::PlayerInfo__set_NewTreasureKey_funcaddr);
  SYBO_Subway_Characters_Character__get_Instance = reinterpret_cast<
      decltype(SYBO_Subway_Characters_Character__get_Instance)>(
      FunctionAddress::SYBO_Subway_Characters_Character__get_Instance_Addr);
  UnityEngine_Camera__get_main =
      reinterpret_cast<decltype(UnityEngine_Camera__get_main)>(
          FunctionAddress::UnityEngine_Camera__get_main_funcaddr);
  UnityEngine_Camera__WorldToScreenPoint =
      reinterpret_cast<decltype(UnityEngine_Camera__WorldToScreenPoint)>(
          FunctionAddress::UnityEngine_Camera__WorldToScreenPoint_addr);
  DummyMgr__get_Instance = reinterpret_cast<decltype(DummyMgr__get_Instance)>(
      FunctionAddress::DummyMgr__get_Instance_addr);
  DummyMgr__get_allDummy = reinterpret_cast<decltype(DummyMgr__get_allDummy)>(
      FunctionAddress::DummyMgr__get_allDummy_addr);
}
} // namespace GameFunction

namespace CustomFunctions {
inline void addHoverboardEnergy() {
  void *HPowerupManager = GameFunction::HPowerupManager__get_instance(0);
  if (HPowerupManager)
    GameFunction::HPowerupManager__IncEnergy(HPowerupManager, 0);
}
inline void setNewTreasureKey(void *PlayerInfoInstance, int32_t value) {
  GameFunction::PlayerInfo__set_NewTreasureKey(PlayerInfoInstance, value, 0);
}
} // namespace CustomFunctions

namespace hooks {
inline void (*org_PlayerInfo__set_amountOfCoins)(void *_this, int32_t value,
                                                 void *method);
inline void new_PlayerInfo__set_amountOfCoins(void *_this, int32_t value,
                                              void *method) {
  if (Config::修改金币) {
    value = Config::修改成多少金币;
  }
  org_PlayerInfo__set_amountOfCoins(_this, value, method);
  if (Config::修改宝物钥匙) {
    int32_t TreasureKeyvalue = Config::修改成多少宝物钥匙;
    CustomFunctions::setNewTreasureKey(_this, TreasureKeyvalue);
  }
}
inline void (*org_PlayerInfo__set_amountOfKeys)(void *_this, int32_t value,
                                                void *method);
inline void new_PlayerInfo__set_amountOfKeys(void *_this, int32_t value,
                                             void *method) {
  if (Config::修改钥匙) {
    value = Config::修改成多少钥匙;
  }
  org_PlayerInfo__set_amountOfKeys(_this, value, method);
}
inline void (*org_GameStats__set_score)(void *_this, int32_t value,
                                        void *method);
inline void new_GameStats__set_score(void *_this, int32_t value, void *method) {
  if (Config::修改分数) {
    value = Config::修改成多少分;
  }
  org_GameStats__set_score(_this, value, method);
}

inline void (*org_HPowerupEnergy___TriggerIn)(void *_this, void *method);
inline void new_HPowerupEnergy___TriggerIn(void *_this, void *method) {
  org_HPowerupEnergy___TriggerIn(_this, method);
  if (Config::双倍充能) {
    CustomFunctions::addHoverboardEnergy();
  }
}

inline void (*org_HCharSpeed___ChangeState)(void *_this, uint8_t state,
                                            float bumpSpeedLossPercentage,
                                            int32_t accLevel, bool forceChange,
                                            void *method);
inline void new_HCharSpeed___ChangeState(void *_this, uint8_t state,
                                         float bumpSpeedLossPercentage,
                                         int32_t accLevel, bool forceChange,
                                         void *method) {
  if (Config::疯狂加速) {
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
inline float (*org_HCharSpeed__get_speed)(void *_this, void *method);
inline float new_HCharSpeed__get_speed(void *_this, void *method) {
  float result = org_HCharSpeed__get_speed(_this, method);
  if (Config::修改速度) {
    if (result < Config::速度修改为)
      result = Config::速度修改为;
  }
  return result;
}
inline UnityEngine_Vector3_o (*org_CharacterModel__GetScale)(
    void *_this, int32_t characterType, void *method);
inline UnityEngine_Vector3_o
new_CharacterModel__GetScale(void *_this, int32_t characterType, void *method) {
  auto result = org_CharacterModel__GetScale(_this, characterType, method);
  if (Config::修改模型大小) {
    float value = Config::模型大小倍率;
    result.fields.x *= value;
    result.fields.y *= value;
    result.fields.z *= value;
  }
  return result;
}

inline void (*org_UnityEngine_Transform__set_position)(
    void *_this, // UnityEngine_Transform_o
    UnityEngine_Vector3_o value, void *method);

inline void
new_UnityEngine_Transform__set_position(void *_this, // UnityEngine_Transform_o
                                        UnityEngine_Vector3_o value,
                                        void *method) {
  if (Config::上帝视角) {
    value.fields.y = 100;
  }
  org_UnityEngine_Transform__set_position(_this, value, method);
}
inline System_String_o newcontent;
inline void (*org_HRealPVPRoomManager__CommitGameChat)(
    void *_this, // HRealPVPRoomManager_o
    int32_t chatType, int32_t chatId, System_String_o *content, void *method);
inline void new_HRealPVPRoomManager__CommitGameChat(
    void *_this, // HRealPVPRoomManager_o
    int32_t chatType, int32_t chatId, System_String_o *content, void *method) {
  if (Config::自定义消息内容) {
    chatType = 3;
    chatId = 0;
    newcontent = *content;
    newcontent.set_utf8_to_this(Config::要发送的消息内容);
    org_HRealPVPRoomManager__CommitGameChat(_this, chatType, chatId,
                                            &newcontent, method);
  } else {
    org_HRealPVPRoomManager__CommitGameChat(_this, chatType, chatId, content,
                                            method);
  }
}

inline void (*org_SYBO_Subway_Characters_Character__ApplyGravity)(void *_this,
                                                                  void *method);
inline void new_SYBO_Subway_Characters_Character__ApplyGravity(void *_this,
                                                               void *method) {
  //_this是SYBO_Subway_Characters_Character_o*
  if (Config::修改重力)
    *(float *)((uintptr_t)_this + 0x10 + structoffset_DummyFields_gravity) =
        Config::重力修改为;
  org_SYBO_Subway_Characters_Character__ApplyGravity(_this, method);
}
inline System_String_o newNickname;
inline System_String_o *(*org_PlayerInfo__get_playerNickName)(
    void *_this, // PlayerInfo_o*
    void *method);
inline System_String_o *
new_PlayerInfo__get_playerNickName(void *_this, // RealPVPManager_o
                                   void *method) {
  System_String_o *result = org_PlayerInfo__get_playerNickName(_this, method);
  if (Config::修改昵称) {
    newNickname = *result;
    newNickname.set_utf8_to_this(Config::修改昵称为);
    return &newNickname;
  }
  return result;
}

inline void (*org_ReportPlayerManager__ReportPlayer)(
    void *_this, // ReportPlayerManager_o
    System_String_o *playerId,
    void *reasonTypes, // System_String_array
    System_String_o *fightId, int32_t matchType, void *method);
inline void
new_ReportPlayerManager__ReportPlayer(void *_this, // ReportPlayerManager_o
                                      System_String_o *playerId,
                                      void *reasonTypes, // System_String_array
                                      System_String_o *fightId,
                                      int32_t matchType, void *method) {
  if (Config::十倍举报) {
    for (int i = 0; i < 10; i++) {
      org_ReportPlayerManager__ReportPlayer(_this, playerId, reasonTypes,
                                            fightId, matchType, method);
    }
  } else {
    org_ReportPlayerManager__ReportPlayer(_this, playerId, reasonTypes, fightId,
                                          matchType, method);
  }
}

inline int32_t (*org_PartyPvpManager__get_allRank)(
    void *_this, // PartyPvpManager_o
    void *method);
inline int32_t
new_PartyPvpManager__get_allRank(void *_this, // PartyPvpManager_o
                                 void *method) {
  int32_t result = org_PartyPvpManager__get_allRank(_this, method);
  if (Config::修改排名) {
    return Config::修改排名为;
  }
  return result;
}

inline int32_t (*org_RealPVPManager__get_allRank)(
  void *_this, // PartyPvpManager_o
  void *method);
inline int32_t
new_RealPVPManager__get_allRank(void *_this, // PartyPvpManager_o
                               void *method) {
int32_t result = org_RealPVPManager__get_allRank(_this, method);
if (Config::修改排名) {
  return Config::修改排名为;
}
return result;
}

} // namespace hooks