#include <AutomaticDifferentiation/Forward.h>

#include <iostream>

using namespace AD::Forward;

dual f(dual x) { return 5 + x - exp(x); }

int main() {
    double xInit = 1.0;
    dual xCurrent = xInit;

    double precision = 1e-5;
    int iterations = 0;

    while (abs(f(xCurrent).a) > precision) {
        auto [y, dy] = derivative(f, at(xCurrent), xCurrent);

        xCurrent = xCurrent - y / dy;
        iterations++;
    }

    std::cout << "The found root is " << xCurrent.a << "\n"
              << "With initial guess " << xInit << "\n"
              << "Found in " << iterations << " iteration(s)";
}
