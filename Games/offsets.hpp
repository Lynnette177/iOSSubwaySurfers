#pragma once
#include "../Config/Config.h"
#import "../Utils/Macros.h"
#include "GameStructs.h"
#include <__config>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>

#define offset_SuperRunVIPManager__IsActive ENCRYPTOFFSET("0x24AA26C")
#define offset_IDreamSky_BagManager$$IsUnlockedCharacter \
  ENCRYPTOFFSET("0x3093FBC")
#define offset_PlayerInfo__isHoverboardUnlockedm ENCRYPTOFFSET("0x1F7610C")
#define offset_IDreamSky_BagManager__IsUnlockedCharacterTheme \
  ENCRYPTOFFSET("0x30942BC")
#define offset_CharacterStickerManager__isCharacterUnlocked \
  ENCRYPTOFFSET("0x257AD74")
#define offset_PlayerInfo__IsOrnamentUnlocked ENCRYPTOFFSET("0x1F9B740")
#define offset_HPFXBase___DefenseCheck ENCRYPTOFFSET("0x2F6D7D4")
#define offset_SubwayAdManager__VideoFailed ENCRYPTOFFSET("0x249D030")
#define offset_SYBO_Subway_Utilities_DebugSettings__get_IsAllowed \
  ENCRYPTOFFSET("0x230028C")
#define offset_SYBO_Subway_Utilities_DebugSettings__get_CharacterInvincible \
  ENCRYPTOFFSET("0x2300478")
#define offset_AntiAddictionManager_HasVerifid ENCRYPTOFFSET("0x2E91898")
#define offset_ReportPlayerManager__CanReportPlayer ENCRYPTOFFSET("0x21018FC")
#define offset_ReportPlayerManager__ReportPlayerManager__CanShowReportPlayer \
  ENCRYPTOFFSET("0x2101A04")
#define offset_PlayerInfo__get_ReportPlayerDayTimes ENCRYPTOFFSET("0x1FA811C")
#define offset_SYBO_Subway_Characters_CharacterBase__AllowDoubleJump \
  ENCRYPTOFFSET("0x2207844")
#define offset_DummyMgr__GetNearestFrontDummy_BAWAY ENCRYPTOFFSET("0x2DFFA28")
//把这个找前方最近的重定向到找最靠前的
#define offset_DummyMgr__GetFrontestDummy_CSEL ENCRYPTOFFSET("0x2DFFEB8")
//最靠前的被patch成不管本地玩家，就找最前的

#define hookFunctionAddress_NetDirector__Rule_ReqItemByServer ENCRYPTOFFSET("0x34C5560")
#define hookFunctionAddress_PlayerInfo__set_amountOfCoins_Address \
  ENCRYPTOFFSET("0x1F626F8")
#define hookFunctionAddress_PlayerInfo__set_amountOfKeys_Address \
  ENCRYPTOFFSET("0x1F62A0C")
#define hookFunctionAddress_GameStats__set_score_Address \
  ENCRYPTOFFSET("0x2F11200")
#define hookFunctionAddress_HPowerupEnergy___TriggerIn_Address \
  ENCRYPTOFFSET("0x2F8FD08")
#define hookFunctionAddress_HCharSpeed___ChangeState_Address \
  ENCRYPTOFFSET("0x2F56010")
#define hookFunctionAddress_HCharSpeed__get_speed ENCRYPTOFFSET("0x2F559C4")
#define hookFunctionAddress_CharacterModel__GetScale_Address \
  ENCRYPTOFFSET("0x232B79C")
#define hookFunctionAddress_SYBO_Subway_Cameras_CameraData__get_CameraPositionOffset \
  ENCRYPTOFFSET("0x21DA884")
#define hookFunctionAddress_HRealPVPRoomManager__CommitGameChat_Address \
  ENCRYPTOFFSET("0x2FB30D8")
#define hookFunctionAddress_SYBO_Subway_Characters_Character__ApplyGravity \
  ENCRYPTOFFSET("0x21FD970")
