#pragma once

class Particle
{
    public:
    Particle(int x, int y, int z);
    virtual ~Particle();

    int X, Y, Z;

    void MoveBy(float u, float v, float w);
};

