#pragma once
#define JAILED  //给越狱的手机编译需要打开这个宏
//#define DEBUG
//#define DUMP_HOOK   //当需要生成修改过的可执行文件 打开这个宏
#define  EXCUTABLEPATH "Frameworks/UnityFramework.framework/UnityFramework"
//只用于在非越狱环境下，进行Patch和Hook
#define EXCUTABLENAME "UnityFramework"
//用于在越狱环境下进行Patch和Hook

#define WATERMARK "Rigel SubwaySuck:"

#ifdef DEBUG
#define debug_log(...)  NSLog(__VA_ARGS__)
#else
#define debug_log(...)
#endif