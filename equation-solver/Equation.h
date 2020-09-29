//
// Created by adman on 26.09.2020.
//

#ifndef EQUATION_RESOLVER_EQUATION_H
#define EQUATION_RESOLVER_EQUATION_H


#include <vector>
#include "EquationRoot.h"

class Equation {
private:
    std::vector<double> *coef;
    std::vector<EquationRoot> *roots;
    Equation *derivative;
    unsigned int degree;

    void calcDerivative();
    double getDiscriminant();
    double findRoot(double accuracy, double stepSize, double leftBorder, double rightBorder);
public:
    explicit Equation(std::vector<double> &coef);
    void calcRoots(double accuracy, double stepSize);
    double getValue(double x);
    std::vector<EquationRoot> getRoots();
    ~Equation();
};


#endif //EQUATION_RESOLVER_EQUATION_H
