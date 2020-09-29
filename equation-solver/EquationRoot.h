//
// Created by adman on 26.09.2020.
//

#ifndef EQUATION_RESOLVER_EQUATIONROOT_H
#define EQUATION_RESOLVER_EQUATIONROOT_H


class EquationRoot {
private:
    double value;
    int multiplicity;
public:
    EquationRoot(double value, int multiplicity);
    double getValue() const;
    int getMultiplicity() const;

};

inline bool operator< (const EquationRoot& lhs, const EquationRoot& rhs){ return lhs.getValue() < rhs.getValue();}
inline bool operator> (const EquationRoot& lhs, const EquationRoot& rhs){ return rhs < lhs; }
inline bool operator<=(const EquationRoot& lhs, const EquationRoot& rhs){ return !(lhs > rhs); }
inline bool operator>=(const EquationRoot& lhs, const EquationRoot& rhs){ return !(lhs < rhs); }

#endif //EQUATION_RESOLVER_EQUATIONROOT_H
