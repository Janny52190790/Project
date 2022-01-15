#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define EPSILON 1e-14

// define Absolute value function
static inline double Abs(double x) {
    return x < 0 ? -x : x;
}

// define Exponential function
double Exp(double x) {
    double trm = 1, sum = trm;
    for (int k = 1; trm > EPSILON; k++) {
        trm *= Abs(x) / k;
        sum += trm;
    }
    if (x > 0) {
        return sum;
    } else {
        return 1 / sum;
    }
}

// define sin funcion
double Sin(double x) {
    double sgn = 1, val = x, trm = x;
    for (int k = 3; Abs(trm) > EPSILON; k += 2) {
        trm = trm * (x * x) / ((k - 1) * k);
        sgn = -sgn;
        val += sgn * trm;
    }
    return val;
}
// define cos function
double Cos(double x) {
    double sgn = 1, val = 1, trm = 1;
    for (int k = 2; Abs(trm) > EPSILON; k += 2) {
        trm = trm * (x * x) / ((k - 1) * k);
        sgn = -sgn;
        val += sgn * trm;
    }
    return val;
}

// define sqrt function
double Sqrt(double x) {
    double y = 1;
    for (double z = 0; Abs(y - z) > EPSILON; y = 0.5 * (z + x / z)) {
        z = y;
    }
    return y;
}

// define log function
double Log(double x) {
    double y = 1;
    for (double p = Exp(y); Abs(p - x) > EPSILON; p = Exp(y)) {
        y = y + x / p - 1;
    }
    return y;
}

// define integrate function using Simpson’s Rules
double integrate(double (*f)(double), double a, double b, uint32_t n) {
    double h = (b - a) / n;
    double sum = (*f)(a) + (*f)(b);
    for (uint32_t i = 1; n > i; i++) {
        if (i % 2 == 0) {
            sum += 2 * (*f)(a + i * h);
        } else {
            sum += 4 * (*f)(a + i * h);
        }
    }
    sum *= h * 1 / 3;
    return sum;
}
