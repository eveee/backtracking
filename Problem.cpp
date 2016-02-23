#include "backtracking.h"

Problem::Problem()
{

}

Problem::Problem(unsigned int _id, unsigned int _dim, bool _dir):fct_id(_id), _dimension(_dim), _direction(_dir)
{
	switch (fct_id) {
		case 0:
			test_limits();
			break;
		case 1:
			rosenbrock_limits();
			break;
		case 2:
			rastrigin_limits();
			break;
		case 3:
			ackley_limits();
			break;
		case 4:
			schwefel_limits();
			break;
		case 5:
			schaffer_limits();
			break;
		case 6:
			weierstrass_limits();
			break;
		default:
			throw string("Erreur : ID inconnu");
	}
}

Problem::~Problem()
{

}


ostream& operator << (ostream& os, const Problem& pbm)
{
	switch(pbm.id()) {
		case 1:
			os << "Rosenbrock";
			break;
		case 2:
			os << "Rastrigin";
			break;
		case 3:
			os << "Ackley";
			break;
		case 4:
			os << "Schwefel";
			break;
		case 5:
			os << "Schaffer";
			break;
		case 6:
			os << "Weiestrass";
			break;
		default:
			os << "Fonction non reconnue";
			break;
	}
	os << " de dimension " << pbm.dimension() << " dont on cherche le ";
	if(pbm.direction())
		os << "maximum.";
	else
		os << "minimum.";
	return os;
}

istream& operator >> (istream& is, Problem& pbm)
{
	int id, dim;
	is >> id >> dim >> pbm._direction;
	pbm.fct_id = (id < 0 ? -id : id);
	pbm._dimension = (dim < 0 ? -dim : dim);
	return is;
}


Problem& Problem::operator = (const Problem& pbm)
{
	if (this != &pbm) {
		fct_id = pbm.id();
		_dimension = pbm.dimension();
		_direction = pbm.direction();
	}
	return *this;
}

bool Problem::operator == (const Problem& pbm) const
{
	return !(fct_id == pbm.id() && _dimension == pbm.dimension()
			&& _direction == pbm.direction());
}

bool Problem::operator != (const Problem& pbm) const
{
	return !(fct_id == pbm.id() && _dimension == pbm.dimension()
			&& _direction == pbm.direction());
}


unsigned int Problem::id() const
{
	return fct_id;
}

unsigned int Problem::dimension() const
{
	return _dimension;
}

bool Problem::direction() const
{
	return _direction;
}

double Problem::evaluate(vector<double> &x) const
{
	for (unsigned int i = 0; i < _dimension; i++)
			if (x.at(i) > UpperLimit || x.at(i) < LowerLimit)
				throw string("Erreur : coordonnées interdites");
	switch (fct_id) {
	case 0: //Fonction de test (f(x) = 1^x * x%50)
		return test_function(x);
	case 1:
		return rosenbrock_function(x);
	case 2:
		return rastrigin_function(x);
	case 3:
		return ackley_function(x);
	case 4:
		return schwefel_function(x);
	case 5:
		return schaffer_function(x);
	case 6:
		return weierstrass_function(x);
	default:
		throw string("Erreur : ID inconnu");
	}
}


void Problem::rosenbrock_limits()
{
	LowerLimit = -2.048;
	UpperLimit = 2.048;
	return;
}

double Problem::rosenbrock_function(vector<double> &arguments) const
{
	double f = 0.0, tmp;
	for (unsigned int i = 0; i < _dimension; i++) {
		tmp = arguments.at(i);
		f += pow(1.0 - tmp, 2) + 100 * pow((tmp - pow(tmp, 2)), 2);
	}
	return f;
}

void Problem::rastrigin_limits()
{
	LowerLimit = -5.12;
	UpperLimit = 5.12;
	return;
}

double Problem::rastrigin_function(vector<double> &arguments) const
{
	double f = (double) (10 * _dimension), tmp;
	for (unsigned int i = 0; i < _dimension; i++) {
		tmp = arguments.at(i);
		f += pow(tmp, 2) - 10.0 * cos(2.0 * PI * tmp);
	} return f;
}

void Problem::ackley_limits()
{
	LowerLimit = -32.768;
	UpperLimit = 32.768;
	return;
}

double Problem::ackley_function(vector<double> &arguments) const
{
	double s1 = 0.0, s2 = 0.0, tmp;
	for (unsigned int i = 0; i < _dimension; i++) {
		tmp = arguments.at(i);
		s1 = s1 + pow(tmp, 2);
		s2 = s2 + cos(0.2 * PI * tmp);
	}
	return (-20.0 * exp(-0.2 * sqrt(s1 / (double) (_dimension))) - exp(s2 / (double) (_dimension)) + 20.0 + exp(1.0));
}

void Problem::schwefel_limits()
{
	LowerLimit = -500.0;
	UpperLimit = 500.0;
	return;
}

double Problem::schwefel_function(vector<double> &arguments) const
{
	double f = 0.0, tmp;
	for (unsigned int i = 0; i < _dimension; i++) {
		tmp = arguments.at(i);
		f -= tmp * sin(sqrt((tmp < 0 ? -tmp : tmp)));
	}
	return f;
}

void Problem::schaffer_limits()
{
	LowerLimit = -100.0;
	UpperLimit = 100.0;
	return;
}

double Problem::schaffer_function(vector<double> &arguments) const
{
	double f = 0.0, tmp_x, tmp_y;
	if(_dimension == 1) {
		tmp_x = pow(arguments.at(0), 2);
		f = 0.5 + (((pow(sin(tmp_x), 2)) - 0.5) / (pow(1+0.001*(tmp_x),2)));
	}
	for (unsigned int i = 0; i < _dimension - 1; i++) {
		tmp_x = pow(arguments.at(i), 2); tmp_y = pow(arguments.at(i+1), 2);
		f += 0.5 + (((pow(sin(tmp_x - tmp_y), 2)) - 0.5) / (pow(1+0.001*(tmp_x + tmp_y),2)));
	} return f;
}

void Problem::weierstrass_limits()
{
	LowerLimit = -1000.0;
	UpperLimit = 1000.0;
	return;
}

double Problem::weierstrass_function(vector<double> &arguments) const
{
	double a = 0.5, b = 3, f = 0, s = 0;
	for (unsigned int i = 0; i < _dimension; i++)
		for (int j = 0; j <= 100; j++)
			f += pow(a, j) * cos(2 * PI * pow(b, j) * (arguments.at(i) + 0.5));
	for (int j = 0; j <= 100; j++)
		s += pow(a, j) * cos(2 * PI * pow(b, j) * 0.5);
	s *= _dimension;
	return (f - s);
}

//Partie test:

void Problem::test_limits()
{
	LowerLimit = -100.0;
	UpperLimit = 100.0;
	return;
}

double Problem::test_function(vector<double> &arguments) const
{
	double f = 0.0;
	for (unsigned int i = 0; i < arguments.size(); i++)
		f = pow(-1, arguments.at(i)) * (double) ((int) arguments.at(i) % 10);
	return f;
}
