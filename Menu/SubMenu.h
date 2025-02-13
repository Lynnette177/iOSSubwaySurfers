#pragma once
#include "../Config/Config.h"
#include "../Games/offsets.hpp"
#include "../hooks/hooks.h"
#include "../Games/mainFunctions.hpp"
#include "Menu.h"
#include <string>
#include <vector>
inline vector<MemoryPatch> Patches = {};
inline vector<std::string> enabledFeatures = {};
inline std::map<std::string, std::string> Descriptions = {};
extern bool StreamerMode;


void Submenu0_Personal(std::map<std::string, bool> &childVisibilityMap,bool isPage, bool shouldLoad);
void Submenu1_Aim(std::map<std::string, bool> &childVisibilityMap,bool isPage, bool shouldLoad);
void Submenu2_Visual(std::map<std::string, bool> &childVisibilityMap,bool isPage, bool shouldLoad);
void Submenu3_Server(std::map<std::string, bool> &childVisibilityMap,bool isPage, bool shouldLoad);
void Submenu4_Settings(std::map<std::string, bool> &childVisibilityMap,bool isPage, bool shouldLoad);
void ChildView(const std::map<std::string, bool> &childVisibilityMap,bool shoudLoad);
void esp();