#pragma once

#include "ModSettings.h"

class HealthMenu : public ModMenu {
public:
    const char* GetName() override { return "TEST MENU"; }
    const char* GetDescription() override { return "Template script menu."; }
    MenuType GetType() override { return MenuType::Pause; }
    void Create() override;
};

