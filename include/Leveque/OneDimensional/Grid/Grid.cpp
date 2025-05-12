#include "Grid.h"

namespace Jabre::Leveque::OneDimensional {
    Grid::Grid(int numCells, double xMin, double xMax, int numGhostCells)
        : numCells_(numCells),
          xMin_(xMin),
          xMax_(xMax),
          numGhostCells_(numGhostCells) {
        dx_ = (xMax - xMin) / numCells;
    }

    double Grid::dx(int cellIndex) const {
        return dx_;
    }

    double Grid::cellCentre(int cellIndex) const {
        return xMin_ + (cellIndex + 0.5) * dx_;
    }

    double Grid::point(int pointIndex) const {
        return pointIndex * dx_;
    }

    int Grid::numCells() const {
        return numCells_;
    }

    int Grid::numGhostCells() const {
        return numGhostCells_;
    }

    int Grid::numTotalCells() const {
        return numCells() + 2 * numGhostCells();
    }
}  // namespace Jabre::Leveque::OneDimensional