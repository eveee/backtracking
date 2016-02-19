#include "backtracking.h"
#include "test_optimization.h"
#include <cmath>

Problem::Problem(int _id):fct_id(_id)
{
    _dimension = 1;
    LowerLimit =0;
    UpperLimit = 1000;
    //ctor
}

Problem::~Problem()
{
    //dtor
}

double Problem::evaluate(std::vector<double> x) const
{
    switch (fct_id)
    {
    case 0: //fonction test
        return pow(-1,x[0])*(double)((int)x[0]%50);
    case 1: //rosenbrock's valley
        return *p04_f(_dimension, 1, &x[0]);
    case 2: //rastrigin's function
        return *p05_f(_dimension, 1, &x[0]);
    case 3: //schwefel's function
        return *p06_f(_dimension, 1, &x[0]);
    case 4: //ackley's function
       return  *p09_f(_dimension, 1, &x[0]);
    case 5: //schaffer
        double fit;
        for (int i = 0; i <= _dimension-1; i++)
            fit = 0.5 + (sin(x[i] * x[i] - x[i+1] * x[i+1]) * sin(x[i] * x[i] - x[i+1] * x[i+1]) - 0.5) / ((1 + 0.001*(x[i] * x[i] + x[i+1] * x[i+1])) * (1 + 0.001*(x[i] * x[i] + x[i+1] * x[i+1])));
        return fit;
    case 6: //weierstrass
        double a = 0.5, b = 3;
        int kmax = 30;
        double fit2 = 0, s = 0;
        for (int i = 0; i<_dimension; i++)
            for (int k = 0; k <= kmax; k++)
                fit2 += pow(a, k)*cos(2 * M_PI*pow(b, k)*(x[i] + 0.5));
        for (int k = 0; k <= kmax; k++)
            s += pow(a, k)*cos(2 * M_PI*pow(b, k)*0.5);
        s = s*_dimension;
        return fit2 - s;
    }
    return 0;
}

int Problem::dimension() const
{
    return _dimension;
}
