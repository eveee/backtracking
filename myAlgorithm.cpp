#include "backtracking.h"

MyAlgorithm::MyAlgorithm(const Problem& pbm, const SetUpParams& setup):
_pbm(pbm), _setup(setup)
{
	initialize();
	evaluate();
	_upper_cost = best_cost();
	_lower_cost = worst_cost();
	mixrate = 1;
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


void MyAlgorithm::evolution(unsigned int iter)
{
	if(iter == _setup.nb_evolution_steps())
		return;

	srand(time(NULL) + iter);

	//Initilization

	Solution *u = new Solution(_pbm);	//Vecteur uniforme de LowerLimit à UpperLimit
	for(unsigned int i = 0; i < _pbm.dimension(); i++)
		u->position(i, _pbm.LowerLimit + i * ((_pbm.UpperLimit - _pbm.LowerLimit) / (_pbm.dimension() - 1)));
	_upper_cost = best_cost();
	_lower_cost = worst_cost();

	//Selection-I

	vector<Solution*> oldP(_setup.population_size());
	for(unsigned int i = 0; i < _setup.population_size(); i++) {
		oldP.at(i) = new Solution(_pbm);
		for(unsigned int j = 0; j < _pbm.dimension(); j++)
			if(rand() < rand())
				oldP.at(i)->position(j, _solutions.at(i)->position(j));
			else
				oldP.at(i)->position(j, u->position(rand() % _pbm.dimension()));
	}

	for (unsigned int i = _setup.population_size() - 1; i > 0; --i)
	    swap(oldP.at(i), oldP.at(rand() % (_setup.population_size())));

	//Mutation

	vector<Solution*> Mutant(_setup.population_size(), new Solution(_pbm));
	for(unsigned int i = 0; i < _setup.population_size(); i++)
		Mutant.at(i) = new Solution(_pbm);
	double F = (double)(rand() % 3000) / 10000;
	for(unsigned int i = 0; i < _setup.population_size(); i++)
		for(unsigned int j = 0; j < _pbm.dimension(); j++)
			Mutant.at(i)->position(j, (_solutions.at(i)->position(j) + (F * (oldP.at(i)->position(j) - _solutions.at(i)->position(j)))));

	//Crossover

	vector<vector<bool> > map(_setup.population_size(), vector<bool> (_pbm.dimension(), false));
	if(rand() < rand()) {
		vector<unsigned int > v(_pbm.dimension());
		for(unsigned int i = 0; i < _pbm.dimension(); )
					v.at(i = ++i);
		for(unsigned int i = 0; i < _setup.population_size(); i++) {
			for(unsigned int i = 0; i < rand() % 100; i++)
				swap(v.at(rand() % _pbm.dimension()), v.at(rand() % _pbm.dimension()));
			for(unsigned int i = 0; i < ceil(mixrate * (double)(rand() % 1001) / 1000 * _pbm.dimension()); i++)
				map.at(i).at(v.at(i)) = true;
		}
	} else
		for(unsigned int i = 0; i < _setup.population_size(); i++)
			map.at(i).at(rand() % _pbm.dimension()) = true;

	vector<Solution*> Trial(_setup.population_size(), new Solution(_pbm));
	for(unsigned int i = 0; i < _setup.population_size(); i++)
		for(unsigned int j = 0; j < _pbm.dimension(); j++)
			if(map.at(i).at(j)) {
				Trial.at(i)->position(j, _solutions.at(i)->position(j));
				Trial.at(i)->fitness();
			} else {
				Trial.at(i)->position(j, Mutant.at(i)->position(j));
				if(Trial.at(i)->position(j) < _pbm.LowerLimit || Trial.at(i)->position(j) > _pbm.UpperLimit)
					Trial.at(i)->position(j, _pbm.UpperLimit + rand() % _pbm.dimension() * (_pbm.UpperLimit - _pbm.LowerLimit));
				Trial.at(i)->fitness();
			}

	//Selection-II

	if(_pbm.direction()) {
		for(unsigned int i = 0; i < _setup.population_size(); i++) {
			if(Trial.at(i)->get_fitness() > _solutions.at(i)->get_fitness())
				for(unsigned int j = 0; j < _pbm.dimension(); j++)
					_solutions.at(i)->position(j, Trial.at(i)->position(j));
			_solutions.at(i)->fitness();
		}

		if(best_cost() > upper_cost())
			_upper_cost = best_cost();
	} else {
		for(unsigned int i = 0; i < _setup.population_size(); i++) {
			if(Trial.at(i)->get_fitness() < _solutions.at(i)->get_fitness())
				for(unsigned int j = 0; j < _pbm.dimension(); j++)
					_solutions.at(i)->position(j, Trial.at(i)->position(j));
			_solutions.at(i)->fitness();
		}

		if(worst_cost() < lower_cost())
			_lower_cost = worst_cost();
	}

	evolution(++iter);

}
