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

    dual x = +(+ y);

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
    seed(x);

    dual y = sin(x);

    CHECK(y.a == sin(1.0));
    CHECK(y.b == cos(1.0));
}

TEST_CASE("Cos operator") {
    using namespace AD::Forward;

    dual x = 1.0;
    seed(x);

    dual y = cos(x);

    CHECK(y.a == cos(1.0));
    CHECK(y.b == -sin(1.0));
}
