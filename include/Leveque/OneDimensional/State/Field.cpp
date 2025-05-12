#include "Field.h"

namespace Jabre::Leveque::OneDimensional {
    Field::Field(const Grid& grid, const std::string& name)
        : grid_(grid), name_(name) {
        values_ = std::vector<double>(
            grid.numCells() + 2 * grid.numGhostCells(), 0.0);
    }

    const Grid& Field::grid() const {
        return grid_;
    }

    const std::string& Field::name() const {
        return name_;
    }

    const std::vector<double>& Field::values() const {
        return values_;
    }

    std::vector<double>& Field::values() {
        return values_;
    }
}  // namespace Jabre::Leveque::OneDimensional