#define hookFunctionAddress_PlayerInfo__get_playerNickName \
  ENCRYPTOFFSET("0x1F7E3CC")
#define hookFunctionAddress_ReportPlayerManager__ReportPlayer \
  ENCRYPTOFFSET("0x210164C")
#define hookFunctionAddress_RealPVPManager__get_allRank \
  ENCRYPTOFFSET("0x207BEB8")
#define hookFunctionAddress_PartyPvpManager__get_allRank \
  ENCRYPTOFFSET("0x1F0956C")
#define hookFunctionAddress_EncrptUtil__AESEncrypt ENCRYPTOFFSET("0x2E0BF28")

namespace FunctionAddress
{
  inline uintptr_t HPowerupManager__get_instance_funcaddr = 0x2F90304;
  inline uintptr_t HPowerupManager__IncEnergy_funcaddr = 0x2F903A4;
  inline uintptr_t HPowerupManager__CanReleaseEnergy_addr = 0x2F949B8;
  inline uintptr_t HPowerupManager__ReleaseEnergy_addr = 0x2F94AE4;

  inline uintptr_t PlayerInfo__set_NewTreasureKey_funcaddr = 0x1FA2D10;
  inline uintptr_t SYBO_Subway_Characters_Character__get_Instance_Addr =
      0x21F22EC;
  inline uintptr_t SYBO_Subway_Characters_CharacterBase__get_runningTime_addr =
      0x2203CC8;
  inline uintptr_t UnityEngine_Camera__get_main_funcaddr = 0x433A618;
  inline uintptr_t UnityEngine_Camera__WorldToScreenPoint_addr = 0x4339798;
  inline uintptr_t DummyMgr__get_allDummy_addr = 0x2DF97E0;
  inline uintptr_t DummyMgr__get_Instance_addr = 0x2DF9620;
  inline uintptr_t PhotonNetwork__get_otherPlayers_addr = 0x1F2B128;
  inline uintptr_t PhotonPlayer__get_ID_addr = 0x1F2CA64;
  inline uintptr_t PhotonPlayer__get_UserId_addr = 0x1F36C0C;
  inline uintptr_t NetDirector__PostRoom_EndGame_addr = 0x34CB72C;
  inline uintptr_t OnlineSettings__get_instance = 0x357CDB4;
  inline uintptr_t OnlineSettings__get_RealPvpCheatTime_addr = 0x358B884;
  inline uintptr_t PVPModuleMgr__get_Instance_addr = 0x1EC1AEC;
  inline uintptr_t PVPModuleMgr__get_ROUTE_LEGNGTH_addr = 0x1EC1A44;
  inline uintptr_t BindWeChatManager__get_Instance_addr = 0x334C28C;

  inline void initFunctionAddress(uintptr_t base)
  {
    HPowerupManager__IncEnergy_funcaddr += base;
    HPowerupManager__get_instance_funcaddr += base;
    HPowerupManager__CanReleaseEnergy_addr += base;
    HPowerupManager__ReleaseEnergy_addr += base;

    PlayerInfo__set_NewTreasureKey_funcaddr += base;
    SYBO_Subway_Characters_Character__get_Instance_Addr += base;
    SYBO_Subway_Characters_CharacterBase__get_runningTime_addr += base;
    UnityEngine_Camera__get_main_funcaddr += base;
    UnityEngine_Camera__WorldToScreenPoint_addr += base;
    DummyMgr__get_Instance_addr += base;
    DummyMgr__get_allDummy_addr += base;
    PhotonNetwork__get_otherPlayers_addr += base;
    PhotonPlayer__get_ID_addr += base;
    PhotonPlayer__get_UserId_addr += base;
    NetDirector__PostRoom_EndGame_addr += base;
    OnlineSettings__get_instance += base;
    OnlineSettings__get_RealPvpCheatTime_addr += base;
    PVPModuleMgr__get_Instance_addr += base;
    PVPModuleMgr__get_ROUTE_LEGNGTH_addr += base;
    BindWeChatManager__get_Instance_addr += base;
  }
} // namespace FunctionAddress

