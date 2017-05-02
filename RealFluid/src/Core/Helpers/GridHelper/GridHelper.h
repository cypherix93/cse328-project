#pragma once
#include <string>
#include <sstream>
#include <Core/Fluid/Particle/Particle.h>
#include <Core/Fluid/Grid/Grid.h>
#include <Core/Physics/Models/Velocity.h>

using namespace std;

namespace Helpers
{
    string GetCellKey(int i, int j, int k);

    Velocity ComputeParticleVelocity(Grid* grid, Particle* particle);
}
