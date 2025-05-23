#pragma once
#include "../Utils/definations.h"
#include "stdint.h"
#include <cstdint>
#include <string.h>
#include <string>
#include <vector>

#define UnityUnitToGame 0.055

template <typename WPMType>
inline bool WPM(uintptr_t Address, WPMType Buffer)
{
  if (!Address)
  {
    return false;
  }
  *(WPMType *)Address = Buffer;
  return true;
}
template <typename RPMType>
inline RPMType RPM(uintptr_t Address)
{
  RPMType Buffer = RPMType(); // Initialize Buffer to a default value
  if (!Address)
  {
    return Buffer;
  }
  Buffer = *(RPMType *)Address;
  return Buffer;
}

struct UnityEngine_Vector3_Fields
{
  float x;
  float y;
  float z;
};
struct UnityEngine_Vector3_o
{
  UnityEngine_Vector3_Fields fields;
  // 重载减法运算符
  UnityEngine_Vector3_o(float x, float y, float z) : fields{x, y, z} {}
  UnityEngine_Vector3_o() {}
  UnityEngine_Vector3_o operator-(const UnityEngine_Vector3_o &other) const
  {
    UnityEngine_Vector3_o result = *this;
    result.fields.x -= other.fields.x;
    result.fields.y -= other.fields.y;
    result.fields.z -= other.fields.z;
    return result;
  }
  UnityEngine_Vector3_o operator+(const UnityEngine_Vector3_o &other) const
  {
    UnityEngine_Vector3_o result = *this;
    result.fields.x += other.fields.x;
    result.fields.y += other.fields.y;
    result.fields.z += other.fields.z;
    return result;
  }
};

struct SmoothDampFloat_Fields // sizeof=0x10
{                             // XREF: SmoothDampFloat_o/r
  float _target;
  float _smoothTime;
  float _value;
  float valueSpeed;
};
struct SmoothDampFloat_o // sizeof=0x20
{
  void *klass; // SmoothDampFloat_c *
  void *monitor;
  SmoothDampFloat_Fields fields;
};

struct SYBO_Subway_Cameras_CameraData_Fields // sizeof=0x48
{                                            // XREF: SYBO_Subway_Cameras_CameraData_o/r
  int32_t _cameraDataMode;
  bool _useLastGroundedY;
  bool _dontMoveInY;
  char pad[2];
  struct SmoothDampFloat_o *_fieldOfView;
  struct UnityEngine_Vector3_o _cameraTargetOffset;
  struct UnityEngine_Vector3_o _cameraTargetOffsetSmoothTime;
  struct UnityEngine_Vector3_o _cameraPositionOffset;
  struct UnityEngine_Vector3_o _cameraPositionOffsetSmoothTime;
  float _transformTweenDuration;
};

struct SYBO_Subway_Cameras_CameraData_o // sizeof=0x58
{
  void *klass; // SYBO_Subway_Cameras_CameraData_c *
  void *monitor;
  SYBO_Subway_Cameras_CameraData_Fields fields;
};

struct SYBO_Subway_Cameras_CharacterCamera_Fields// : UnityEngine_MonoBehaviour_Fields // sizeof=0x110
{                       
  char pad[0x8];                                                                      // XREF: SYBO_Subway_Cameras_CharacterCamera_o/r
  float MenuFieldOfView;
  float tunnelDelta;
  void *_mainCamera;//SYBO_Subway_Cameras_MainCamera_o
  void  *_disappearEff;//UnityEngine_GameObject_o
  struct UnityEngine_Vector3_o _position;
  struct UnityEngine_Vector3_o _target;
  float _speed;
  float _previousCameraEndYPosition;
  float _previousCameraEndXRotation;
  char pad1[4];
  void *_currentCameraData;//struct SYBO_Subway_Cameras_CameraData_o
  void *_cameraAnimation;//struct UnityEngine_Animation_o 
  int32_t _cameraSpeedType;
  float _customhighSpeedFOV;
  void *_currentCharacterState;//struct SYBO_Subway_Characters_States_CharacterState_o
  float _lastZ;
  struct UnityEngine_Vector3_o _shake;
  struct UnityEngine_Vector3_o _diff;
  bool _fovGipping;
  char pad2[3];
  void* _camera;//struct UnityEngine_Camera_o 
  void* _cameraTarget;//struct SYBO_Common_Data_SmoothDampVector3B_o
  struct UnityEngine_Vector3_o _lastCameraTransformPosition;
  struct UnityEngine_Vector3_o _lastCameraTarget;
  void *_cameraPosition;//struct SYBO_Common_Data_SmoothDampVector3B_o
  void *_character;//struct SYBO_Subway_Characters_CharacterBase_o
  void *_fieldOfViewSmoothDampFloat;//struct SmoothDampFloat_o 
  bool _hasSuperSneakers;
  char pad3[3];
  float _cameraModifierColliderStartGamePositionZ;
  void *offsetDeltaCurve;//struct SYBO_Subway_Curve_o 
  float _cameraModifierColliderEndGamePositionZ;
  float _cameraModifierY;
  float _cameraModifierX;
  struct UnityEngine_Vector3_o _previousCameraEndPosition;
  struct UnityEngine_Vector3_o _previousTargetEndPosition;
  float _tweenTimeTransform;
  bool _initialized;
  char pad4[3];
  float _lastDeltaYFactor;
  void *_pvpFinishFX;//struct UnityEngine_GameObject_o 
};