#define PATCH_RET ENCRYPTHEX("C0 03 5F D6")
#define PATCH_RET0 ENCRYPTHEX("00 00 80 D2 C0 03 5F D6")
#define PATCH_RET1 ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
#define PATCH_FROM_FAILED_TO_FINSH_ADS \
  ENCRYPTHEX("C8 FF FF 17") // 这里是跳转到finish的位置
#define PATCH_NOP ENCRYPTHEX("1F 20 03 D5")
#define PATCH_MOV_X0_X20 ENCRYPTHEX("E0 03 14 AA")
#define PATCH_BFROMNEARTOFRONTEST ENCRYPTHEX("C4 00 00 14")

namespace GameFunction
{
  inline void *(*HPowerupManager__get_instance)(void *method);
  inline void (*HPowerupManager__IncEnergy)(void *_this, void *method);
  inline void (*PlayerInfo__set_NewTreasureKey)(void *_this, int32_t value,
                                                void *method);
  inline bool (*HPowerupManager__CanReleaseEnergy)(
      void *_this /*HPowerupManager_o **/, void *method);
  inline void (*HPowerupManager__ReleaseEnergy)(
      void *_this /*HPowerupManager_o **/, void *method);

  inline void *(*SYBO_Subway_Characters_Character__get_Instance)(
      void *method); // SYBO_Subway_Characters_Character_o
  inline float (*SYBO_Subway_Characters_CharacterBase__get_runningTime)(
      void *_this, // SYBO_Subway_Characters_CharacterBase_o
      void *method);

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
  inline PhotonPlayer_array *(*PhotonNetwork__get_otherPlayers)(void *method);
  inline int32_t (*PhotonPlayer__get_ID)(PhotonPlayer_o *_this, void *method);
  inline System_String_o *(*PhotonPlayer__get_UserId)(PhotonPlayer_o *_this,
                                                      void *method);
  inline void (*NetDirector__PostRoom_EndGame)(double delaySecond,
                                               int32_t playerID,
                                               System_String_o *uid, bool endLine,
                                               void *method);
  inline void *(*OnlineSettings__get_instance)(
      void *method); // 返回OnlineSettings_o *
  inline int32_t (*OnlineSettings__get_RealPvpCheatTime)(
      void *_this /*OnlineSettings_o* */, void *method);

  inline void *(*PVPModuleMgr__get_Instance)(void *method); // PVPModuleMgr_o *
  inline float (*PVPModuleMgr__get_ROUTE_LEGNGTH)(void *method);

  inline void * /*BindWeChatManager_o **/ (*BindWeChatManager__get_Instance)(
      void *method);

