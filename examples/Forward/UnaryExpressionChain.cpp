#include <AutomaticDifferentiation/Forward.h>

#include <iostream>

using namespace AD::Forward;

constexpr auto f(const dual& x) { return cos(sin(x)); }

int main() {
    dual x = 1.0;
    auto [y, dy] = derivative(f, at(x), x);

    std::cout << "The value of f at x is: " << y << "\n"
              << "The value of df/dx at x is: " << dy << "\n";

    return 0;
}