struct SYBO_Subway_Cameras_CharacterCamera_o // sizeof=0x120
{
  void *klass; // SYBO_Subway_Cameras_CharacterCamera_c
  void *monitor;
  SYBO_Subway_Cameras_CharacterCamera_Fields fields;
};


/*DummyField*/
#define structoffset_DummyFields_PlayerID 0x308
#define structoffset_DummyFields_CharacterID 0x30C
#define structoffset_DummyFields_name 0x330
#define structoffset_DummyFields_isAIMode 0x368
/*Dummy_Fields 继承自CharacterBase*/
#define structoffset_DummyFields_gamePosition 0x194
#define structoffset_DummyFields_transformPosition 0x1A0
#define structoffset_DummyFields_gravity 0xAC
#define structoffset_DummyFields_UID 0x10
/*SYBO_Subway_Characters_Character_o也继承base*/

#define structOffset_BindWeChatManager_fields_loginshield 0x11
#define structOffset_BindWeChatManager_fields_payshield 0x20

static inline uint16_t byteswap_ushort(uint16_t number)
{
#if defined(_MSC_VER) && _MSC_VER > 1310
  return _byteswap_ushort(number);
#elif defined(__GNUC__)
  return __builtin_bswap16(number);
#else
  return (number >> 8) | (number << 8);
#endif
}

// 从UTF16 LE编码的字符串创建
inline std::string utf16le_to_utf8(const std::u16string &u16str)
{
  if (u16str.empty())
  {
    return std::string();
  }
  const char16_t *p = u16str.data();
  std::u16string::size_type len = u16str.length();
  if (p[0] == 0xFEFF)
  {
    p += 1; // 带有bom标记，后移
    len -= 1;
  }

  // 开始转换
  std::string u8str;
  u8str.reserve(len * 3);

  char16_t u16char;
  for (std::u16string::size_type i = 0; i < len; ++i)
  {
    // 这里假设是在小端序下(大端序不适用)
    u16char = p[i];

    // 1字节表示部分
    if (u16char < 0x0080)
    {
      // u16char <= 0x007f
      // U- 0000 0000 ~ 0000 07ff : 0xxx xxxx
      u8str.push_back((char)(u16char & 0x00FF)); // 取低8bit
      continue;
    }
    // 2 字节能表示部分
    if (u16char >= 0x0080 && u16char <= 0x07FF)
    {
      // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
      u8str.push_back((char)(((u16char >> 6) & 0x1F) | 0xC0));
      u8str.push_back((char)((u16char & 0x3F) | 0x80));
      continue;
    }
    // 代理项对部分(4字节表示)
    if (u16char >= 0xD800 && u16char <= 0xDBFF)
    {
      // * U-00010000 - U-001FFFFF: 1111 0xxx 10xxxxxx 10xxxxxx 10xxxxxx
      uint32_t highSur = u16char;
      uint32_t lowSur = p[++i];
      // 从代理项对到UNICODE代码点转换
      // 1、从高代理项减去0xD800，获取有效10bit
      // 2、从低代理项减去0xDC00，获取有效10bit
      // 3、加上0x10000，获取UNICODE代码点值
      uint32_t codePoint = highSur - 0xD800;
      codePoint <<= 10;
      codePoint |= lowSur - 0xDC00;
      codePoint += 0x10000;
      // 转为4字节UTF8编码表示
      u8str.push_back((char)((codePoint >> 18) | 0xF0));
      u8str.push_back((char)(((codePoint >> 12) & 0x3F) | 0x80));
      u8str.push_back((char)(((codePoint >> 06) & 0x3F) | 0x80));
      u8str.push_back((char)((codePoint & 0x3F) | 0x80));
      continue;
    }
    // 3 字节表示部分
    {
      // * U-0000E000 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
      u8str.push_back((char)(((u16char >> 12) & 0x0F) | 0xE0));
      u8str.push_back((char)(((u16char >> 6) & 0x3F) | 0x80));
      u8str.push_back((char)((u16char & 0x3F) | 0x80));
      continue;
    }
  }

  return u8str;
}

