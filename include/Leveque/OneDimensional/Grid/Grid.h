#pragma once

#include <vector>

namespace Jabre::Leveque::OneDimensional {
    class Grid {
       public:
        Grid() = delete;
        Grid(int numCells, double xMin, double xMax, int numGhostCells = 2);

        double dx(int cellIndex) const;
        double cellCentre(int cellIndex) const;
        double point(int pointIndex) const;

        int numCells() const;
        int numGhostCells() const;
        int numTotalCells() const;

       private:
        double xMin_, xMax_, dx_;
        int numCells_, numGhostCells_;
    };
}  // namespace Jabre::Leveque::OneDimensional