#pragma once
#include <Core/Fluid/Grid/Grid.h>
#include <omp.h>

#define EPSILON 0.1
#define BETA_0 1.7


/* Public */
void ProcessGrid(Grid* grid);

/* Private */
static void ComputeNewVelocities(Grid* grid);
static void AdjustForIncompressibility(Grid* grid);

static float ComputeDivergence(FluidCell* cell);
static float ComputeBeta(FluidCell* cell);
static float ComputeDeltaPressure(float beta, float divergence);