// 从UTF16BE编码字符串创建
inline std::string utf16be_to_utf8(const std::u16string &u16str)
{
  if (u16str.empty())
  {
    return std::string();
  }
  const char16_t *p = u16str.data();
  std::u16string::size_type len = u16str.length();
  if (p[0] == 0xFEFF)
  {
    p += 1; // 带有bom标记，后移
    len -= 1;
  }

  // 开始转换
  std::string u8str;
  u8str.reserve(len * 2);
  char16_t u16char; // u16le 低字节存低位，高字节存高位
  for (std::u16string::size_type i = 0; i < len; ++i)
  {
    // 这里假设是在小端序下(大端序不适用)
    u16char = p[i];
    // 将大端序转为小端序
    u16char = byteswap_ushort(u16char);

    // 1字节表示部分
    if (u16char < 0x0080)
    {
      // u16char <= 0x007f
      // U- 0000 0000 ~ 0000 07ff : 0xxx xxxx
      u8str.push_back((char)(u16char & 0x00FF));
      continue;
    }
    // 2 字节能表示部分
    if (u16char >= 0x0080 && u16char <= 0x07FF)
    {
      // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
      u8str.push_back((char)(((u16char >> 6) & 0x1F) | 0xC0));
      u8str.push_back((char)((u16char & 0x3F) | 0x80));
      continue;
    }
    // 代理项对部分(4字节表示)
    if (u16char >= 0xD800 && u16char <= 0xDBFF)
    {
      // * U-00010000 - U-001FFFFF: 1111 0xxx 10xxxxxx 10xxxxxx 10xxxxxx
      uint32_t highSur = u16char;
      uint32_t lowSur = byteswap_ushort(p[++i]);
      // 从代理项对到UNICODE代码点转换
      // 1、从高代理项减去0xD800，获取有效10bit
      // 2、从低代理项减去0xDC00，获取有效10bit
      // 3、加上0x10000，获取UNICODE代码点值
      uint32_t codePoint = highSur - 0xD800;
      codePoint <<= 10;
      codePoint |= lowSur - 0xDC00;
      codePoint += 0x10000;
      // 转为4字节UTF8编码表示
      u8str.push_back((char)((codePoint >> 18) | 0xF0));
      u8str.push_back((char)(((codePoint >> 12) & 0x3F) | 0x80));
      u8str.push_back((char)(((codePoint >> 06) & 0x3F) | 0x80));
      u8str.push_back((char)((codePoint & 0x3F) | 0x80));
      continue;
    }
    // 3 字节表示部分
    {
      // * U-0000E000 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
      u8str.push_back((char)(((u16char >> 12) & 0x0F) | 0xE0));
      u8str.push_back((char)(((u16char >> 6) & 0x3F) | 0x80));
      u8str.push_back((char)((u16char & 0x3F) | 0x80));
      continue;
    }
  }
  return u8str;
}
inline std::string utf16_to_utf8(const std::u16string &u16str)
{
  if (u16str.empty())
  {
    return std::string();
  }
  // Byte Order Mark
  char16_t bom = u16str[0];
  switch (bom)
  {
  case 0xFEFF: // Little Endian
    return utf16le_to_utf8(u16str);
    break;
  case 0xFFFE: // Big Endian
    return utf16be_to_utf8(u16str);
    break;
  default:
    return std::string();
  }
}
inline std::u16string utf8_to_utf16le(const std::string &u8str, bool addbom,
                                      bool *ok)
{
  std::u16string u16str;
  u16str.reserve(u8str.size());
  if (addbom)
  {
    u16str.push_back(0xFEFF); // bom (字节表示为 FF FE)
  }
  std::string::size_type len = u8str.length();

  const unsigned char *p = (unsigned char *)(u8str.data());
  // 判断是否具有BOM(判断长度小于3字节的情况)
  if (len > 3 && p[0] == 0xEF && p[1] == 0xBB && p[2] == 0xBF)
  {
    p += 3;
    len -= 3;
  }

  bool is_ok = true;
  // 开始转换
  for (std::string::size_type i = 0; i < len; ++i)
  {
    uint32_t ch = p[i]; // 取出UTF8序列首字节
    if ((ch & 0x80) == 0)
    {
      // 最高位为0，只有1字节表示UNICODE代码点
      u16str.push_back((char16_t)ch);
      continue;
    }
    switch (ch & 0xF0)
    {
    case 0xF0: // 4 字节字符, 0x10000 到 0x10FFFF
    {
      uint32_t c2 = p[++i];
      uint32_t c3 = p[++i];
      uint32_t c4 = p[++i];
      // 计算UNICODE代码点值(第一个字节取低3bit，其余取6bit)
      uint32_t codePoint = ((ch & 0x07U) << 18) | ((c2 & 0x3FU) << 12) |
                           ((c3 & 0x3FU) << 6) | (c4 & 0x3FU);
      if (codePoint >= 0x10000)
      {
        // 在UTF-16中 U+10000 到 U+10FFFF 用两个16bit单元表示, 代理项对.
        // 1、将代码点减去0x10000(得到长度为20bit的值)
        // 2、high 代理项 是将那20bit中的高10bit加上0xD800(110110 00 00000000)
        // 3、low  代理项 是将那20bit中的低10bit加上0xDC00(110111 00 00000000)
        codePoint -= 0x10000;
        u16str.push_back((char16_t)((codePoint >> 10) | 0xD800U));
        u16str.push_back((char16_t)((codePoint & 0x03FFU) | 0xDC00U));
      }
      else
      {
        // 在UTF-16中 U+0000 到 U+D7FF 以及 U+E000 到 U+FFFF
        // 与Unicode代码点值相同. U+D800 到 U+DFFF 是无效字符,
        // 为了简单起见，这里假设它不存在(如果有则不编码)
        u16str.push_back((char16_t)codePoint);
      }
    }
    break;
    case 0xE0: // 3 字节字符, 0x800 到 0xFFFF
    {
      uint32_t c2 = p[++i];
      uint32_t c3 = p[++i];
      // 计算UNICODE代码点值(第一个字节取低4bit，其余取6bit)
      uint32_t codePoint =
          ((ch & 0x0FU) << 12) | ((c2 & 0x3FU) << 6) | (c3 & 0x3FU);
      u16str.push_back((char16_t)codePoint);
    }
    break;
    case 0xD0: // 2 字节字符, 0x80 到 0x7FF
    case 0xC0:
    {
      uint32_t c2 = p[++i];
      // 计算UNICODE代码点值(第一个字节取低5bit，其余取6bit)
      uint32_t codePoint = ((ch & 0x1FU) << 12) | ((c2 & 0x3FU) << 6);
      u16str.push_back((char16_t)codePoint);
    }
    break;
    default: // 单字节部分(前面已经处理，所以不应该进来)
      is_ok = false;
      break;
    }
  }
  if (ok != NULL)
  {
    *ok = is_ok;
  }

  return u16str;
}

