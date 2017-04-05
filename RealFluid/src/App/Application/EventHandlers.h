#pragma once

#include "Application.h"
#include <Core/Fluid/Grid/Grid.h>
#include <App/Drawing/GridDrawer/GridDrawer.h>

using namespace std;

static Grid* CELL_GRID;

void InitHandler();
void DrawHandler();
void KeyboardButtonHandler(SDL_KeyboardEvent);
void MouseButtonHandler(SDL_MouseButtonEvent);
