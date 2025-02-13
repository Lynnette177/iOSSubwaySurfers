#ifndef Menu_h
#define Menu_h
#include <vector>
#include <functional>
#include <string>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
#include "../ImGui/imgui_impl_metal.h"
#include "../ImGui/CustomWidgets.h"
#include "../ImGui/Fonts.hpp"
#include "SubMenu.h"

using namespace std;

void LoadMenu();
void SetStyles();
void ESP();
extern ImVec2 MenuOrigin;
extern ImVec2 MenuSize;
extern bool MoveMenu;
extern UITextField* hideRecordTextfield;
extern void LoadMods();

#endif