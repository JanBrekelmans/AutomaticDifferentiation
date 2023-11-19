#include <AutomaticDifferentiation/Forward.h>

#include <iostream>

int main() {
    using namespace AD::Forward;
    dual x = 3.0;
    auto f = [](dual t) -> dual { return pow(t, 2.0); };
    auto [y, dy] = derivative(f, at(x), x);
}