#pragma once
#include "GameStructs.h"
#include "offsets.hpp"
#include <cstdint>
#include <vector>
template <typename WPMType> inline bool WPM(uintptr_t Address, WPMType Buffer) {
  if (!Address) {
    return false;
  }
  *(WPMType *)Address = Buffer;
  return true;
}
template <typename RPMType> inline RPMType RPM(uintptr_t Address) {
  RPMType Buffer = RPMType(); // Initialize Buffer to a default value
  if (!Address) {
    return Buffer;
  }
  Buffer = *(RPMType *)Address;
  return Buffer;
}
inline bool UVector3toScreenPos(UnityEngine_Vector3_o in, float ScreenHeight,
                                ImVec2 &out) {
  if (in.fields.z < -0.0001)
    return false;
  in.fields.x /= Config::screenScale;
  out.x = in.fields.x;
  out.y = (ScreenHeight - in.fields.y)/ Config::screenScale;
  return true;
}
class Entity {
public:
  uintptr_t address;
  int32_t playerID;
  int32_t characterID;
  System_String_o *name;
  UnityEngine_Vector3_o GamePosition;
  UnityEngine_Vector3_o TransformPosition;
};
inline std::vector<Entity> Entities;
inline void mainFunction() {
  Entities = {};
  void *DummyManager = GameFunction::DummyMgr__get_Instance(NULL);
  if (DummyManager) {
    debug_log(@"DummyManager: %p", DummyManager);
    auto DummyDict = GameFunction::DummyMgr__get_allDummy(DummyManager, NULL);
    if (DummyDict) {
      std::vector<uint64_t> dummies = getAllDummy(DummyDict);
      debug_log(@"Got entities:%d", dummies.size());
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
        Entities.push_back(temp_entity);
      }
    }
  }
}