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

TEST_CASE("Addition Operator 3") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return t + t; };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == 2.0);
    CHECK(dy == 2.0);
}

TEST_CASE("Addition Operator 4") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return sin(t) + cos(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == sin(1.0) + cos(1.0));
    CHECK(dy == cos(1.0) - sin(1.0));
}

TEST_CASE("Addition Operator 5") {
    using namespace AD::Forward;
    dual v = 1.0;
    dual w = 2.0;
    auto f = [](dual s, dual t) -> dual { return s + t; };
    auto [y, dy] = derivative(f, at(v, w), v);

    CHECK(y == 1.0 + 2.0);
    CHECK(dy == 1.0);
}

TEST_CASE("Addition operator nested") {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = x + (x + x);
    dual z = (x + x) + x;
    CHECK(y.a == 3.0);
    CHECK(z.a == 3.0);
}

TEST_CASE("Subtraction operator 1") {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = x - x;
    CHECK(y.a == 0.0);
}

TEST_CASE("Subtraction operator 2") {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = x - x - x;
    CHECK(y.a == -1.0);
}

TEST_CASE("Subtraction Operator 3") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return -t - t; };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == -2.0);
    CHECK(dy == -2.0);
}

TEST_CASE("Subtraction Operator 4") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return sin(t) - cos(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == sin(1.0) - cos(1.0));
    CHECK(dy == cos(1.0) + sin(1.0));
}

TEST_CASE("Subtraction Operator 5") {
    using namespace AD::Forward;
    dual v = 1.0;
    dual w = 2.0;
    auto f = [](dual s, dual t) -> dual { return s - t; };
    auto [y, dy] = derivative(f, at(v, w), v);

    CHECK(y == 1.0 - 2.0);
    CHECK(dy == 1.0);
}

TEST_CASE("Subtraction operator nested") {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = x - (x - x);
    dual z = (x - x) - x;
    CHECK(y.a == 1.0);
    CHECK(z.a == -1.0);
}

TEST_CASE("Multiplication operator 1") {
    using namespace AD::Forward;

    dual x = 2.0;
    dual y = x * x;
    CHECK(y.a == 4.0);
}

TEST_CASE("Multiplication operator 2") {
    using namespace AD::Forward;

    dual x = 2.0;
    dual y = x * x * x;
    CHECK(y.a == 8.0);
}

TEST_CASE("Multiplication Operator 3") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return t * t; };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == 1.0);
    CHECK(dy == 2.0);
}

TEST_CASE("Multiplication Operator 4") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return sin(t) * cos(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == sin(1.0) * cos(1.0));
    CHECK(dy == cos(1.0) * cos(1.0) - sin(1.0) * sin(1.0));
}

TEST_CASE("Multiplication Operator 5") {
    using namespace AD::Forward;
    dual v = 1.0;
    dual w = 2.0;
    auto f = [](dual s, dual t) -> dual { return s * t; };
    auto [y, dy] = derivative(f, at(v, w), v);

    CHECK(y == 1.0 * 2.0);
    CHECK(dy == 2.0);
}

TEST_CASE("Multiplication operator nested") {
    using namespace AD::Forward;

    dual x = 2.0;
    dual y = x * (x * x);
    dual z = (x * x) * x;
    CHECK(y.a == 8.0);
    CHECK(z.a == 8.0);
}

TEST_CASE("Division operator 1") {
    using namespace AD::Forward;

    dual x = 2.0;
    dual y = 1 / x;
    CHECK(y.a == 0.5);
}

TEST_CASE("Division operator 2") {
    using namespace AD::Forward;

    dual x = 2.0;
    dual y = 1 / x / x;
    CHECK(y.a == 0.25);
}

TEST_CASE("Division Operator 3") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return 1/t; };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == 1.0);
    CHECK(dy == -1.0);
}

TEST_CASE("Division Operator 4") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [](dual t) -> dual { return sin(t) / cos(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(doctest::Approx(y) == tan(1.0));
    CHECK(dy == 1/(cos(1.0)*cos(1.0)));
}

TEST_CASE("Division Operator 5") {
    using namespace AD::Forward;
    dual v = 1.0;
    dual w = 2.0;
    auto f = [](dual s, dual t) -> dual { return t/s; };
    auto [y, dy] = derivative(f, at(v, w), v);

    CHECK(y == 2.0);
    CHECK(dy == -2.0);
}

TEST_CASE("Division operator nested") {
    using namespace AD::Forward;

    dual x = 2.0;
    dual y = x / (x / x);
    dual z = (x / x) / x;
    CHECK(y.a == 2.0);
    CHECK(z.a == 1.0/2.0);
}