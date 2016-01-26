#include "Problem.h"
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

double Problem::evaluate(std::vector<double> x)
{
    switch (fct_id)
    {
    case 0:
        return pow(-1,x[0])*(double)((int)x[0]%50);
    }
    return 0;
}

int Problem::dimension() const
{
    return _dimension;
}
