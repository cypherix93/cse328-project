#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL.h>
#include <functional>

typedef std::function<void(void)> InitHandlerFunc;
typedef std::function<void(void)> DrawHandlerFunc;
typedef std::function<void(void)> UpdateHandlerFunc;
typedef std::function<void(SDL_WindowEvent)> WindowHandlerFunc;
typedef std::function<void(SDL_MouseButtonEvent)> MouseHandlerFunc;
typedef std::function<void(SDL_KeyboardEvent)> KeyboardHandlerFunc;

class WindowManager
{
    public:
    WindowManager();
    virtual ~WindowManager();

    // Lifecycle functions
    void OpenWindow(std::string title, int width, int height);
    void Start(int fps = 60);

    // Event Handler Register functions
    void OnInit(InitHandlerFunc);
    void OnUpdateEvent(UpdateHandlerFunc);
    void OnDrawEvent(DrawHandlerFunc);
    void OnWindowEvent(WindowHandlerFunc);
    void OnMouseEvent(MouseHandlerFunc);
    void OnKeyboardEvent(KeyboardHandlerFunc);


    private:
    void Init() const;
    void Dispose() const;

    SDL_Window* _Window = nullptr;
    SDL_GLContext _GLContext;
    bool _IsRunning;

    InitHandlerFunc _InitHandler = nullptr;
    UpdateHandlerFunc _UpdateEventHandler = nullptr;
    DrawHandlerFunc _DrawEventHandler = nullptr;
    WindowHandlerFunc _WindowEventHandler = nullptr;
    MouseHandlerFunc _MouseEventHandler = nullptr;
    KeyboardHandlerFunc _KeypressEventHandler = nullptr;
};

