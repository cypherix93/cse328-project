#pragma once

class Particle
{
    public:
    Particle(float x, float y, float z);
    virtual ~Particle();

    float X, Y, Z;

    void MoveBy(float u, float v, float w);
};

