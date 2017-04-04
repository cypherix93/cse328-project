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
    omp_set_dynamic(0);
    auto t = omp_get_max_threads();
    omp_set_num_threads(t);

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
    _WindowManager->OpenWindow("Real Fluid - CSE 328 Project", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Start Window Lifecycle
    _WindowManager->Start(5);
}
