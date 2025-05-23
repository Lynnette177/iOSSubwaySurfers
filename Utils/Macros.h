//
//  Macros.h
//  ModMenu
//
//  Created by Joey on 4/2/19.
//  Copyright © 2019 Joey. All rights reserved.
//
#import "../KittyMemory/KittyMemory.hpp"
#import "../KittyMemory/MemoryPatch.hpp"
#import "../KittyMemory/writeData.hpp"
#import "Obfuscate.h"
#import "definations.h"

#include <mach-o/dyld.h>
#include <substrate.h>

// definition at Menu.h

// thanks to shmoo for the usefull stuff under this comment.
#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^
#define jbHOOK(offset, ptr, orig)                                              \
  MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)
#define jbHOOK_NO_ORIG(offset, ptr)                                            \
  MSHookFunction((void *)getRealOffset(offset), (void *)ptr, NULL)

// Note to not prepend an underscore to the symbol. See Notes on the Apple
// manpage
// (https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/dlsym.3.html)
#define jbHOOKSYM(sym, ptr, org)                                               \
  MSHookFunction((void *)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr,        \
                 (void **)&org)
#define jbHOOKSYM_NO_ORIG(sym, ptr)                                            \
  MSHookFunction((void *)dlsym((void *)RTLD_DEFAULT, sym), (void *)ptr, NULL)
#define getSym(symName) dlsym((void *)RTLD_DEFAULT, symName)

// Convert hex color to UIColor, usage: For the color #BD0000 you'd use:
// UIColorFromHex(0xBD0000)
#define UIColorFromHex(hexColor)                                               \
  [UIColor colorWithRed:((float)((hexColor & 0xFF0000) >> 16)) / 255.0         \
                  green:((float)((hexColor & 0xFF00) >> 8)) / 255.0            \
                   blue:((float)(hexColor & 0xFF)) / 255.0                     \
                  alpha:1.0]