  inline void initFunctions()
  {
    HPowerupManager__get_instance =
        reinterpret_cast<decltype(HPowerupManager__get_instance)>(
            FunctionAddress::HPowerupManager__get_instance_funcaddr);
    HPowerupManager__IncEnergy =
        reinterpret_cast<decltype(HPowerupManager__IncEnergy)>(
            FunctionAddress::HPowerupManager__IncEnergy_funcaddr);
    HPowerupManager__CanReleaseEnergy =
        reinterpret_cast<decltype(HPowerupManager__CanReleaseEnergy)>(
            FunctionAddress::HPowerupManager__CanReleaseEnergy_addr);
    HPowerupManager__ReleaseEnergy =
        reinterpret_cast<decltype(HPowerupManager__ReleaseEnergy)>(
            FunctionAddress::HPowerupManager__ReleaseEnergy_addr);

    PlayerInfo__set_NewTreasureKey =
        reinterpret_cast<decltype(PlayerInfo__set_NewTreasureKey)>(
            FunctionAddress::PlayerInfo__set_NewTreasureKey_funcaddr);

    SYBO_Subway_Characters_Character__get_Instance = reinterpret_cast<
        decltype(SYBO_Subway_Characters_Character__get_Instance)>(
        FunctionAddress::SYBO_Subway_Characters_Character__get_Instance_Addr);
    SYBO_Subway_Characters_CharacterBase__get_runningTime = reinterpret_cast<
        decltype(SYBO_Subway_Characters_CharacterBase__get_runningTime)>(
        FunctionAddress::
            SYBO_Subway_Characters_CharacterBase__get_runningTime_addr);

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
    PhotonNetwork__get_otherPlayers =
        reinterpret_cast<decltype(PhotonNetwork__get_otherPlayers)>(
            FunctionAddress::PhotonNetwork__get_otherPlayers_addr);
    PhotonPlayer__get_ID = reinterpret_cast<decltype(PhotonPlayer__get_ID)>(
        FunctionAddress::PhotonPlayer__get_ID_addr);
    PhotonPlayer__get_UserId =
        reinterpret_cast<decltype(PhotonPlayer__get_UserId)>(
            FunctionAddress::PhotonPlayer__get_UserId_addr);
    NetDirector__PostRoom_EndGame =
        reinterpret_cast<decltype(NetDirector__PostRoom_EndGame)>(
            FunctionAddress::NetDirector__PostRoom_EndGame_addr);
    OnlineSettings__get_instance =
        reinterpret_cast<decltype(OnlineSettings__get_instance)>(
            FunctionAddress::OnlineSettings__get_instance);
    OnlineSettings__get_RealPvpCheatTime =
        reinterpret_cast<decltype(OnlineSettings__get_RealPvpCheatTime)>(
            FunctionAddress::OnlineSettings__get_RealPvpCheatTime_addr);

    PVPModuleMgr__get_Instance =
        reinterpret_cast<decltype(PVPModuleMgr__get_Instance)>(
            FunctionAddress::PVPModuleMgr__get_Instance_addr);
    PVPModuleMgr__get_ROUTE_LEGNGTH =
        reinterpret_cast<decltype(PVPModuleMgr__get_ROUTE_LEGNGTH)>(
            FunctionAddress::PVPModuleMgr__get_ROUTE_LEGNGTH_addr);
    BindWeChatManager__get_Instance =
        reinterpret_cast<decltype(BindWeChatManager__get_Instance)>(
            FunctionAddress::BindWeChatManager__get_Instance_addr);
  }
} // namespace GameFunction

namespace CustomFunctions
{
  inline void addHoverboardEnergy()
  {
    void *HPowerupManager = GameFunction::HPowerupManager__get_instance(0);
    if (HPowerupManager)
      GameFunction::HPowerupManager__IncEnergy(HPowerupManager, 0);
  }
  inline void setNewTreasureKey(void *PlayerInfoInstance, int32_t value)
  {
    GameFunction::PlayerInfo__set_NewTreasureKey(PlayerInfoInstance, value, 0);
  }
  inline int32_t get_min_pvp_time()
  {
    void *OnlineSettings = GameFunction::OnlineSettings__get_instance(NULL);
    if (!OnlineSettings)
      return 0;
    int32_t result =
        GameFunction::OnlineSettings__get_RealPvpCheatTime(OnlineSettings, NULL);
    return result;
  }
  inline int getCheatStatus()
  {
    auto BindWechatManager = GameFunction::BindWeChatManager__get_Instance(NULL);
    if (!BindWechatManager)
      return 0;
    uintptr_t BindWechatManager_fields = (uintptr_t)BindWechatManager + 0x10;
    bool loginShield =
        RPM<bool>(BindWechatManager_fields +
                  structOffset_BindWeChatManager_fields_loginshield);
    bool payShield = RPM<bool>(BindWechatManager_fields +
                               structOffset_BindWeChatManager_fields_payshield);
    return (payShield << 1) | loginShield;
  }
  inline void check_and_user_hoverboard_pvp()
  {
    void *HPowerupManager = GameFunction::HPowerupManager__get_instance(NULL);
    bool canuse =
        GameFunction::HPowerupManager__CanReleaseEnergy(HPowerupManager, NULL);
    if (canuse)
    {
      GameFunction::HPowerupManager__ReleaseEnergy(HPowerupManager, NULL);
    }
  }
} // namespace CustomFunctions

