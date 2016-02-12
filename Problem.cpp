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
    }
    return 0;
}

int Problem::dimension() const
{
    return _dimension;
}
