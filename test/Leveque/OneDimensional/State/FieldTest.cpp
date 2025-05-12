#include <doctest/doctest.h>

#include <Leveque/OneDimensional/State/Field.h>

TEST_CASE("Field test") {
    using namespace Jabre::Leveque::OneDimensional;
    constexpr int numCells = 10;
    constexpr double xMin = 0.0, xMax = 1.0;
    constexpr int numGhostCells = 2;
    const std::string fieldName = "q";

    Grid g(numCells, xMin, xMax, numGhostCells);
    Field f(g, fieldName);

    REQUIRE(f.name() == fieldName);
    REQUIRE(f.values().size() == numCells + 2 * numGhostCells);
    REQUIRE(&f.grid() == &g);
}