// 获取转换为UTF-16 BE的字符串
inline std::u16string utf8_to_utf16be(const std::string &u8str, bool addbom,
                                      bool *ok)
{
  // 先获取utf16le编码字符串
  std::u16string u16str = utf8_to_utf16le(u8str, addbom, ok);
  // 将小端序转换为大端序
  for (size_t i = 0; i < u16str.size(); ++i)
  {
    u16str[i] = byteswap_ushort(u16str[i]);
  }
  return u16str;
}

struct System_String_Fields
{
  int32_t m_stringLength;
  uint16_t
      m_firstChar[256]; // XREF: UI.Pages.BattlePassPreviousPage$$SetView+8/w
};
struct System_String_o
{
  void *klass;
  void *monitor;
  System_String_Fields fields;
  std::string get_utf8_string()
  {
    std::u16string namewstr;
    for (int j = 0; j < this->fields.m_stringLength; j++)
    {
      namewstr.push_back((this->fields.m_firstChar[j]));
    }
    std::string namestr = utf16le_to_utf8(namewstr);
    return namestr;
  }
  void set_utf8_to_this(std::string in)
  {
    std::u16string tmp = utf8_to_utf16le(in, false, NULL);
    this->fields.m_stringLength = tmp.size();
    for (int i = 0; i < tmp.size(); i++)
    {
      this->fields.m_firstChar[i] = tmp[i];
    }
  }
};

