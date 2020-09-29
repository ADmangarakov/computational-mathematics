//
// Created by adman on 26.09.2020.
//

#include "Equation.h"
#include <cmath>

void Equation::calcDerivative() {
    if (degree == 2) {
        return;
    }
    std::vector<double> derCoef = std::vector<double>(degree);
    for (int i = 0; i < degree; i++) {
        derCoef[i] = (degree - i) * (*coef)[i];
    }
    derivative = new Equation(derCoef);
}

Equation::~Equation() {
    delete derivative;
    delete roots;
    delete coef;
}

Equation::Equation(std::vector<double> &coef) {
    this->coef = new std::vector<double>(coef);
    roots = new std::vector<EquationRoot>();
    degree = coef.size() - 1;
    calcDerivative();
}

void Equation::calcRoots(double accuracy, double stepSize) {
    if (degree > 2) { derivative->calcRoots(accuracy, stepSize); }
    if (degree == 2) {
        double discr = getDiscriminant();
        if (discr < 0) {
        } else if (discr == 0) {
            roots->emplace_back(-(*coef)[1] / (2 * (*coef)[0]), 2);
        } else {
            roots->push_back(EquationRoot((-(*coef)[1] - sqrt(discr)) / (2 * (*coef)[0]), 1));
            roots->push_back(EquationRoot((-(*coef)[1] + sqrt(discr)) / (2 * (*coef)[0]), 1));
        }
        return;
    }

    if (derivative->getRoots().size() < 2) {
        double value = getValue(0);
        double root;
        if (std::abs(value) <= accuracy) {
            root = 0;
        } else if (value < 0) {
            root = findRoot(accuracy, stepSize, 0, INFINITY);
        } else {
            root = findRoot(accuracy, stepSize, -INFINITY, 0);
        }
        roots->push_back(EquationRoot(root, 3));
        return;
    }

    double root;
    if (getValue(derivative->getRoots()[1].getValue()) > accuracy) {
        root = findRoot(accuracy, stepSize, -INFINITY, derivative->getRoots()[0].getValue());
        roots->push_back(EquationRoot(root, 3));
    } else if (getValue(derivative->getRoots()[1].getValue()) < accuracy && //replace to abs
               getValue(derivative->getRoots()[1].getValue()) > -accuracy) {
        roots->push_back(EquationRoot(derivative->getRoots()[1].getValue(), 2));
        root = findRoot(accuracy, stepSize, -INFINITY, derivative->getRoots()[0].getValue());
        roots->push_back(EquationRoot(root, 1));
    } else if (getValue(derivative->getRoots()[0].getValue()) < -accuracy) {
        root = findRoot(accuracy, stepSize, derivative->getRoots()[1].getValue(), INFINITY);
        roots->push_back(EquationRoot(root, 3));
    } else if (getValue(derivative->getRoots()[0].getValue()) < accuracy &&
               getValue(derivative->getRoots()[1].getValue()) > -accuracy) {
        roots->push_back(EquationRoot(derivative->getRoots()[0].getValue(), 2));
        root = findRoot(accuracy, stepSize, derivative->getRoots()[1].getValue(), INFINITY);
        roots->push_back(EquationRoot(root, 1));
    } else {
        root = findRoot(accuracy, stepSize, -INFINITY, derivative->getRoots()[0].getValue());
        roots->push_back(EquationRoot(root, 1));
        root = findRoot(accuracy, stepSize, derivative->getRoots()[1].getValue(), derivative->getRoots()[0].getValue());
        roots->push_back(EquationRoot(root, 1));
        root = findRoot(accuracy, stepSize, derivative->getRoots()[1].getValue(), INFINITY);
        roots->push_back(EquationRoot(root, 1));
    }
}

double Equation::getDiscriminant() {
    return (*coef)[1] * (*coef)[1] - 4 * (*coef)[0] * (*coef)[2];
}

std::vector<EquationRoot> Equation::getRoots() {
    return *roots;
}

double Equation::getValue(double x) {
    double value = 0;
    for (int i = 0; i < degree + 1; ++i) {
        double tmp = 1;
        for (int j = 0; j < degree - i; ++j) {
            tmp *= x;
        }
        value += tmp * (*coef)[i];
    }
    return value;
}

double Equation::findRoot(double const accuracy, double stepSize, double leftBorder, double rightBorder) {
    if (leftBorder == -INFINITY) {
        while (getValue(rightBorder - stepSize) >= -accuracy) {
            stepSize *= 2;
        }
        leftBorder = rightBorder - stepSize;
    } else if (rightBorder == INFINITY) {
        while (getValue(leftBorder + stepSize) <= accuracy) {
            stepSize *= 2;
        }
        rightBorder = leftBorder + stepSize;
    }

    while (true) {
        if (std::abs(getValue(leftBorder)) <= accuracy) {
            return leftBorder;
        } else if (std::abs(getValue(rightBorder)) <= accuracy) {
            return rightBorder;
        }
        double median = (leftBorder + rightBorder) / 2;
        if (std::abs(getValue(median)) <= accuracy) {
            return median;
        } else if (getValue(median) > accuracy) {
            rightBorder = median;
        } else {
            leftBorder = median;
        }
    }
}







