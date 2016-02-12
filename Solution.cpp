#include "backtracking.h"

Solution::Solution(const Problem& pbm) :
	_pbm(pbm)
	,_current_fitness(NULL)
	,_solution(vector<double> (pbm.dimension()))
{}

Solution::Solution(const Solution& sol) :
	_pbm(sol.pbm())
	, _current_fitness(sol.get_fitness())
	,_solution(sol.size())
{}

Solution::~Solution()
{}


void Solution::initialize() {
	//_solution = NULL;
	_current_fitness = NULL;
	//_pbm = NULL;
}





double Solution::get_fitness() const{
	return _current_fitness;
}

unsigned int Solution::size() const{
	return _solution.size();
}

vector<double>& Solution::solution() {
	return _solution;
}

void Solution::set_solution(vector <double>& solution) {
	_solution = solution;
}


const Problem& Solution::pbm() const {
	return _pbm;
}

double& Solution::position(const int index) {
	return _solution[index];
}

void Solution::position(const int index, const double value) {
	for (int i = _solution.size(); i > index; i--) {
		_solution[i] = _solution[i - 1];
	}
	_solution[index] = value;
}

