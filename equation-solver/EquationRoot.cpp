//
// Created by adman on 26.09.2020.
//

#include "EquationRoot.h"

EquationRoot::EquationRoot(double value, int multiplicity) {
    this->value = value;
    this->multiplicity = multiplicity;
}

double EquationRoot::getValue() const {
    return value;
}

int EquationRoot::getMultiplicity() const{
    return multiplicity;
}
