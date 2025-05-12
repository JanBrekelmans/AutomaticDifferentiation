#include <doctest/doctest.h>

#include <Leveque/OneDimensional/Grid/Grid.h>

TEST_CASE("Grid test") {
    using namespace Jabre::Leveque::OneDimensional;
    constexpr int numCells = 10;
    constexpr double xMin = 0.0, xMax = 1.0;
    constexpr int numGhostCells = 2;
    constexpr double dx = (xMax - xMin) / numCells;

    Grid g(numCells, xMin, xMax, numGhostCells);
    REQUIRE(g.numCells() == numCells);
    REQUIRE(g.numGhostCells() == numGhostCells);
    for (int cellIndex = -numGhostCells; cellIndex < numCells + numGhostCells; cellIndex++) {
        REQUIRE(g.dx(cellIndex) == doctest::Approx(dx));
        REQUIRE(g.cellCentre(cellIndex) == doctest::Approx(xMin + (cellIndex + 0.5) * dx));
    }

    for (int pointIndex = -numGhostCells; pointIndex <= numCells + numGhostCells; pointIndex++) {
        REQUIRE(g.point(pointIndex) == doctest::Approx(xMin + pointIndex * dx));
    }
}