#include <doctest/doctest.h>

#include <Leveque/OneDimensional/BoundaryConditions/PeriodicBoundaryConditions.h>

TEST_CASE("Periodic Boundary Conditions test") {
    using namespace Jabre::Leveque::OneDimensional;
    constexpr int numCells = 10;
    constexpr double xMin = 0.0, xMax = 1.0;
    constexpr int numGhostCells = 2;
    const std::string fieldName = "q";

    Grid g(numCells, xMin, xMax, numGhostCells);
    State s(g, {fieldName});
    PeriodicBoundaryConditions pbc(fieldName);

    Field& f = s.field(fieldName);
    std::vector<double>& values = f.values();
    for (int i = 0; i < numGhostCells; i++) {
        values[i + numGhostCells] = 2+i;
        values[i + numCells] = 4 + i;
    }

    pbc.apply(f);
    for (int i = 0; i < numGhostCells; i++) {
        REQUIRE(values[i] == doctest::Approx(4 + i));
        REQUIRE(values[i + numCells + numGhostCells] == doctest::Approx(2 + i));
    }
}