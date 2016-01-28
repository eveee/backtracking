#include "backtracking.h"

using namespace std;

MyAlgorithm::MyAlgorithm(const Problem& pbm,const SetUpParams& setup):
    _setup(setup)
    ,_upper_cost(0), _lower_cost(0)
	, _fitness_values()
	//,_solutions({})
{}

MyAlgorithm::~MyAlgorithm() {}

const SetUpParams& MyAlgorithm::setup() const{
    return _setup;
}

void MyAlgorithm::initialize(){
}

unsigned int MyAlgorithm::upper_cost() const{
    return _upper_cost;
}

unsigned int MyAlgorithm::lower_cost() const{
    return _lower_cost;
}

const vector<Solution*>& MyAlgorithm::solutions() const{
    return _solutions;
}

vector<struct particle>& MyAlgorithm::fitness_values(){
    return _fitness_values;
}

Solution& MyAlgorithm::solution(const unsigned int index) const{
    return *_solutions[index];
}

double MyAlgorithm::fitness(const unsigned int index) const{
    return _fitness_values[index].fitness;
}

void MyAlgorithm::evaluate(const Problem& pbm){
	double min = 0;
	vector<struct particle> fitness(1);
	vector<double> cmin(1);
	vector<double> coord(1);
    for(int i=0; i<_setup.nb_evolution_steps(); i++){
		cout << i << endl;
        coord[0] = i;
        if(pbm.evaluate(coord) < min){
            min = pbm.evaluate(coord);
            cmin = coord;
        }
    }
	fitness[0].fitness = min;
	cout << min << endl;
    //_fitness_values[0].fitness = min;

}
