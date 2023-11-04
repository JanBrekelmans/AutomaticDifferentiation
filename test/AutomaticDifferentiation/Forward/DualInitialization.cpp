#include <doctest/doctest.h>

#include <AutomaticDifferentiation/Forward.h>

TEST_CASE("Dual default initialization") {
    using namespace AD::Forward;

    Dual<double> x;
    CHECK(x.a == 0.0);
    CHECK(x.b == 0.0);
}

TEST_CASE("Dual initialization to scalar") {
    using namespace AD::Forward;

    Dual<double> x = 2.0;
    CHECK(x.a == 2.0);
    CHECK(x.b == 0.0);
}

TEST_CASE("Dual initialization to other dual") {
    using namespace AD::Forward;

    Dual<double> y = 2.0;
    Dual<double> x = y;
    CHECK(x.a == y.a);
    CHECK(x.b == y.b);
}
