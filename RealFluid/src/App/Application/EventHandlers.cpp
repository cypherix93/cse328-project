#include "EventHandlers.h"
#include <Core/Physics/NavierStokesSolver/NavierStokesSolver.h>

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

//    gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 200.0);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);

    CELL_GRID = new Grid{ WINDOW_WIDTH, WINDOW_HEIGHT, 40 };
}

void DrawHandler()
{
    ProcessGrid(CELL_GRID);

    glClearColor(0.0f, 0.10f, 0.20f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//    glTranslatef(0.0f, 0.0f, -8.0f);
    /*glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(_angleY, 0.0f, 1.0f, 0.0f);*/

//    glLineWidth(2.0f);

    GridDrawOptions options;
//    options.DrawCellOutline = false;
    DrawCellGrid(CELL_GRID, &options);
}

// Called when a keyboard key is pressed
void KeyboardButtonHandler(SDL_KeyboardEvent evt)
{
}

//Called when the mouse button is pressed
void MouseButtonHandler(SDL_MouseButtonEvent evt)
{
}
