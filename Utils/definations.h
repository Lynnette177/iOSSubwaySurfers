#pragma once
#define JAILED  //给越狱的手机编译需要打开这个宏
#define DEBUG
#define  EXCUTABLEPATH "Frameworks/UnityFramework.framework/UnityFramework"
//只用于在非越狱环境下，进行Patch和Hook
#define EXCUTABLENAME "UnityFramework"
//用于在越狱环境下进行Patch和Hook