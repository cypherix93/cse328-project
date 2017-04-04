#pragma once
#include <Core/Fluid/Grid/Grid.h>
#include <Core/Helpers/NavierStokesHelper/NavierStokesHelper.h>

#define EPSILON 0.1
#define BETA_0 1.7

struct UpdatedCellVector
{
    int I;
    int J;
    int K;

    float U;
    float V;
    float W;
};

/* Public */
void ProcessGrid(Grid* grid);

/* Private */
static vector<UpdatedCellVector> UpdatedCellVectorBuffer;

static void UpdateNewVelocities(Grid* grid);
static void ComputeNewVelocities(Grid* grid);

static void AdjustBoundaryConditions(Grid* grid);
static void AdjustForIncompressibility(Grid* grid);

static void MoveParticles(Grid* grid);

static float ComputeDivergence(FluidCell* cell);
static float ComputeBeta(FluidCell* cell);
static float ComputeDeltaPressure(float beta, float divergence);
