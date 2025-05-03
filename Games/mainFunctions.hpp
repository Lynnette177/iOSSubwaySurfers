#pragma once
#include "GameStructs.h"
#include "offsets.hpp"
#include <cstdint>
#include <vector>

inline bool UVector3toScreenPos(UnityEngine_Vector3_o in, float ScreenHeight,
                                ImVec2 &out) {
  if (in.fields.z < -0.0001)
    return false;
  in.fields.x /= Config::screenScale;
  out.x = in.fields.x;
  out.y = (ScreenHeight - in.fields.y) / Config::screenScale;
  return true;
}
class Entity {
public:
  uintptr_t address;
  int32_t playerID;
  int32_t characterID;
  System_String_o *name;
  System_String_o *UID;
  UnityEngine_Vector3_o GamePosition;
  UnityEngine_Vector3_o TransformPosition;
  bool isAI;
};
inline void* local_entity_address = 0;
inline uintptr_t local_entity_field_address = 0;
inline std::vector<Entity> Entities;
inline void mainFunction() {
  local_entity_address = GameFunction::SYBO_Subway_Characters_Character__get_Instance(NULL);
  local_entity_field_address = ((uintptr_t)local_entity_address + 0x10);
  Entities = {};
  void *DummyManager = GameFunction::DummyMgr__get_Instance(NULL);
  if (DummyManager) {
    //debug_log(@"DummyManager: %p", DummyManager);
    auto DummyDict = GameFunction::DummyMgr__get_allDummy(DummyManager, NULL);
    if (DummyDict) {
      std::vector<uint64_t> dummies = getAllDummy(DummyDict);
      //debug_log(@"Got entities:%d", dummies.size());
      for (int i = 0; i < dummies.size(); i++) {
        Entity temp_entity;
        temp_entity.address = dummies[i];
        temp_entity.playerID = RPM<int32_t>(temp_entity.address +
                                            structoffset_DummyFields_PlayerID);
        temp_entity.characterID = RPM<int32_t>(
            temp_entity.address + structoffset_DummyFields_CharacterID);
        temp_entity.GamePosition = RPM<UnityEngine_Vector3_o>(
            temp_entity.address + structoffset_DummyFields_gamePosition);
        temp_entity.TransformPosition = RPM<UnityEngine_Vector3_o>(
            temp_entity.address + structoffset_DummyFields_transformPosition);
        temp_entity.name = RPM<System_String_o *>(
            (uint64_t)temp_entity.address + structoffset_DummyFields_name);
        temp_entity.UID = RPM<System_String_o *>((uint64_t)temp_entity.address +
                                                 structoffset_DummyFields_UID);
        temp_entity.isAI = RPM<bool>((uint64_t)temp_entity.address +
                                     structoffset_DummyFields_isAIMode);
        // debug_log(@"UID: %s", temp_entity.UID->get_utf8_string().c_str());
        Entities.push_back(temp_entity);
      }
      /*
      PhotonPlayer_array *PhotonArray_ptr =
          GameFunction::PhotonNetwork__get_otherPlayers(NULL);
      PhotonPlayer_array PhotonArray = *PhotonArray_ptr;
      debug_log(@"Photon Player Count:%d", PhotonArray.max_length);
      for (int i = 0; i < PhotonArray.max_length; i++) {
        PhotonPlayer_o *PhotonPlayer = PhotonArray.m_Items[i];
        if (PhotonPlayer) {
          debug_log(@"PhotonPlayer Address: %p", PhotonPlayer);
          int32_t PID = GameFunction::PhotonPlayer__get_ID(PhotonPlayer, NULL);
          System_String_o *UID_ptr =
              GameFunction::PhotonPlayer__get_UserId(PhotonPlayer, NULL);
          System_String_o UID = *UID_ptr;
          debug_log(@"PID:%d UID:%s", PID, UID.get_utf8_string().c_str());
          GameFunction::NetDirector__PostRoom_EndGame(0.0, PID, UID_ptr, 0,
                                                      NULL);
        }
      }
        */
    }
  }
}