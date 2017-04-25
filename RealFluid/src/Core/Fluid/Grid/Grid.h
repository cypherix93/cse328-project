#pragma once
#include <map>

#include <Core/Fluid/Particle/Particle.h>
#include <Core/Fluid/Cell/FluidCell.h>
#include <Core/Physics/Models/Coordinate.h>

using namespace std;

class Grid
{
    public:
    Grid(int xCells, int yCells, int zCells);
    virtual ~Grid();

    int CellsX, CellsY, CellsZ;

    // Grid Operations
    map<string, FluidCell*>* GetCellsMap();
    vector<FluidCell*>* GetCellsVector();
    vector<Particle*>* GetParticlesVector();

    // Cell Operations
    FluidCell* GetCellAtIndex(int i, int j, int k);
    FluidCell* GetCellAtCoordinate(Coordinate coord);
    
    void AddParticle(FluidCell* cell);


    float GetCellU(int i, int j, int k) { if (IsBoundaryU(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->U; }
    float GetCellV(int i, int j, int k) { if (IsBoundaryV(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->V; }
    float GetCellW(int i, int j, int k) { if (IsBoundaryW(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->W; }

    float GetCellAverageU(int i, int j, int k) { return (GetCellU(i - 1, j, k) + GetCellU(i, j, k)) * 0.5; }
    float GetCellAverageV(int i, int j, int k) { return (GetCellV(i, j - 1, k) + GetCellV(i, j, k)) * 0.5; }
    float GetCellAverageW(int i, int j, int k) { return (GetCellW(i, j, k - 1) + GetCellW(i, j, k)) * 0.5; }

    float GetCellUV(int i, int j, int k) { return GetCellAverageU(i, j, k) * GetCellAverageV(i, j, k); }
    float GetCellVW(int i, int j, int k) { return GetCellAverageV(i, j, k) * GetCellAverageW(i, j, k); }
    float GetCellWU(int i, int j, int k) { return GetCellAverageW(i, j, k) * GetCellAverageU(i, j, k); }

    bool IsBoundaryU(int i, int j, int k) { if (i >= 0 && i < CellsX - 1 && j >= 0 && j < CellsY && k >= 0 && k < CellsZ) return false; return true; }
    bool IsBoundaryV(int i, int j, int k) { if (i >= 0 && i < CellsX && j >= 0 && j < CellsY - 1 && k >= 0 && k < CellsZ) return false; return true; }
    bool IsBoundaryW(int i, int j, int k) { if (i >= 0 && i < CellsX && j >= 0 && j < CellsY && k >= 0 && k < CellsZ - 1) return false; return true; }

    float GetCellPressure(int i, int j, int k) { if (IsBoundaryU(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->Pressure; }


    private:
    map<string, FluidCell*> CellsMap;
    vector<FluidCell*> CellsVector;

    vector<Particle*> ParticlesVector;

    void ConstructGrid();
    void DestructGrid();
};

