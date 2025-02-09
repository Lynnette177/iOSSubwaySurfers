#import "Macros.h"
#include <cstdbool>
#include <cstdint>
#include <Foundation/Foundation.h>
#import <substrate.h>
#import <mach-o/dyld.h>
#import "offsets.hpp"
bool InstallHooks();
/***********************************************************
  INSIDE THE FUNCTION BELOW YOU'LL HAVE TO ADD YOUR SWITCHES!
***********************************************************/
void setup() {
  
  [switches addOffsetSwitch:NSSENCRYPT("广告退出即奖励")
    description:NSSENCRYPT("开启后看广告弹窗后退出，即可获得奖励")
    offsets: {
      ENCRYPTOFFSET(offset_SubwayAdManager__VideoFailed)//上下可以一同写多个
    }
    bytes: {
      ENCRYPTHEX("C8 FF FF 17")//这里是跳转到finish的位置
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("无视碰撞")
    description:NSSENCRYPT("开启后无视碰撞")
    offsets: {
      ENCRYPTOFFSET(offset_SYBO_Subway_Utilities_DebugSettings__get_IsAllowed),//上下可以一同写多个
      ENCRYPTOFFSET(offset_SYBO_Subway_Utilities_DebugSettings__get_CharacterInvincible)
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6"),
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];
  [switches addSwitch:NSSENCRYPT("上帝视角")
    description:NSSENCRYPT("开启后俯视赛道")
  ];
  [switches addOffsetSwitch:NSSENCRYPT("强开炫跑卡")
    description:NSSENCRYPT("开启后本地强制启用炫跑卡")
    offsets: {
      ENCRYPTOFFSET(offset_SuperRunVIPManager__IsActive)//上下可以一同写多个
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有角色")//IDreamSky.BagManager$$IsUnlockedCharacter
    description:NSSENCRYPT("开启后解锁全部角色")
    offsets: {
      ENCRYPTOFFSET(offset_IDreamSky_BagManager$$IsUnlockedCharacter)
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有滑板")//
    description:NSSENCRYPT("开启后解锁全部滑板")
    offsets: {
      ENCRYPTOFFSET(offset_PlayerInfo__isHoverboardUnlockedm)
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有角色主题")//
    description:NSSENCRYPT("开启后解锁全部角色主题")
    offsets: {
      ENCRYPTOFFSET(offset_IDreamSky_BagManager__IsUnlockedCharacterTheme)
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有Sticker")//
    description:NSSENCRYPT("开启后解锁全部Sticker")
    offsets: {
      ENCRYPTOFFSET(offset_CharacterStickerManager__isCharacterUnlocked)
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有装饰")//
    description:NSSENCRYPT("开启后解锁全部装饰")
    offsets: {
      ENCRYPTOFFSET(offset_PlayerInfo__IsOrnamentUnlocked)
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];

  [switches addSwitch:NSSENCRYPT("PVP双倍滑板能量")
    description:NSSENCRYPT("道具赛收集到的能量翻倍")
  ];
  [switches addSwitch:NSSENCRYPT("PVP疯狂加速")
    description:NSSENCRYPT("道具赛开启后可以无视碰撞。无论是碰撞还是减速带都会变成最高等级的加速。")
  ];
  [switches addOffsetSwitch:NSSENCRYPT("PVP无视道具")//
    description:NSSENCRYPT("开启后PVP不会受到其他玩家减速道具的影响")
    offsets: {
      ENCRYPTOFFSET(offset_HPFXBase___DefenseCheck)
    }
    bytes: {
      ENCRYPTHEX("20 00 80 52 C0 03 5F D6")
    }
  ];

  [switches addSliderSwitch:NSSENCRYPT("修改金币")
    description:NSSENCRYPT("开启后将修改并锁定金币，触发任何导致金币变化的事件即可修改。比如开一把吃两个金币。如果需要修改跑酷币，也要打开这个。")
    minimumValue:1
    maximumValue:100000
    sliderColor:UIColorFromHex(0xBD0000)
  ];
  [switches addSliderSwitch:NSSENCRYPT("修改钥匙")
    description:NSSENCRYPT("开启后将修改并锁定钥匙，触发任何导致钥匙变化的事件即可修改。比如使用一把钥匙")
    minimumValue:1
    maximumValue:9999
    sliderColor:UIColorFromHex(0xBD0000)
  ];
   [switches addSliderSwitch:NSSENCRYPT("修改宝物钥匙")
    description:NSSENCRYPT("开启后当金币数量发生变化的时候将连带修改宝物钥匙")
    minimumValue:1
    maximumValue:9999
    sliderColor:UIColorFromHex(0xBD0000)
  ];
  [switches addSliderSwitch:NSSENCRYPT("修改分数")
    description:NSSENCRYPT("当分数发生变化的时候，会修改分数。")
    minimumValue:1
    maximumValue:300000
    sliderColor:UIColorFromHex(0xBD0000)
  ];
  [switches addSliderSwitch:NSSENCRYPT("修改模型大小")
    description:NSSENCRYPT("开启后当游戏重新加载人物模型的时候，将改变其大小")
    minimumValue:0.1
    maximumValue:10
    sliderColor:UIColorFromHex(0xBD0000)
  ];
}


/**********************************************************************************************************
     You can customize the menu here
     For colors, you can use hex color codes or UIColor itself
      - For the hex color #d51b07 you'd use: UIColorFromHex(0xBD0000)
      - For UIColor you can visit this site: https://www.uicolor.xyz/#/rgb-to-ui
        NOTE: remove the ";" when you copy your UIColor from there!
     
     Site to find your perfect font for the menu: http://iosfonts.com/  --> view on mac or ios device
     See comment next to maxVisibleSwitches!!!!

     menuIcon & menuButton is base64 data, upload a image to: https://www.browserling.com/tools/image-to-base64 \
     then replace that string with mine.
************************************************************************************************************/
void setupMenu() {

  // If a game uses a framework as base executable, you can enter the name here.
  // For example: UnityFramework, in that case you have to replace NULL with "UnityFramework" (note the quotes)
  while(!InstallHooks()){}//在这里拿到UnityFramework基地址，确保加载过了

  menu = [[Menu alloc]  
            initWithTitle:NSSENCRYPT("SubwaySuck - Mod Menu")
            titleColor:[UIColor whiteColor]
            titleFont:NSSENCRYPT("Copperplate-Bold")
            credits:NSSENCRYPT("SubwaySuck Mod Menu.\n作者：Lynnette177\n请勿在未经允许的情况下分享\n游戏反作弊已被关闭\nEnjoy!")
            headerColor:UIColorFromHex(0xd51b07)
            switchOffColor:[UIColor darkGrayColor]
            switchOnColor:UIColorFromHex(0x00ADF2)
            switchTitleFont:NSSENCRYPT("Copperplate-Bold")
            switchTitleColor:[UIColor whiteColor]
            infoButtonColor:UIColorFromHex(0xBD0000)
            maxVisibleSwitches:4 // Less than max -> blank space, more than max -> you can scroll!
            menuWidth:250
            menuIcon:@"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"
            menuButton:@"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"];    

    /********************************************************************
        Once menu has been initialized, it will run the setup functions. 
        All of your switches should be entered in the setup() function!
    *********************************************************************/
    setup();
}

// If the menu button doesn't show up; Change the timer to a bigger amount.
static void didFinishLaunching(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef info) {
    Initialize();
    timer(5) {
    SCLAlertView *alert = [[SCLAlertView alloc] initWithNewWindow];

    // Website link, remove it if you don't need it.
    [alert addButton: NSSENCRYPT("访问我的网站") actionBlock: ^(void) {
      [[UIApplication sharedApplication] openURL: [NSURL URLWithString: NSSENCRYPT("https://note.lynnette.uk")]];
      timer(2) {
        setupMenu();
      });        
    }];

    [alert addButton: NSSENCRYPT("感谢，已理解") actionBlock: ^(void) {
      timer(2) {
        setupMenu();
      });
    }];    

    alert.shouldDismissOnTapOutside = NO;
    alert.customViewColor = [UIColor purpleColor];  
    alert.showAnimationType = SCLAlertViewShowAnimationSlideInFromCenter;   
    
    [alert showSuccess: nil
            subTitle:NSSENCRYPT("SubwaySuck Mod Menu.\n作者：Lynnette177\n请勿在未经允许的情况下分享\n游戏反作弊已被关闭\n开屏广告已移除\nEnjoy!") 
              closeButtonTitle:nil
                duration:99999999.0f];
  });
}

typedef struct {
    char pad[0x18];
    size_t length;
    int32_t vector[0];  // 这个是数组的起始位置
} MonoArray;


bool InstallHooks(){
  uintptr_t UnityFrameworkBaseAddr = NULL;
  uint32_t moduleCount = _dyld_image_count();
  for (uint32_t i = 0; i<moduleCount; i++){
    const char* moduleName = _dyld_get_image_name(i);
    if (strstr(moduleName, "UnityFramework")){
      UnityFrameworkBaseAddr = (uintptr_t)_dyld_get_image_header(i);
    }
  }
  if (UnityFrameworkBaseAddr){
    FunctionAddress::initFunctionAddress(UnityFrameworkBaseAddr);
    GameFunction::initFunctions();
    hookFunctionAddress::PlayerInfo__set_amountOfCoins_Address += UnityFrameworkBaseAddr;
    MSHookFunction((void*)hookFunctionAddress::PlayerInfo__set_amountOfCoins_Address, (void*)hooks::new_PlayerInfo__set_amountOfCoins, (void**)&hooks::org_PlayerInfo__set_amountOfCoins);
    hookFunctionAddress::PlayerInfo__set_amountOfKeys_Address += UnityFrameworkBaseAddr;
    MSHookFunction((void*)hookFunctionAddress::PlayerInfo__set_amountOfKeys_Address, (void*)hooks::new_PlayerInfo__set_amountOfKeys, (void**)&hooks::org_PlayerInfo__set_amountOfKeys);
    hookFunctionAddress::GameStats__set_score_Address += UnityFrameworkBaseAddr;
    MSHookFunction((void*)hookFunctionAddress::GameStats__set_score_Address, (void*)hooks::new_GameStats__set_score, (void**)&hooks::org_GameStats__set_score);
    hookFunctionAddress::HPowerupEnergy___TriggerIn_Address += UnityFrameworkBaseAddr;
    MSHookFunction((void*)hookFunctionAddress::HPowerupEnergy___TriggerIn_Address, (void*)hooks::new_HPowerupEnergy___TriggerIn, (void**)&hooks::org_HPowerupEnergy___TriggerIn);
    hookFunctionAddress::HCharSpeed___ChangeState_Address += UnityFrameworkBaseAddr;
    MSHookFunction((void*)hookFunctionAddress::HCharSpeed___ChangeState_Address, (void*)hooks::new_HCharSpeed___ChangeState, (void**)&hooks::org_HCharSpeed___ChangeState);
    hookFunctionAddress::CharacterModel__GetScale_Address += UnityFrameworkBaseAddr;
    MSHookFunction((void*)hookFunctionAddress::CharacterModel__GetScale_Address, (void*)hooks::new_CharacterModel__GetScale, (void**)&hooks::org_CharacterModel__GetScale);
    hookFunctionAddress::UnityEngine_Transform__set_position_Address += UnityFrameworkBaseAddr;
    MSHookFunction((void*)hookFunctionAddress::UnityEngine_Transform__set_position_Address, (void*)hooks::new_UnityEngine_Transform__set_position, (void**)&hooks::org_UnityEngine_Transform__set_position);
    return true;
  }
  return false;
}

%ctor {
  CFNotificationCenterAddObserver(CFNotificationCenterGetLocalCenter(), NULL, &didFinishLaunching, (CFStringRef)UIApplicationDidFinishLaunchingNotification, NULL, CFNotificationSuspensionBehaviorDeliverImmediately);
}