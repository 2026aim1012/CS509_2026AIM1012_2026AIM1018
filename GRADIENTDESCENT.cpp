#include "GRADIENTDESCENT.h"
#include <cmath>
#include <vector>

using namespace std;

double evaluatePolynomial(const vector<double>& coeffs, double x) {
    double result = 0.0;
    double currentPowerOfX = 1.0; 
    
    for (int i = 0; i < coeffs.size(); ++i) {
        result += coeffs[i] * currentPowerOfX;
        currentPowerOfX *= x; 
    }
    return result;
}

double evaluateDerivative(const vector<double>& coeffs, double x) {
    double result = 0.0;
    double currentPowerOfX = 1.0; 
    
    for (int i = 1; i < coeffs.size(); ++i) {
        result += i * coeffs[i] * currentPowerOfX;
        currentPowerOfX *= x;
    }
    return result;
}

GDResult gradientDescentFunc(int degree, const vector<double>& coeffs, double initialX, double learningRate, double tolerance, int maxIterations) {
    double x = initialX;
    int iter = 0;
    bool converged = false;

    while (iter < maxIterations) {
        double derivative = evaluateDerivative(coeffs, x);
        
        if (abs(derivative) <= tolerance) {
            converged = true;
            break;
        }
        
        x = x - (learningRate * derivative);
        iter++;
    }

    GDResult finalResult;
    finalResult.degree = degree;
    finalResult.finalX = x;
    finalResult.finalFx = evaluatePolynomial(coeffs, x);
    finalResult.iterations = iter;
    finalResult.converged = converged;
    
    return finalResult;
}