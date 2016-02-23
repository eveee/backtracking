#include <iostream>
#include "backtracking.h"

using namespace std;

void problem_test()
{
	cout << "---Test du problème---" << endl << endl;
	Problem pb1 = Problem(1, 1, true);
	Problem pb2 = pb1;
	cout << "pb1 == pb2 ? => " << (pb1 == pb2) << endl << endl;
	cout << "(ID => Dimension => Direction)" << endl;
	cin >> pb2;
	cout << endl << "pb1 : " << pb1 << endl;
	cout << "pb2 : " << pb2 << endl << endl;
	cout << "pb1 != pb2 ? => " << (pb1 != pb2) << endl << endl;
	cout << "id : " << pb1.id() << endl;
	cout << "dimension : " << pb1.dimension() << endl;
	cout << "direction : " << (pb1.direction() ? "maximize" : "minimize") << endl << endl;
	int size = 10;
	vector<double> vecteur_test (1, 1);
	cout << "Pour  " << vecteur_test.at(0) << " : " << pb1.evaluate(vecteur_test) << endl;
	for(int i = 2; i <= size; i++) {
		vecteur_test.push_back(i);
		cout << (i < 10 ? "Pour  " : "Pour ") << vecteur_test.at(i-1) << " : " << (pb1.evaluate(vecteur_test) < 0 ? "" : " ") << pb1.evaluate(vecteur_test) << endl;
	}
	cout << endl << "---Fin du test du problème---" << endl << endl;
}

void solution_test()
{
	cout << "---Test de la solution---" << endl << endl;
	vector<double> vecteur_test2 (1, 1);
	Problem pb = Problem(1, 1, true);
	Solution sol1 = Solution(pb);
	sol1.set_solution(vecteur_test2);
	sol1.fitness();
	Solution sol2(sol1);
	cout << "sol1 == sol2 ? => " << (sol1 == sol2) << endl << endl;
	cout << "(1 réel)" << endl;
	cin >> sol2;
	cout << endl << "sol1 : " << sol1 << endl;
	cout << "sol2 : " << sol2 << endl << endl;
	cout << "sol1 != sol2 ? => " << (sol1 != sol2) << endl << endl;
	cout << sol1.problem() << endl << endl;
	cout << sol1.size() << endl << endl;
	cout << sol1.position(0) << endl;
	sol1.position(0, 2);
	cout << "*set_position(0, 2)*" << endl << sol1.position(0) << endl << endl;
	cout << sol1.get_fitness() << endl << endl;
	sol1.initialize(); cout << sol1 << endl;
	cout << endl << "---Fin du test de la solution---" << endl << endl;
}

void params_test()
{
	cout << "---Test des paramètres---" << endl << endl;
	SetUpParams params = SetUpParams();
	cout << params << endl << endl << "(Runs => Steps => PopSize => SolSize)" << endl;
	cin >> params;
	cout << endl << params << endl << endl;
	cout << params.independent_runs() << endl << "*independent_runs(1)*" << endl;
	params.independent_runs(1);
	cout << params.independent_runs() << endl << endl;
	cout << params.nb_evolution_steps() << endl << "*nb_evolution_steps(2)*" << endl;
	params.nb_evolution_steps(2);
	cout << params.nb_evolution_steps() << endl << endl;
	cout << params.population_size() << endl << "*population_size(3)*" << endl;
	params.population_size(3);
	cout << params.population_size() << endl << endl;
	cout << params.solution_size() << endl << "*solution_size(4)*" << endl;
	params.solution_size(4);
	cout << params.solution_size() << endl << endl;
	cout << endl << "---Fin du test des paramètres---" << endl << endl;
}

void algo_test()
{
	Problem pb = Problem(1, 1, true);
	SetUpParams params;

	cout << "---Test de l'algorithme---" << endl << endl;
	MyAlgorithm algo = MyAlgorithm(pb, params);
	cout << algo << endl << endl;
	cout << algo.problem() << endl << endl;
	cout << algo.setup() << endl << endl;
	cout << algo.upper_cost() << endl;
	cout << algo.lower_cost() << endl << endl;
	cout << *algo.solutions().at(0) << endl;
	cout << algo.solution(0) << endl << endl;
	cout << algo.fitness_values().at(0).fitness << endl;
	cout << algo.fitness(0) << endl << endl;
	cout << algo.best_cost() << endl;
	cout << algo.worst_cost() << endl << endl;
	cout << algo.best_solution() << endl;
	cout << algo.worst_solution() << endl;
	cout << endl << "---Fin du test de l'algorithme---" << endl << endl;
}


int main()
{
	//problem_test();
	//solution_test();
	//params_test();
	algo_test();

	return 0;
}
