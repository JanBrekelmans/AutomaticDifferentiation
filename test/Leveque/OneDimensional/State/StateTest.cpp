#include <doctest/doctest.h>

#include <Leveque/OneDimensional/State/State.h>
#include <stdexcept>

TEST_CASE("State test") {
    using namespace Jabre::Leveque::OneDimensional;
    constexpr int numCells = 10;
    constexpr double xMin = 0.0, xMax = 1.0;
    constexpr int numGhostCells = 2;
    const std::string fieldName = "q";

    Grid g(numCells, xMin, xMax, numGhostCells);
    State s(g, {fieldName});

    const Field& f = s.field(fieldName);
    REQUIRE(f.name() == fieldName);
    REQUIRE(f.values().size() == numCells + 2 * numGhostCells);
    REQUIRE(&f.grid() == &g);

    REQUIRE(s.time() == doctest::Approx(0.0));

    CHECK_THROWS_AS(s.field("non existant"), const std::runtime_error&);
}