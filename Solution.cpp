#include "backtracking.h"

Solution::Solution(const Problem& pbm):_pbm(pbm)
{
	vector<double> sol (pbm.dimension());
	_solution = sol;
}

Solution::Solution(const Solution& sol):_pbm(sol.problem()), _solution(sol.size()), _current_fitness(sol.get_fitness())
{

}

Solution::~Solution()
{

}


ostream& operator << (ostream& os, const Solution& sol)
{
	os << "{";
	for(unsigned int i = 0; i < sol.size(); i++)
		(i != sol.size()-1 ? os << sol.position(i) << ", " : os << sol.position(i) << "}");
	os << " => " << sol.get_fitness();
	return os;
}

istream& operator >> (istream& is, Solution& sol)
{
	for(unsigned int i = 0; i < sol.size(); i++)
		is >> sol._solution.at(i);
	return is;
}


Solution& Solution::operator = (const Solution& sol)
{
	if (this != &sol) {
		for(unsigned int i = 0; i < sol.size(); i++)
			position(i, sol.position(i));
		_current_fitness = sol.get_fitness();
	}
	return *this;
}

bool Solution::operator == (const Solution& sol) const
{
	for(unsigned int i = 0; i < sol.size(); i++)
		if(sol.position(i) != position(i))
			return false;
	return (_pbm == sol.problem() && _current_fitness == sol.get_fitness());
}

bool Solution::operator != (const Solution& sol) const
{
	for(unsigned int i = 0; i < sol.size(); i++)
			if(sol.position(i) != position(i))
				return true;
		return (_pbm != sol.problem() || _current_fitness != sol.get_fitness());
}


const Problem& Solution::problem() const
{
	return _pbm;
}

vector<double>& Solution::solution()
{
	return _solution;
}

unsigned int Solution::size() const
{
	return _solution.size();
}

double& Solution::position(const unsigned int index) const
{
	double *pos = new double(_solution.at(index));
	return *pos;
}

double Solution::get_fitness() const
{
	return _current_fitness;
}


void Solution::set_solution(vector <double>& sol)
{
	if(sol.size() == _pbm.dimension())
		_solution = sol;
	else
		throw string("Erreur : dimension de la solution invalide");
}

void Solution::position(const unsigned int index, const double value)
{
	_solution.at(index) = value;
}

double Solution::fitness()
{
	_current_fitness = _pbm.evaluate(_solution);
	return _current_fitness;
}


void Solution::initialize(int init)
{
	srand(init == 0 ? time(NULL) : init); double random;
	for(unsigned int i = 0; i < size(); i++) {
		for(int j = 0; j < rand()%100; j++)
			random = rand();
		random = (random/(double)RAND_MAX) * (_pbm.UpperLimit-_pbm.LowerLimit) + _pbm.LowerLimit;
		position(i, random);
	}
	fitness();
}
