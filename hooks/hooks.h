#pragma once
#import "dobby_defines.h"
#include "../Utils/definations.h"
#include <libgen.h>
#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <mach-o/dyld.h>
#include <mach/vm_page_size.h>
#include <Foundation/Foundation.h>
#include <map>
#include <deque>
#include <vector>
#include <array>
#include <substrate.h>




#ifdef DEBUG
#define log(...)  NSLog(__VA_ARGS__)
#else
#define log(...)
#endif

//HOOK BEGIN
#pragma GCC diagnostic ignored "-Warc-performSelector-leaks"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wincomplete-implementation"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-W#warnings"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wreorder"
#pragma GCC diagnostic ignored "-Wwritable-strings"
#pragma GCC diagnostic ignored "-Wtrigraphs"

#define STATIC_HOOK_CODEPAGE_SIZE PAGE_SIZE
#define STATIC_HOOK_DATAPAGE_SIZE PAGE_SIZE

// C++ version made by Lavochka

uint64_t va2rva(struct mach_header_64* header, uint64_t va);
// C++ version made by Lavochka
void* rva2data(struct mach_header_64* header, uint64_t rva);
// C++ version made by Lavochka
NSMutableData* load_macho_data(NSString* path);
NSMutableData* add_hook_section(NSMutableData* macho);
bool hex2bytes(char* bytes, unsigned char* buffer);

uint64_t calc_patch_hash(uint64_t vaddr, char* patch);

NSString* StaticInlineHookPatch(char* machoPath, uint64_t vaddr, char* patch);

void* find_module_by_path(char* machoPath);
StaticInlineHookBlock* find_hook_block(void* base, uint64_t vaddr);

void* StaticInlineHookFunction(char* machoPath, uint64_t vaddr, void* replace);

BOOL ActiveCodePatch(char* machoPath, uint64_t vaddr, char* patch);
BOOL DeactiveCodePatch(char* machoPath, uint64_t vaddr, char* patch);
#ifdef JAILED
inline NSString* result_string;
#define HOOK(x, y, z) \
result_string = StaticInlineHookPatch(EXCUTABLEPATH, x, nullptr); \
if (result_string) { \
     log(@"Hook result: %s", result_string.UTF8String); \
    void* result = StaticInlineHookFunction(EXCUTABLEPATH, x, (void *) y); \
     log(@"Hook result %p", result); \
    *(void **) (&z) = (void*) result; \
}
#define ONETIMEPATCH(addr, patch)\
result_string = StaticInlineHookPatch(EXCUTABLEPATH, addr, (char*)patch); \
if (result_string){\
     log(result_string);\
    if(ActiveCodePatch(EXCUTABLEPATH, addr,(char*)patch))\
         log(@"OneTime Patch Succeed.");\
}
#define ADDSWITCHPATCH(addr, patch)\
log(StaticInlineHookPatch(EXCUTABLEPATH, addr, patch));

#define ACTIVATESWITCHPATCH(addr, patch)\
if (ActiveCodePatch(EXCUTABLEPATH, addr, patch)){\
     log(@"Patch Activated.");\
}
#define DEACTIVATESWITCHPATCH(addr, patch)\
if (DeactiveCodePatch(EXCUTABLEPATH, addr, patch)){\
     log(@"Patch DEActivated.");\
}
#else
#define HOOK(x, y, z) \
     jbHOOK(x,y,z);
#define ONETIMEPATCH(addr, patch)\
patchOffset(addr, patch);
#endif