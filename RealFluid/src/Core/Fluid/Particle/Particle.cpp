#include "Particle.h"

Particle::Particle(float x, float y, float z)
{
    X = x;
    Y = y;
    Z = z;
}


Particle::~Particle()
{
}

void Particle::MoveBy(float u, float v, float w)
{
    X += u;
    Y += v;
    Z += w;
}
