#include "StateWriter.h"

#include <Leveque/Util/IO/FileWriter.h>

namespace Jabre::Leveque::OneDimensional {
    void writeStateToCsvFile(const State& state, std::filesystem::path path) {
        CsvWriter writer(path);
        const Grid& grid = state.grid();
        const std::vector<Field> fields = state.fields(),
                                 auxilliaryFields = state.auxilliaryFields();

        writer.startFile("Position");
        for (const Field& field : fields) {
            writer.addColumn(field.name());
        }
        for (const Field& auxilliaryField : auxilliaryFields) {
            writer.addColumn(auxilliaryField.name());
        }

        int numCells = grid.numCells();
        int numGhostCells = grid.numGhostCells();

        // Write left boundary values
        writer.startColumn(grid.point(numGhostCells));
        for (const Field& field : fields) {
            const std::vector<double>& values = field.values();
            double value = 0.5*(values[numGhostCells - 1] +
                           values[numGhostCells]);
            writer.addColumn(value);
        }
        for (const Field& auxilliaryField : auxilliaryFields) {
            const std::vector<double>& values = auxilliaryField.values();
            double value =
                0.5 * (values[numGhostCells - 1] + values[numGhostCells]);
            writer.addColumn(value);
        }

        // Write interior values
        for (int i = numGhostCells; i < numCells + numGhostCells; i++) {
            writer.startColumn(grid.point(numGhostCells));
            for (const Field& field : fields) {
                const std::vector<double>& values = field.values();
                writer.addColumn(values[i]);
            }
            for (const Field& auxilliaryField : auxilliaryFields) {
                const std::vector<double>& values = auxilliaryField.values();
                writer.addColumn(values[i]);
            }
        }

        // Write right boundary value
        writer.startColumn(grid.point(numGhostCells + numCells));
        for (const Field& field : fields) {
            const std::vector<double>& values = field.values();
            double value = 0.5 * (values[numGhostCells + numCells - 1] +
                                  values[numGhostCells + numCells]);
            writer.addColumn(value);
        }
        for (const Field& auxilliaryField : auxilliaryFields) {
            const std::vector<double>& values = auxilliaryField.values();
            double value = 0.5 * (values[numGhostCells + numCells - 1] +
                                  values[numGhostCells + numCells]);
            writer.addColumn(value);
        }
    }
}  // namespace Jabre::Leveque::OneDimensional