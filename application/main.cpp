#include <AutomaticDifferentiation/Forward.h>

#include <iostream>
#include <memory>
#include <vector>

using namespace AD::Forward;

int main() {
    Dual<double> x = 3.0;
    Dual<double> b;
    seed(x);
    x = x*x*x; 

    auto f = IsArithmetic<AdditionExpression<double, double>&> || IsExpression<AdditionExpression<double, double>&>;


    auto i = 1;
    std::cout << b.a;
}