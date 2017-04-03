#pragma once
#include <iostream>
#include "../../Core/Window/WindowManager/WindowManager.h"
#include "EventHandlers.h"

using namespace std;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Application
{
    public:
    Application();
    virtual ~Application();
    
    // Lifecycle Hooks
    void Setup();
    void Start();

    private:
    WindowManager* _WindowManager;
};