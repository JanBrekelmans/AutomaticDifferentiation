#include <doctest/doctest.h>

#include <AutomaticDifferentiation/Forward.h>

TEST_CASE("Addition operator 1") {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = x + x;
    CHECK(y.a == 2.0);
}

TEST_CASE("Addition operator 2") {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = x + x + x;
    CHECK(y.a == 3.0);
}

TEST_CASE("Addition operator nested") {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = x + (x + x);
    dual z = (x + x) + x;
    CHECK(y.a == 3.0);
    CHECK(z.a == 3.0);
}