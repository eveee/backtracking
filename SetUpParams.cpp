#include "backtracking.h"

SetUpParams::SetUpParams(unsigned int independent_runs = 30, unsigned int nb_evolution_steps = 30, unsigned int population_size = 30, unsigned int solution_size = 30) :
_independent_runs(independent_runs), _nb_evolution_steps(nb_evolution_steps), _population_size(population_size), _solution_size(solution_size) {}

ostream& operator << (ostream& os, const SetUpParams& setup) {
	os << "Runs : " << setup._independent_runs << ", Steps : " << setup._nb_evolution_steps <<
		", Population : " << setup._population_size << ", Solution : " << setup._solution_size;
	return os;
}

istream& operator >> (istream& is, SetUpParams& setup) {
	is >> setup._independent_runs >> setup._nb_evolution_steps >>
		setup._population_size >> setup._solution_size;
	return is;
}

const unsigned int SetUpParams::independent_runs() const {
	return _independent_runs;
}

const unsigned int SetUpParams::nb_evolution_steps() const {
	return _nb_evolution_steps;
}

const unsigned int SetUpParams::population_size() const {
	return _population_size;
}

const unsigned int SetUpParams::solution_size() const {
	return _solution_size;
}

void SetUpParams::independent_runs(const unsigned int val) {
	if(val != 0) _independent_runs = val;
	else _independent_runs = 30;
}

void SetUpParams::nb_evolution_steps(const unsigned int val) {
	if (val != 0) _nb_evolution_steps = val;
	else _independent_runs = 30;
}

void SetUpParams::population_size(const unsigned int val){
	if (val != 0) _population_size = val;
	else _population_size = 30;
}

void SetUpParams::solution_size(const unsigned int val){
	if (val != 0) _solution_size = val;
	else _solution_size = 30;
}

SetUpParams::~SetUpParams() {
	delete &_independent_runs;
	delete &_nb_evolution_steps;
	delete &_population_size;
	delete &_solution_size;
}
