#include "GridHelper.h"

string Helpers::GetCellKey(int i, int j, int k)
{
    stringstream stream;
    stream << i << "," << j << "," << k;

    return stream.str();
}

Velocity Helpers::ComputeParticleVelocity(Grid* grid, Particle* particle)
{
    float u, v;

    auto dim = grid->GetCellDimensions();

    auto px = particle->X;
    auto py = particle->Y;
    auto pz = particle->Z;

    auto dim_2 = dim / 2;
    auto dim_sq = pow(dim, 2);

    vector<Coordinate> particleBounds = {
        Coordinate(px - dim_2, py + dim_2), // top left
        Coordinate(px + dim_2, py + dim_2), // top right
        Coordinate(px + dim_2, py - dim_2), // bottom right
        Coordinate(px - dim_2, py - dim_2) // bottom left
    };

    vector<FluidCell*> neighborCells = {
        grid->GetCellAtCoordinate(particleBounds[0]), // top left
        grid->GetCellAtCoordinate(particleBounds[1]), // top right
        grid->GetCellAtCoordinate(particleBounds[2]), // bottom right
        grid->GetCellAtCoordinate(particleBounds[3]), // bottom left
    };

    // Area Interpolation
    Coordinate pbrk;
    float a1, a2, a3, a4;

    if (neighborCells[1] != nullptr)
    {
        pbrk = neighborCells[1]->GetCoordinates();
    }
    else if (neighborCells[0] != nullptr)
    {
        pbrk = neighborCells[0]->GetCoordinates();
        pbrk.X += dim;
    }
    else if (neighborCells[2] != nullptr)
    {
        pbrk = neighborCells[2]->GetCoordinates();
        pbrk.Y += dim;
    }
    else if (neighborCells[3] != nullptr)
    {
        pbrk = neighborCells[3]->GetCoordinates();
        pbrk.X += dim;
        pbrk.Y += dim;
    }

    a1 = abs(pbrk.X - particleBounds[0].X) * abs(pbrk.Y - particleBounds[0].Y) / dim_sq;
    a2 = abs(pbrk.X - particleBounds[1].X) * abs(pbrk.Y - particleBounds[1].Y) / dim_sq;
    a3 = abs(pbrk.X - particleBounds[2].X) * abs(pbrk.Y - particleBounds[2].Y) / dim_sq;
    a4 = abs(pbrk.X - particleBounds[3].X) * abs(pbrk.Y - particleBounds[3].Y) / dim_sq;

    // Compute U
    u = (neighborCells[0] == nullptr ? 0 : (a1 * neighborCells[0]->U)) +
        (neighborCells[1] == nullptr ? 0 : (a2 * neighborCells[1]->U)) +
        (neighborCells[2] == nullptr ? 0 : (a3 * neighborCells[2]->U)) +
        (neighborCells[3] == nullptr ? 0 : (a4 * neighborCells[3]->U));

    // Compute V
    v = (neighborCells[0] == nullptr ? 0 : (a1 * neighborCells[0]->V)) +
        (neighborCells[1] == nullptr ? 0 : (a2 * neighborCells[1]->V)) +
        (neighborCells[2] == nullptr ? 0 : (a3 * neighborCells[2]->V)) +
        (neighborCells[3] == nullptr ? 0 : (a4 * neighborCells[3]->V));

    return Velocity(u, v);
}
