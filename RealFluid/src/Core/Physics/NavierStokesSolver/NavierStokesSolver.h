#pragma once
#include <Core/Fluid/Grid/Grid.h>

#define MIN_DIVERGENCE 0.0001
#define BETA_0 1.7


/* Public */
void ProcessGrid(Grid grid);

/* Private */
static float ComputeDivergence(FluidCell cell);
static float ComputeBeta(FluidCell cell);
static float ComputeDeltaPressure(float beta, float divergence);