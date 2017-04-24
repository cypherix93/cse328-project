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
    glEnable(GL_POINT_SMOOTH);
    glShadeModel(GL_SMOOTH);

    CELL_GRID = new Grid{ 16, 16, 0 };

    CELL_GRID_OPTIONS = new GridDrawOptions();
    CELL_GRID_OPTIONS->CellDimensions = 40;

    int windowWidth, windowHeight;
    windowWidth = CELL_GRID->CellsX * CELL_GRID_OPTIONS->CellDimensions;
    windowHeight = CELL_GRID->CellsY * CELL_GRID_OPTIONS->CellDimensions;

    APPLICATION->GetWindowManager()->ResizeWindow(windowWidth, windowHeight);

    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //    gluPerspective(45.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 200.0);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
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

    //options.DrawCellOutline = false;
    DrawCellGrid(CELL_GRID, CELL_GRID_OPTIONS);
}

// Called when a keyboard key is pressed
void KeyboardButtonHandler(SDL_KeyboardEvent evt)
{
}

//Called when the mouse button is pressed
void MouseButtonHandler(SDL_MouseButtonEvent evt)
{
}