namespace hooks
{
  inline void (*org_PlayerInfo__set_amountOfCoins)(void *_this, int32_t value,
                                                   void *method);
  inline void new_PlayerInfo__set_amountOfCoins(void *_this, int32_t value,
                                                void *method)
  {
    if (Config::修改金币)
    {
      value = Config::修改成多少金币;
    }
    org_PlayerInfo__set_amountOfCoins(_this, value, method);
    if (Config::修改宝物钥匙)
    {
      int32_t TreasureKeyvalue = Config::修改成多少宝物钥匙;
      CustomFunctions::setNewTreasureKey(_this, TreasureKeyvalue);
    }
  }
  inline void (*org_PlayerInfo__set_amountOfKeys)(void *_this, int32_t value,
                                                  void *method);
  inline void new_PlayerInfo__set_amountOfKeys(void *_this, int32_t value,
                                               void *method)
  {
    if (Config::修改钥匙)
    {
      value = Config::修改成多少钥匙;
    }
    org_PlayerInfo__set_amountOfKeys(_this, value, method);
  }
  inline void (*org_GameStats__set_score)(void *_this, int32_t value,
                                          void *method);
  inline void new_GameStats__set_score(void *_this, int32_t value, void *method)
  {
    if (Config::修改分数)
    {
      value = Config::修改成多少分;
    }
    org_GameStats__set_score(_this, value, method);
  }

