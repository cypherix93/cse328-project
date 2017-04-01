#pragma once

#include "Application.h"

using namespace std;

void InitHandler();
void DrawHandler();
void KeyboardButtonHandler(SDL_KeyboardEvent);
void MouseButtonHandler(SDL_MouseButtonEvent);


void RotationHandler(SDL_Keycode key);
void ZoomHandler(SDL_Keycode key);
void StateHandler(SDL_Keycode key);