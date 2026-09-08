#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>
using namespace std;

struct GDResult {
    int degree;
    double finalX;
    double finalFx;
    int iterations;
    bool converged;
};

double evaluatePolynomial(const vector<double>& coeffs, double x);
double evaluateDerivative(const vector<double>& coeffs, double x);
GDResult gradientDescentFunc(int degree, const vector<double>& coeffs, double initialX, double learningRate, double tolerance, int maxIterations);

#endif