#include "EventHandlers.h"

/* Event Handlers*/
void InitHandler()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    CELL_GRID = new Grid{ WINDOW_WIDTH, WINDOW_HEIGHT, 40 };
    CELL_GRID->ConstructGrid();
}

void DrawHandler()
{
    glClearColor(0.0f, 0.15f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    glTranslatef(0.0f, 0.0f, -8.0f);
    /*glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(_angleY, 0.0f, 1.0f, 0.0f);*/

//    glLineWidth(2.0f);

    glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
    DrawCellGrid(*CELL_GRID);
}

// Called when a keyboard key is pressed
void KeyboardButtonHandler(SDL_KeyboardEvent evt)
{
}

//Called when the mouse button is pressed
void MouseButtonHandler(SDL_MouseButtonEvent evt)
{
}
