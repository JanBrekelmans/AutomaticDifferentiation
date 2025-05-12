#include "PeriodicBoundaryConditions.h"

namespace Jabre::Leveque::OneDimensional {
    namespace internal {
        void LeftPeriodicBoundaryCondition::applyOnLeft(Field& field) {
            const Grid& grid = field.grid();
            int numCells = grid.numCells();
            int numGhostCells = grid.numGhostCells();

            std::vector<double>& values = field.values();
            for (int i = 0; i < numGhostCells; i++) {
                values[i] = values[numCells + i];
            }
        }

        void RightPeriodicBoundaryCondition::applyOnRight(Field& field) {
            const Grid& grid = field.grid();
            int numCells = grid.numCells();
            int numGhostCells = grid.numGhostCells();

            std::vector<double>& values = field.values();
            for (int i = 0; i < numGhostCells; i++) {
                values[numCells + numGhostCells + i] =
                    values[numGhostCells + i];
            }
        }
    }  // namespace internal

    PeriodicBoundaryConditions::PeriodicBoundaryConditions(
        const std::string& fieldName)
        : BoundaryConditions(
              fieldName,
              std::shared_ptr<LeftBoundaryCondition>(
                  new internal::LeftPeriodicBoundaryCondition(fieldName)),
              std::shared_ptr<RightBoundaryCondition>(
                  new internal::RightPeriodicBoundaryCondition(fieldName))) {}
}  // namespace Jabre::Leveque::OneDimensional
