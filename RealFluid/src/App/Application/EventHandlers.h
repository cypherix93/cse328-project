#pragma once

#include "Application.h"
#include <Core/Fluid/Grid/Grid.h>
#include <App/Drawing/GridDrawer/GridDrawer.h>

using namespace std;

static Grid* CELL_GRID;
static GridDrawOptions* CELL_GRID_OPTIONS;

void InitHandler();
void DrawHandler();
void KeyboardButtonHandler(SDL_KeyboardEvent evt);
void MouseButtonHandler(SDL_MouseButtonEvent evt);
