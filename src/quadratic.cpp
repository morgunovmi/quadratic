#include <math.h>
#include <assert.h>
#include <stdio.h> 

#include "quadratic.h"

int getCoefsFromInput(double *a, double *b, double *c) {
    const int ret = scanf("%lg %lg %lg", a, b, c); 
    if (ret == EOF) {
        printf("scanf function returned EOF\n");
        return 0;
    } 
    if (ret != 3) {
        printf("Not enough valid coefficients\n");
        return 0;
    } 
    
    return (isfinite(*a) && isfinite(*b) && isfinite(*c)) ? 1 : 0;
}

void printResult(const NRoots nRoots, const double x1, const double x2) {
    switch (nRoots) {
        case ZERO:
            printf("Given equation has no real solutions\n");
            break;
        case ONE:
            printf("The only equation solution is %lg\n", x1);
            break;
        case TWO:
            printf("Equation solutions are %lg and %lg\n", x1, x2);
            break;
        case INF_ROOTS:
            printf("Given equation has infinite solutions\n");
            break;
        default:
            printf("Undefined number of roots returned\n");
    }
}

void printEquation(const double a, const double b, const double c) {
    printf("Your equation is %lgx^2 ", a);
    if (b < 0) {
        printf("- %lgx ", -b);
    } else { 
        printf("+ %lgx ", b);
    }
    if (c < 0) {
        printf("- %lg = 0\n", -c);
    } else { 
        printf("+ %lg = 0\n", c);
    }
}

bool isEqualDouble(const double lhs, const double rhs) {
    return abs(lhs - rhs) < EPSILON;
}

NRoots solveQuadratic(const double a, const double b, const double c,
                      double *x1, double *x2) {

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);
    
    if (isEqualDouble(a, 0)) {
        if (isEqualDouble(b, 0)) {
            return (isEqualDouble(c, 0)) ? NRoots::INF_ROOTS : NRoots::ZERO;
        } else { 
            *x1 = solveLinear(b, c);
            return NRoots::ONE;
        }
    } else {
        if (isEqualDouble(c, 0)) {
            const double temp = solveLinear(a, b);
            if (isEqualDouble(temp, 0)) {
                *x1 = temp;
                return NRoots::ONE;
            } else {
                if (temp < 0) {
                    *x1 = temp;
                    *x2 = 0;
                } else {
                    *x1 = 0;
                    *x2 = temp;
                }
                return NRoots::TWO;
            }
        }

        const double discr = b * b - 4 * a * c;
        assert(isfinite(discr));
        if (discr < 0) {
            return NRoots::ZERO;
        } else if (isEqualDouble(discr, 0)) {
            *x1 = -b / (2 * a);
            return NRoots::ONE;
        }

        const double sqrtD = sqrt(discr);
        *x1 = (-b - sqrtD) / (2 * a);
        *x2 = (-b + sqrtD) / (2 * a);
        return NRoots::TWO;
    }
}

double solveLinear(const double a, const double b) {
    return -b / a;
}
