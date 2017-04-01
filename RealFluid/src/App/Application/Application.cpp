#include "Application.h"

/* Constructor */
Application::Application()
{
    _WindowManager = new WindowManager();
}

/* Destructor */
Application::~Application()
{
    free(_WindowManager);
}

/* Public Methods*/
void Application::Setup()
{
    //Set handler functions
    _WindowManager->OnInit(InitHandler);
    _WindowManager->OnDrawEvent(DrawHandler);

    _WindowManager->OnKeyboardEvent(KeyboardButtonHandler);
    _WindowManager->OnMouseEvent(MouseButtonHandler);
}

void Application::Start()
{
    Setup();

    // Open GLUT Window
    _WindowManager->OpenWindow("CSE 328 Assignment 1", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Start Window Lifecycle
    _WindowManager->Start();
}
