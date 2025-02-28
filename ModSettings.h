#pragma once

#include <functional>
#include <vector>

#ifdef MENU_EXPORTS
    #define MENU_API __declspec(dllexport)
#else
    #define MENU_API __declspec(dllimport)
#endif

typedef std::function<void()> CallbackFn;
class UISystemMenu;

#ifdef MENU_EXPORTS
    #include "game/UI/UISystemMenuItem.h"
#else
class UISystemMenuItem {
    char _0x0[0x30];
};

class ItemDisplayData {
    char _0x0[0x88];
public:
    MENU_API void SetLabel(const char* label);
    MENU_API void SetDescription(const char* desc);
    MENU_API void SetImage(const char* img);
    MENU_API void SetIcon(const char* icon);
};
#endif

class BaseMenu {
    int id;
    UISystemMenu* menu;
    std::vector<UISystemMenuItem> items;
    
    virtual void Create() = 0;
    inline UISystemMenuItem* GetItems() { return items.data(); };
    inline int GetItemsCount() { return items.size(); };
    MENU_API void Deinit();
public:
    virtual const char* GetName() = 0;
    virtual const char* GetDescription() { return nullptr; };
    MENU_API BaseMenu();
    MENU_API void Init();
    MENU_API int GetMenuID();
    
    MENU_API UISystemMenu* GetMenu();

    MENU_API void GotoMenu(BaseMenu* menu);
    MENU_API void GotoMenu(BaseMenu* menu, const char* image);

    template<typename T>
    inline void GotoMenu() {
        GotoMenu(new T());
    }
    template<typename T>
    inline void GotoMenu(const char* texture) {
        GotoMenu(new T(), texture);
    }
    
    MENU_API void Dropdown(BaseMenu* menu);
    template<typename T>
    inline void Dropdown() {
        Dropdown(new T());
    }
    
    MENU_API void Header(const char* label);
    MENU_API void Button(const char* label, const char* desc, CallbackFn on_click);
    MENU_API void Button(ItemDisplayData &display_data, CallbackFn on_click);
    MENU_API void Toggle(const char* label, const char* desc, int* toggled, CallbackFn on_change = nullptr);
    MENU_API void Toggle(ItemDisplayData &display_data, int* toggled, CallbackFn on_change = nullptr);
    MENU_API void Option(const char* label, const char* desc, int* selected, const char** options, int count, CallbackFn on_change = nullptr);
    MENU_API void Option(ItemDisplayData &display_data, int* selected, const char** options, int count, CallbackFn on_change = nullptr);

    struct SliderOpts {
        float min = 0.0f;
        float max = 1.0f;
        int display_min = 0;
        int display_max = 10;
        // As of the writing of this code,
        // the PC port does not correctly handle step values above 1
        // unless using the dpad or arrow keys
        float step = 1.0f;
    };

    MENU_API void Slider(const char* label, const char* desc, float* value, SliderOpts &options, CallbackFn on_change = nullptr);
    MENU_API void Slider(ItemDisplayData &display_data, float* value, SliderOpts &options, CallbackFn on_change = nullptr);

    MENU_API void RequestRefresh();
    MENU_API void Close();
};

class ModMenu : public BaseMenu {
public:
    enum MenuType {
        Pause,
        Lobby,
        Global
    };
    virtual MenuType GetType() = 0;
    inline bool IsLobby() { return GetType() == MenuType::Lobby || GetType() == MenuType::Global; }
    inline bool IsPause() { return GetType() == MenuType::Pause || GetType() == MenuType::Global; }
};

namespace ModSettings {
    MENU_API void RegisterMenu(ModMenu* inst);
    template<typename T>
    inline void RegisterMenu() {
        RegisterMenu(new T());
    } 

    MENU_API void RegisterSaveCallback(CallbackFn cb);
}