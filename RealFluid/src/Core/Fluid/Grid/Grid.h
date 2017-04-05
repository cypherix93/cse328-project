#pragma once
#include <map>

#include <Core/Helpers/GridHelper/GridHelper.h>
#include <Core/Fluid/Particle/Particle.h>
#include <Core/Fluid/Cell/FluidCell.h>

using namespace std;

class Grid
{
    public:
    Grid(int width, int height, int cellDimensions);
    virtual ~Grid();

    // Grid Operations
    map<string, FluidCell*>* GetCellsMap();
    vector<FluidCell*>* GetCellsVector();
    vector<Particle*>* GetParticlesVector();

    // Cell Operations
    FluidCell* GetCellAtIndex(int i, int j, int k);
    FluidCell* GetCellAtPixel(int x, int y, int z);

    vector<int> GetCellIndex(int x, int y, int z);

    void AddParticle(FluidCell* cell);


    float get_u_plus(int i, int j, int k) { if (u_boundary(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->U; }
    float get_v_plus(int i, int j, int k) { if (v_boundary(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->V; }
    float get_w_plus(int i, int j, int k) { if (w_boundary(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->W; }

    float get_u_avg(int i, int j, int k) { return 0.5*(get_u_plus(i - 1, j, k) + get_u_plus(i, j, k)); }
    float get_v_avg(int i, int j, int k) { return 0.5*(get_v_plus(i, j - 1, k) + get_v_plus(i, j, k)); }
    float get_w_avg(int i, int j, int k) { return 0.5*(get_w_plus(i, j, k - 1) + get_w_plus(i, j, k)); }

    float get_uv_plus(int i, int j, int k) {
        return 0.5*(get_u_plus(i, j, k) + get_u_plus(i, j + 1, k)) * 0.5*(get_v_plus(i, j, k) + get_v_plus(i + 1, j, k));
    }
    float get_uw_plus(int i, int j, int k) {
        return 0.5*(get_u_plus(i, j, k) + get_u_plus(i, j, k + 1)) * 0.5*(get_w_plus(i, j, k) + get_w_plus(i + 1, j, k));
    }
    float get_vw_plus(int i, int j, int k) {
        return 0.5*(get_v_plus(i, j, k) + get_v_plus(i, j, k + 1)) * 0.5*(get_w_plus(i, j, k) + get_w_plus(i, j + 1, k));
    }

    bool u_boundary(int i, int j, int k) { if (i >= 0 && i < CellsX - 1 && j >= 0 && j < CellsY && k >= 0 && k < CellsZ) return false; return true; }
    bool v_boundary(int i, int j, int k) { if (i >= 0 && i < CellsX && j >= 0 && j < CellsY - 1 && k >= 0 && k < CellsZ) return false; return true; }
    bool w_boundary(int i, int j, int k) { if (i >= 0 && i < CellsX && j >= 0 && j < CellsY && k >= 0 && k < CellsZ - 1) return false; return true; }

    float getPressure(int i, int j, int k) { if (u_boundary(i, j, k)) return 0; return GetCellAtIndex(i, j, k)->Pressure; }


    private:
    map<string, FluidCell*> CellsMap;
    vector<FluidCell*> CellsVector;

    vector<Particle*> ParticlesVector;

    int Width, Height;
    int CellsX, CellsY, CellsZ;
    int CellDimensions;

    void ConstructGrid();
    void DestructGrid();
};

