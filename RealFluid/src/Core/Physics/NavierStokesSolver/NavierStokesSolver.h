#pragma once
#include <Core/Fluid/Grid/Grid.h>

#define EPSILON 0.0001
#define BETA_0 1.7

struct UpdatedCellValues
{
    int I;
    int J;
    int K;

    float U;
    float V;
    float W;
    
    float Pressure;
};

/* Public */
void ProcessGrid(Grid* grid);

/* Private */
static vector<UpdatedCellValues> UpdatedCellValuesBuffer;
static void UpdateCellValues(Grid* grid);

static void ComputeNewVelocities(Grid* grid);

static void AdjustBoundaryConditions(Grid* grid);
static void AdjustForIncompressibility(Grid* grid);

static void AddParticles(Grid* grid);
static void UpdateCellsWithParticles(Grid* grid);
static void MoveParticles(Grid* grid);
