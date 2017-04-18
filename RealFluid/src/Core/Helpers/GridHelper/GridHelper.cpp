#include "GridHelper.h"

string Helpers::GetCellKey(int i, int j, int k)
{
    stringstream stream;
    stream << i << "," << j << "," << k;

    return stream.str();
}

vector<float> Helpers::ComputeParticleVelocity(Grid* grid, Particle* particle)
{
    float u = 0, v = 0, w = 0;

    auto dim = grid->GetCellDimensions();

    auto px = particle->X;
    auto py = particle->Y;
    auto pz = particle->Z;

    auto dx_2 = dim / 2;
    auto dy_2 = dim / 2;
    auto dz_2 = dim / 2;

    vector<Coordinate> particleBounds = {
        Coordinate(px - dx_2, py + dy_2), // top left
        Coordinate(px + dx_2, py + dy_2), // top right
        Coordinate(px + dx_2, py - dy_2), // bottom right
        Coordinate(px - dx_2, py - dy_2) // bottom left
    };

    vector<FluidCell*> neighborCells = {
        grid->GetCellAtCoordinate(particleBounds[0]), // top left
        grid->GetCellAtCoordinate(particleBounds[1]), // top right
        grid->GetCellAtCoordinate(particleBounds[2]), // bottom right
        grid->GetCellAtCoordinate(particleBounds[3]), // bottom left
    };

    // Area Interpolation
    auto pbrk = neighborCells[2]->GetCoordinates();
    float a1, a2, a3, a4;

    a1 = abs(pbrk.X - particleBounds[0].X) * abs(pbrk.Y - particleBounds[0].Y);
    a2 = abs(pbrk.X - particleBounds[1].X) * abs(pbrk.Y - particleBounds[1].Y);
    a3 = abs(pbrk.X - particleBounds[2].X) * abs(pbrk.Y - particleBounds[2].Y);
    a4 = abs(pbrk.X - particleBounds[3].X) * abs(pbrk.Y - particleBounds[3].Y);

    // Compute U
    u = (a1 * neighborCells[0]->U) +
        (a2 * neighborCells[1]->U) +
        (a3 * neighborCells[2]->U) +
        (a4 * neighborCells[3]->U);

    // Compute V
    v = (a1 * neighborCells[0]->V) +
        (a2 * neighborCells[1]->V) +
        (a3 * neighborCells[2]->V) +
        (a4 * neighborCells[3]->V);

    return{ u, v, w };
}