inline std::string generateRandomString()
{
  std::string result = "7"; // 字符串以 '7' 开头
  // 设置随机数种子
  std::srand(std::time(0));
  // 生成接下来的9个数字字符
  for (int i = 0; i < 9; ++i)
  {
    result += std::to_string(std::rand() % 10); // 生成随机数字 0-9
  }
  return result;
}

typedef uintptr_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;
struct Il2CppClass;
struct Il2CppObject
{
  Il2CppClass *kclass;
  void *monitor;
};
struct Il2CppArrayBounds
{
  il2cpp_array_size_t length;
  il2cpp_array_lower_bound_t lower_bound;
};
struct System_Collections_Generic_Dictionary_Entry_TKey__TValue__Fields
{
  int32_t hashCode;
  int32_t next;
  Il2CppObject *key;
  Il2CppObject *value;
};
struct System_Collections_Generic_Dictionary_Entry_TKey__TValue__o
{
  System_Collections_Generic_Dictionary_Entry_TKey__TValue__Fields fields;
};
struct System_Collections_Generic_Dictionary_Entry_TKey__TValue__array
{
  Il2CppObject obj;
  Il2CppArrayBounds *bounds;
  il2cpp_array_size_t max_length;
  System_Collections_Generic_Dictionary_Entry_TKey__TValue__o m_Items[20];
};
struct System_Collections_Generic_Dictionary_int__Dummy__Fields
{
  struct System_Int32_array *buckets;
  struct System_Collections_Generic_Dictionary_Entry_TKey__TValue__array
      *entries;
  int32_t count;
  int32_t version;
  int32_t freeList;
  int32_t freeCount;
  struct System_Collections_Generic_IEqualityComparer_TKey__o *comparer;
  struct System_Collections_Generic_Dictionary_KeyCollection_TKey__TValue__o
      *keys;
  struct System_Collections_Generic_Dictionary_ValueCollection_TKey__TValue__o
      *values;
  Il2CppObject *_syncRoot;
};
struct System_Collections_Generic_Dictionary_int__Dummy__o
{
  void *klass;
  void *monitor;
  System_Collections_Generic_Dictionary_int__Dummy__Fields fields;
};

struct PhotonPlayer_Fields // sizeof=0x30
{                          // XREF: PhotonPlayer_o/r
  int32_t actorID;
  char pad0[4];
  struct System_String_o *nameField;
  struct System_String_o *_UserId_k__BackingField;
  bool IsLocal;
  bool _IsInactive_k__BackingField;
  char pad1[6];
  void *_CustomProperties_k__BackingField; // struct
                                           // ExitGames_Client_Photon_Hashtable_o
                                           // *
  void *TagObject;                         // Il2CppObject *
};

struct PhotonPlayer_o // sizeof=0x40
{
  void *klass; // PhotonPlayer_c *
  void *monitor;
  PhotonPlayer_Fields fields;
};
struct PhotonPlayer_array // 只能用指针！ sizeof=0x80018
{
  Il2CppObject obj;
  Il2CppArrayBounds *bounds;
  il2cpp_array_size_t max_length;
  PhotonPlayer_o *m_Items[10];
};

inline std::vector<uint64_t>
getAllDummy(System_Collections_Generic_Dictionary_int__Dummy__o *dictptr)
{
  std::vector<uint64_t> result;
  System_Collections_Generic_Dictionary_int__Dummy__o dictionary = *dictptr;
  debug_log(@"Entry address: %p Size: %d", dictionary.fields.entries,
            dictionary.fields.count);
  int32_t count = dictionary.fields.count;
  if (dictionary.fields.entries)
  {
    System_Collections_Generic_Dictionary_Entry_TKey__TValue__array entry =
        *(dictionary.fields.entries);
    debug_log(@"Entities Count:%d", count);
    for (int i = 0; i < count; i++)
    {
      auto item = entry.m_Items[i];
      if (item.fields.value)
      {
        auto Dummy_Fields = (uint64_t)item.fields.value + 0x10;
        debug_log(@"Pushed entity:%p", Dummy_Fields);
        result.push_back((uint64_t)Dummy_Fields);
      }
    }
  }
  return result;
}