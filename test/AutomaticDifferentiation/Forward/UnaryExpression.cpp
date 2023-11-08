#include <doctest/doctest.h>

#include <AutomaticDifferentiation/Forward.h>

TEST_CASE("Positive operator") {
    using namespace AD::Forward;
    dual y = 2.0;

    dual x = +y;

    CHECK(x.a == y.a);
    CHECK(x.b == y.b);
}

TEST_CASE("Nested positive operators") {
    using namespace AD::Forward;
    dual y = 2.0;

    dual x = +(+y);

    CHECK(x.a == y.a);
    CHECK(x.b == y.b);
}

TEST_CASE("Negative operator") {
    using namespace AD::Forward;

    dual y = 2.0;
    dual x = -y;

    CHECK(x.a == -y.a);
    CHECK(x.b == -y.b);
}

TEST_CASE("Nested negative operators") {
    using namespace AD::Forward;
    dual y = 2.0;

    dual x = -(-y);

    CHECK(x.a == y.a);
    CHECK(x.b == y.b);
}

TEST_CASE("Sin operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    auto f = [&](dual t) { return sin(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == sin(1.0));
    CHECK(dy == cos(1.0));
}

TEST_CASE("Cos operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    auto f = [&](dual t) { return cos(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == cos(1.0));
    CHECK(dy == -sin(1.0));
}

TEST_CASE("Tan operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    auto f = [&](dual t) { return tan(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == tan(1.0));
    CHECK(dy == 1 / (cos(1.0) * cos(1.0)));
}

TEST_CASE("Asin operator") {
    using namespace AD::Forward;

    dual x = 0.5;
    auto f = [&](dual t) { return asin(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == asin(0.5));
    CHECK(dy == 1 / sqrt(1 - 0.5 * 0.5));
}

TEST_CASE("Acos operator") {
    using namespace AD::Forward;

    dual x = 0.5;
    auto f = [&](dual t) { return acos(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == acos(0.5));
    CHECK(dy == -1 / sqrt(1 - 0.5 * 0.5));
}

TEST_CASE("Atan operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    auto f = [&](dual t) { return atan(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == atan(1.0));
    CHECK(dy == 1.0 / (1 + 1 * 1));
}

TEST_CASE("Sinh operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    auto f = [&](dual t) { return sinh(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == sinh(1.0));
    CHECK(dy == cosh(1.0));
}

TEST_CASE("Cosh operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    auto f = [&](dual t) { return cosh(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == cosh(1.0));
    CHECK(dy == sinh(1.0));
}

TEST_CASE("Tanh operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    auto f = [&](dual t) { return tanh(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == tanh(1.0));
    CHECK(dy == 1.0 / (cosh(1.0) * cosh(1.0)));
}

TEST_CASE("Exp operator") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [&](dual t) { return exp(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == exp(1.0));
    CHECK(dy == exp(1.0));
}

TEST_CASE("Log operator") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [&](dual t) { return log(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == log(1.0));
    CHECK(dy == 1.0 / 1.0);
}

TEST_CASE("Sqrt operator") {
    using namespace AD::Forward;
    dual x = 1.0;
    auto f = [&](dual t) { return sqrt(t); };
    auto [y, dy] = derivative(f, at(x), x);

    CHECK(y == sqrt(1.0));
    CHECK(dy == 0.5 / sqrt(1.0));
}
