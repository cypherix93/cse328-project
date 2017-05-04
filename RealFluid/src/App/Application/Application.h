#pragma once

#include <iostream>
#include <omp.h>
#include "../../Core/Window/WindowManager/WindowManager.h"
#include "EventHandlers.h"

using namespace std;

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720

class Application
{
    public:
    Application();
    virtual ~Application();

    // Getters
    WindowManager* GetWindowManager() const;

    // Lifecycle Hooks
    void Setup();
    void Start();

    private:
    WindowManager* _WindowManager;
};

extern Application* APPLICATION;