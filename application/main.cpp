#include <AutomaticDifferentiation/Forward.h>

#include <iostream>

int main() {
    using namespace AD::Forward;

    dual x = 2.0;
    auto v = x - x - x;

    auto w = 5 * x * 5;

    auto f = [](dual t) -> dual { return 1/t; };
    auto [y, dy] = derivative(f, at(x), x);
    
    std::cout << y << "\t" << dy;
}