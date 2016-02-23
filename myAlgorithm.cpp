#include "backtracking.h"

MyAlgorithm::MyAlgorithm(const Problem& pbm, const SetUpParams& setup):
_pbm(pbm), _setup(setup)
{
	initialize();
	evaluate();
	_upper_cost = best_cost();
	_lower_cost = worst_cost();
}

MyAlgorithm::~MyAlgorithm()
{

}


ostream& operator << (ostream& os, const MyAlgorithm& myAlgo)
{
	os << "Population :" << endl << endl;
	for(unsigned int i = 0; i < myAlgo._setup.population_size(); i++)
		os << "{" << myAlgo.solution(i) << "}" << endl;
	os << endl << "Problème :" << endl << endl << myAlgo.problem() << endl << endl;
	os << "Paramètres :" << endl << endl << myAlgo.setup();
	return os;
}

istream& operator >> (istream& is, MyAlgorithm& myAlgo)
{
	return is;
}


MyAlgorithm& MyAlgorithm::operator = (const MyAlgorithm& myAlgo)
{
	if(this != &myAlgo) {
		_solutions = myAlgo.solutions();
		_upper_cost = myAlgo.problem().UpperLimit;
		_lower_cost = myAlgo.problem().LowerLimit;
		evaluate();
	}
	return *this;
}


const Problem& MyAlgorithm::problem() const
{
	return _pbm;
}


const SetUpParams& MyAlgorithm::setup() const
{
    return _setup;
}

double MyAlgorithm::upper_cost() const
{
    return _upper_cost;
}

double MyAlgorithm::lower_cost() const
{
    return _lower_cost;
}


const vector<Solution*>& MyAlgorithm::solutions() const
{
    return _solutions;
}

Solution& MyAlgorithm::solution(const unsigned int index) const
{
    return *_solutions.at(index);
}

vector<struct particle>& MyAlgorithm::fitness_values()
{
    return _fitness_values;
}

double MyAlgorithm::fitness(const unsigned int index) const
{
    return _fitness_values.at(index).fitness;
}


double MyAlgorithm::best_cost() const
{
	double best = fitness(0);
	for(unsigned int i = 1; i < setup().population_size(); i++)
		best = (fitness(i) > best ? fitness(i) : best);
	return best;
}

double MyAlgorithm::worst_cost() const
{
	double worst = fitness(0);
		for(unsigned int i = 0; i < setup().population_size(); i++)
			worst = (fitness(i) < worst ? fitness(i) : worst);
		return worst;
}

Solution& MyAlgorithm::best_solution() const
{
	double fit = best_cost();
	for(unsigned int i = 0; i < setup().population_size(); i++)
			if(fitness(i) == fit)
				return solution(i);
	return best_solution();
}

Solution& MyAlgorithm::worst_solution() const
{
	double fit = worst_cost();
	for(unsigned int i = 0; i < setup().population_size(); i++)
			if(fitness(i) == fit)
				return solution(i);
	return worst_solution();
}


void MyAlgorithm::initialize()
{
	srand(time(NULL));
	for(unsigned int i = 0; i < _setup.population_size(); i++) {
		Solution *sol = new Solution(_pbm);
		sol->initialize(rand() + 1);
		_solutions.push_back(sol);
	}
}

void MyAlgorithm::evaluate()
{
	_fitness_values.clear();
	for(unsigned int i = 0; i < setup().population_size(); i++) {
		struct particle part = {i, solution(i).get_fitness()};
		_fitness_values.push_back(part);
	}
}


void MyAlgorithm::evolution(int iter)
{

}
