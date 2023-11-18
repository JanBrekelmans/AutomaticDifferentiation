#include <AutomaticDifferentiation/Forward.h>

#include <iostream>

int main() {
    using namespace AD::Forward;

    dual x = 1.0;
    dual y = 2.0;

    seed(x);

    x = x + x + x;

    std::cout << x.a << "\t" << x.b;
}