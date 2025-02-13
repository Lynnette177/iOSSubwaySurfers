#import "Games/init.hpp"
#import "Utils/Macros.h"
#include <Foundation/Foundation.h>
#include <cstdbool>
#include <cstdint>
#import <mach-o/dyld.h>
#import <substrate.h>
#import "SCLAlertView/SCLAlertView.h"
#import "ImGui/MenuUtils.h"


void setup() {
  /*
  [switches addSwitch:NSSENCRYPT("上帝视角")
    description:NSSENCRYPT("开启后俯视赛道")
  ];

  [switches addOffsetSwitch:NSSENCRYPT("广告退出即奖励")
    description:NSSENCRYPT("开启后看广告弹窗后退出，即可获得奖励")
    offsets: {
      offset_SubwayAdManager__VideoFailed//上下可以一同写多个
    }
    bytes: {
      PATCH_FROM_FAILED_TO_FINSH_ADS
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("无视碰撞")
    description:NSSENCRYPT("开启后无视碰撞")
    offsets: {
      offset_SYBO_Subway_Utilities_DebugSettings__get_IsAllowed,//上下可以一同写多个
      offset_SYBO_Subway_Utilities_DebugSettings__get_CharacterInvincible
    }
    bytes: {
      PATCH_RET1,
      PATCH_RET1
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("强开炫跑卡")
    description:NSSENCRYPT("开启后本地强制启用炫跑卡")
    offsets: {
      offset_SuperRunVIPManager__IsActive//上下可以一同写多个
    }
    bytes: {
      PATCH_RET1
    }
  ];
  [switches
  addOffsetSwitch:NSSENCRYPT("解锁所有角色")//IDreamSky.BagManager$$IsUnlockedCharacter
    description:NSSENCRYPT("开启后解锁全部角色")
    offsets: {
      offset_IDreamSky_BagManager$$IsUnlockedCharacter
    }
    bytes: {
      PATCH_RET1
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有滑板")//
    description:NSSENCRYPT("开启后解锁全部滑板")
    offsets: {
      offset_PlayerInfo__isHoverboardUnlockedm
    }
    bytes: {
      PATCH_RET1
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有角色主题")//
    description:NSSENCRYPT("开启后解锁全部角色主题")
    offsets: {
      offset_IDreamSky_BagManager__IsUnlockedCharacterTheme
    }
    bytes: {
      PATCH_RET1
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有Sticker")//
    description:NSSENCRYPT("开启后解锁全部Sticker")
    offsets: {
      offset_CharacterStickerManager__isCharacterUnlocked
    }
    bytes: {
      PATCH_RET1
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("解锁所有装饰")//
    description:NSSENCRYPT("开启后解锁全部装饰")
    offsets: {
      offset_PlayerInfo__IsOrnamentUnlocked
    }
    bytes: {
      PATCH_RET1
    }
  ];
  [switches addOffsetSwitch:NSSENCRYPT("PVP无视道具")//
    description:NSSENCRYPT("开启后PVP不会受到其他玩家减速道具的影响")
    offsets: {
      offset_HPFXBase___DefenseCheck
    }
    bytes: {
      PATCH_RET1
    }
  ];

  [switches addSwitch:NSSENCRYPT("PVP双倍滑板能量")
    description:NSSENCRYPT("道具赛收集到的能量翻倍")
  ];
  [switches addSwitch:NSSENCRYPT("PVP疯狂加速")
    description:NSSENCRYPT("道具赛开启后可以无视碰撞。无论是碰撞还是减速带都会变成最高等级的加速。")
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
  */
}
void setupMenu() {
  [MenuUtils loadMenu];
  setup();
}

// If the menu button doesn't show up; Change the timer to a bigger amount.
static void didFinishLaunching(CFNotificationCenterRef center, void *observer,
                               CFStringRef name, const void *object,
                               CFDictionaryRef info) {
  Initialize();
  //setupMenu();//当patch offset时需要打开因为必须在一加载的时候patch
  // 在这里面设置了越狱状态下menu的patch都是patch哪个可执行文件
  timer(3) {
    SCLAlertView *alert = [[SCLAlertView alloc] initWithNewWindow];

    // Website link, remove it if you don't need it.
    [alert addButton:NSSENCRYPT("访问我的网站")
         actionBlock:^(void) {
           [[UIApplication sharedApplication]
               openURL:[NSURL URLWithString:NSSENCRYPT(
                                                "https://note.lynnette.uk")]];
           timer(1) { setupMenu(); });
         }];

    [alert addButton:NSSENCRYPT("感谢，已理解")
         actionBlock:^(void) {
           timer(1) { setupMenu(); });
         }];

    alert.shouldDismissOnTapOutside = NO;
    alert.customViewColor = [UIColor purpleColor];
    alert.showAnimationType = SCLAlertViewShowAnimationSlideInFromCenter;

    [alert showSuccess:nil
                subTitle:NSSENCRYPT("SubwaySuck Mod "
                                    "Menu."
                                    "\n作者：Lynnette177\n请勿在未经允许的情况"
                                    "下分享\n游戏反作弊已被关闭\nEnjoy!")
        closeButtonTitle:nil
                duration:99999999.0f];
  });
}

typedef struct {
  char pad[0x18];
  size_t length;
  int32_t vector[0]; // 这个是数组的起始位置
} MonoArray;

%ctor {
  CFNotificationCenterAddObserver(
      CFNotificationCenterGetLocalCenter(), NULL, &didFinishLaunching,
      (CFStringRef)UIApplicationDidFinishLaunchingNotification, NULL,
      CFNotificationSuspensionBehaviorDeliverImmediately);
}