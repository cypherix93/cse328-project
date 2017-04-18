#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <Core/Fluid/Particle/Particle.h>
#include <Core/Fluid/Grid/Grid.h>
#include <Core/Physics/Models/Coordinate.h>

using namespace std;

namespace Helpers
{
    string GetCellKey(int i, int j, int k);
    vector<float> ComputeParticleVelocity(Grid* grid, Particle* particle);
}
