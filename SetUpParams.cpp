#include "backtracking.h"

SetUpParams::SetUpParams(unsigned int runs, unsigned int steps, unsigned int pop, unsigned int sol):
_independent_runs(runs), _nb_evolution_steps(steps), _population_size(pop), _solution_size(sol)
{

}

SetUpParams::~SetUpParams()
{

}


ostream& operator << (ostream& os, const SetUpParams& setup)
{
	os << "Runs : " << setup._independent_runs << ", Steps : " << setup._nb_evolution_steps <<
		", Population : " << setup._population_size << ", Solution : " << setup._solution_size;
	return os;
}

istream& operator >> (istream& is, SetUpParams& setup)
{
	unsigned int run, step, pop, sol;
	is >> run >> step >> pop >> sol;
	setup.independent_runs(run);
	setup.nb_evolution_steps(step);
	setup.population_size(pop);
	setup.solution_size(sol);
	return is;
}


const unsigned int SetUpParams::independent_runs() const
{
	return _independent_runs;
}

const unsigned int SetUpParams::nb_evolution_steps() const
{
	return _nb_evolution_steps;
}

const unsigned int SetUpParams::population_size() const
{
	return _population_size;
}

const unsigned int SetUpParams::solution_size() const
{
	return _solution_size;
}


void SetUpParams::independent_runs(const unsigned int val)
{
	_independent_runs = (val > 0 ? val : 30);
}

void SetUpParams::nb_evolution_steps(const unsigned int val)
{
	_nb_evolution_steps = (val > 0 ? val : 2000000);
}

void SetUpParams::population_size(const unsigned int val)
{
	_population_size = (val > 0 ? val : 40);
}

void SetUpParams::solution_size(const unsigned int val)
{
	_solution_size = (val > 0 ? val : 20);
}