  inline void (*org_HPowerupEnergy___TriggerIn)(void *_this, void *method);
  inline void new_HPowerupEnergy___TriggerIn(void *_this, void *method)
  {
    org_HPowerupEnergy___TriggerIn(_this, method);
    if (Config::双倍充能)
    {
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
                                           void *method)
  {
    if (Config::疯狂加速)
    {
      accLevel = 3;
      if (state == 3LL || bumpSpeedLossPercentage != 0.0)
      {
        state = 2;
        bumpSpeedLossPercentage = 0.0;
        forceChange = 1;
      }
    }
    org_HCharSpeed___ChangeState(_this, state, bumpSpeedLossPercentage, accLevel,
                                 forceChange, method);
  }
  inline float (*org_HCharSpeed__get_speed)(void *_this, void *method);
  inline float new_HCharSpeed__get_speed(void *_this, void *method)
  {
    float result = org_HCharSpeed__get_speed(_this, method);
    if (Config::修改速度)
    {
      if (result < Config::速度修改为)
        result = Config::速度修改为;
    }
    if (Config::防作弊合法化 && Config::正在休眠防作弊)
      result = 0.f;
    return result;
  }
  inline UnityEngine_Vector3_o (*org_CharacterModel__GetScale)(
      void *_this, int32_t characterType, void *method);
  inline UnityEngine_Vector3_o
  new_CharacterModel__GetScale(void *_this, int32_t characterType, void *method)
  {
    auto result = org_CharacterModel__GetScale(_this, characterType, method);
    if (Config::修改模型大小)
    {
      float value = Config::模型大小倍率;
      result.fields.x *= value;
      result.fields.y *= value;
      result.fields.z *= value;
    }
    return result;
  }

  inline UnityEngine_Vector3_o (*org_SYBO_Subway_Cameras_CameraData__get_CameraPositionOffset)(
      SYBO_Subway_Cameras_CharacterCamera_o *_this,
      void *method);
  inline UnityEngine_Vector3_o new_SYBO_Subway_Cameras_CameraData__get_CameraPositionOffset(
      SYBO_Subway_Cameras_CharacterCamera_o *_this,
      void *method)
  {
    auto result = org_SYBO_Subway_Cameras_CameraData__get_CameraPositionOffset(_this, method);
    debug_log(@"CameraOffset: %f %f %f", result.fields.x, result.fields.y, result.fields.z);
    if (Config::上帝视角)
    {
      result.fields.y = 500;
    }
    return result;
  }

  inline System_String_o newcontent;
  inline void (*org_HRealPVPRoomManager__CommitGameChat)(
      void *_this, // HRealPVPRoomManager_o
      int32_t chatType, int32_t chatId, System_String_o *content, void *method);
  inline void new_HRealPVPRoomManager__CommitGameChat(
      void *_this, // HRealPVPRoomManager_o
      int32_t chatType, int32_t chatId, System_String_o *content, void *method)
  {
    if (Config::自定义消息内容)
    {
      chatType = 3;
      chatId = 0;
      newcontent = *content;
      newcontent.set_utf8_to_this(Config::要发送的消息内容);
      org_HRealPVPRoomManager__CommitGameChat(_this, chatType, chatId,
                                              &newcontent, method);
    }
    else
    {
      org_HRealPVPRoomManager__CommitGameChat(_this, chatType, chatId, content,
                                              method);
    }
  }

  inline void (*org_SYBO_Subway_Characters_Character__ApplyGravity)(void *_this,
                                                                    void *method);
  inline void new_SYBO_Subway_Characters_Character__ApplyGravity(void *_this,
                                                                 void *method)
  {
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
                                     void *method)
  {
    System_String_o *result = org_PlayerInfo__get_playerNickName(_this, method);
    if (Config::修改昵称)
    {
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
                                        int32_t matchType, void *method)
  {
    if (Config::十倍举报)
    {
      for (int i = 0; i < 10; i++)
      {
        org_ReportPlayerManager__ReportPlayer(_this, playerId, reasonTypes,
                                              fightId, matchType, method);
      }
    }
    else
    {
      org_ReportPlayerManager__ReportPlayer(_this, playerId, reasonTypes, fightId,
                                            matchType, method);
    }
  }

  inline int32_t (*org_PartyPvpManager__get_allRank)(
      void *_this, // PartyPvpManager_o
      void *method);
  inline int32_t
  new_PartyPvpManager__get_allRank(void *_this, // PartyPvpManager_o
                                   void *method)
  {
    int32_t result = org_PartyPvpManager__get_allRank(_this, method);
    if (Config::修改排名)
    {
      return Config::修改排名为;
    }
    return result;
  }

  inline int32_t (*org_RealPVPManager__get_allRank)(
      void *_this, // PartyPvpManager_o
      void *method);
  inline int32_t new_RealPVPManager__get_allRank(void *_this, // PartyPvpManager_o
                                                 void *method)
  {
    int32_t result = org_RealPVPManager__get_allRank(_this, method);
    if (Config::修改排名)
    {
      return Config::修改排名为;
    }
    return result;
  }
  inline System_String_o *(*org_EncrptUtil__AESEncrypt)(System_String_o *inStr,
                                                        System_String_o *key,
                                                        void *method);
  inline System_String_o *new_EncrptUtil__AESEncrypt(System_String_o *inStr,
                                                     System_String_o *key,
                                                     void *method)
  {
    size_t blockSize = 100;
    std::string result_str = inStr->get_utf8_string();
    size_t length = result_str.length();
    for (size_t i = 0; i < length; i += blockSize)
    {
      std::string block = result_str.substr(i, blockSize);
      debug_log(@"Crypt:InStr:%s", block.c_str());
    }

    debug_log(@"Crypt:AES Key: %s", key->get_utf8_string().c_str());
    return org_EncrptUtil__AESEncrypt(inStr, key, method);
  }
  inline void *(*org_NetDirector__Rule_ReqItemByServer)( // System_Collections_IEnumerator_o
      void *callback,                                    // System_Action_Dictionary_byte__object___o
      System_String_o *userId,
      int32_t rank,
      int32_t index,
      void *method);
  inline void *new_NetDirector__Rule_ReqItemByServer( // System_Collections_IEnumerator_o
      void *callback,                                 // System_Action_Dictionary_byte__object___o
      System_String_o *userId,
      int32_t rank,
      int32_t index,
      void *method)
  {
    if (Config::始终拿好道具)
    {
      rank = 3;
    }
    return org_NetDirector__Rule_ReqItemByServer(callback, userId, rank, index, method);
  }
} // namespace hooks