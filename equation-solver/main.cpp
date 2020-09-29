#include <iostream>
#include "Equation.h"

int main() {
    double a, b, c, eps, delta;
    std::cout << "Enter a, b, c, eps, delta" << std::endl;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> eps;
    std::cin >> delta;
    std::vector<double> coef = std::vector<double>();
    coef.push_back(1);
    coef.push_back(a);
    coef.push_back(b);
    coef.push_back(c);
    Equation equation = Equation(coef);
    equation.calcRoots(eps, delta);

    int i = 1;
    for (auto &root : equation.getRoots()) {
        std::cout << "x" << i++ << " = " << root.getValue() << ", multiplicity: " << root.getMultiplicity() << std::endl;
    }
    return 0;
}
