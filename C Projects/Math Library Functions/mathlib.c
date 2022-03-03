#include "mathlib.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-10 // 1x10^-10

static inline double Abs(double x) { // provided by Eugene
    return x < 0 ? -x : x;
}

double arcSin(double x) {
    double num = 1.0; // initalizing all variables
    double denom = 1.0;
    double dgn = 1.0;
    double aSinx = 0.0;
    double tside = 1.0;
    double bside = 1.0;
    double bfact = 1.0;
    for (int i = 0; Abs(dgn) >= EPSILON; i += 1) {
        if (i == 0) { // this is specifically for 0! because 0! = 1
            num = x;
            denom = 1.0;
            tside = 1.0;
            bside = 1.0;
        } else {
            num = pow(x, ((2 * i) + 1)); // x^(2k+1)
            denom = ((2 * i) + 1); // 2k + 1
            tside = (2 * i) * ((2 * i) - 1) * tside; // (2k)!
            bfact = i * bfact; // k!
            bside = (pow(2, (2 * i)) * pow(bfact, 2)); // 2^(2k) * (k!)^2
        }
        dgn = ((num * tside) / (denom * bside));
        aSinx = aSinx + dgn;
    }
    return aSinx;
}

double arcCos(double x) { // inverse method
    return ((M_PI / 2) - arcSin(x));
}

double arcTan(double x) { // inverse method using arcCos
    return arcCos(1 / (sqrt((pow(x, 2)) + 1)));
}

double Exp(double x) { // sponsored by the teacher
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}

double Log(double x) {
    double y = 1.0;
    double p = Exp(y);
    while (Abs(x - p) > EPSILON) { // formula provided by teacher
        y = y + ((x - p) / p);
        p = Exp(y);
    }
    return y;
}
