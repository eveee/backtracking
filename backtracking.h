#ifndef INC_METAHEURISTIC
#define INC_METAHEURISTIC

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>

using namespace std;

struct particle 															//Index d'une fitness dans la population, avec sa valeur
{
	unsigned int index;
	double fitness;
};

//===========================================================================================================================================

class Problem {																//Contient la déclaration du problème

public:

	double LowerLimit, UpperLimit; 											//Les limites de l'ensemble d'arrivée suivant chaque coordonnée

	Problem();																//Constructeur par défaut
	Problem(unsigned int, unsigned int, bool); 								//Constructeur valué
	~Problem(); 															//Destructeur

	friend ostream& operator << (ostream&, const Problem&);					//Opérateur de flux sortant
	friend istream& operator >> (istream&, Problem&);						//Opérateur de flux entrant

	Problem& operator = (const Problem&); 									//Opérateur d'affectation
	bool operator == (const Problem&) const; 								//Opérateur de comparaison
	bool operator != (const Problem&) const; 								//Opérateur de comparaison inverse

	unsigned int id() const; 												//Renvoie l'id de la fonction du problème
	unsigned int dimension() const; 										//Renvoie la dimension du problème
	bool direction() const; 												//Renvoie le direction du problème

	double evaluate(vector<double>&) const; 								//Evalue le vecteur d'entrée

	void rosenbrock_limits();												//Modifie les limites du problème pour la fonction de Rosenbrock
	double rosenbrock_function(vector<double>&) const;						//Evalue le vecteur d'entrée par la fonction de Rosenbrock
	void rastrigin_limits();												//Modifie les limites du problème pour la fonction de Rastrigin
	double rastrigin_function(vector<double>&) const;						//Evalue le vecteur d'entrée par la fonction de Rastrigin
	void ackley_limits();													//Modifie les limites du problème pour la fonction de Ackley
	double ackley_function(vector<double>&) const;							//Evalue le vecteur d'entrée par la fonction de Ackley
	void schwefel_limits();													//Modifie les limites du problème pour la fonction de Schwefel
	double schwefel_function(vector<double>&) const;						//Evalue le vecteur d'entrée par la fonction de Schwefel
	void schaffer_limits();													//Modifie les limites du problème pour la fonction de Schaffer
	double schaffer_function(vector<double>&) const;						//Evalue le vecteur d'entrée par la fonction de Schaffer
	void weierstrass_limits();												//Modifie les limites du problème pour la fonction de Weierstrass
	double weierstrass_function(vector<double>&) const;						//Evalue le vecteur d'entrée par la fonction de Weierstrass

	void test_limits();														//---!!!---Limites pour la fonction de test---!!!---
	double test_function(vector<double>&) const; 							//---!!!-----------Fonction de test-----------!!!---

private:

	unsigned int fct_id; 													//Id de la fonction choisie
	unsigned int _dimension; 												//Dimension du problème
	bool _direction; 														//true si on cheche le maximum, false sinon

};

//===========================================================================================================================================

class Solution {															//Contient la déclaration d'une solution

public:

	Solution(const Problem&);												//Constructeur valué
	Solution(const Solution&);												//Constructeur par recopie
	~Solution();															//Destructeur

	friend ostream& operator << (ostream&, const Solution&);				//Opérateur de flux sortant
	friend istream& operator >> (istream&, Solution&);						//Opérateur de flux entrant

	Solution& operator = (const Solution&);									//Opérateur d'affectation
	bool operator == (const Solution&) const;								//Opérateur de comparaison
	bool operator != (const Solution&) const;								//Opérateur de comparaison inverse

	const Problem& problem() const;											//Renvoie le problème de la solution
	vector<double>& solution();												//Renvoie le vecteur solution
	unsigned int size() const;												//Renvoie la dimension de la solution
	double& position(const unsigned int) const; 							//Renvoie une coordonnée de la solution
	double get_fitness() const;												//Renvoie la fitness de la solution

	void set_solution(vector<double>&);										//Modifie le vecteur solution
	void position(const unsigned int, const double);						//Modifie une coordonnée du vecteur solution
	double fitness();														//Calcule la fitness du vecteur solution

	void initialize(int = 0);												//Génère un vecteur solution aléatoire

private:

	const Problem& _pbm;													//Problème associé à la solution
	vector<double> _solution;												//Vecteur solution (de même dimension que le problème)
	double _current_fitness;												//Fitness de la solution

};

//===========================================================================================================================================

class SetUpParams {															//Contient différents paramètres utiles

public:

	SetUpParams(unsigned int runs = 30, unsigned int steps = 2000000,
			unsigned int pop = 40, unsigned int sol = 20);					//Constructeur
	~SetUpParams();															//Destructeur

	friend ostream& operator << (ostream&, const SetUpParams&);				//Opérateur de flux sortant
	friend istream& operator >> (istream&, SetUpParams&p);					//Opérateur de flux entrant

	const unsigned int independent_runs() const;							//Renvoie le nombre d'éxécutions indépendantes
	const unsigned int nb_evolution_steps() const;							//Renvoie le nombre d'itérations par éxécution
	const unsigned int population_size() const;								//Renvoie le nombre de solutions dans une population
	const unsigned int solution_size() const;								//Renvoie la taille de chaque particule

	void independent_runs(const unsigned int val);							//Modifie le nombre d'éxécutions indépendantes
	void nb_evolution_steps(const unsigned int val);						//Modifie le nombre d'itérations par éxécution
	void population_size(const unsigned int val);							//Modifie le nombre de solutions dans une population
	void solution_size(const unsigned int val);								//Modifie la taille de chauqe particule

private:

	unsigned int _independent_runs;											//Nombre d'éxécutions indépendantes
	unsigned int _nb_evolution_steps;										//Nombre d'itérations par éxécution
	unsigned int _population_size;											//Nombre de solutions dans une population
	unsigned int _solution_size;											//Taille de chaque particule

};

//===========================================================================================================================================

class MyAlgorithm {															//Contient l'instanciation d'une éxécution

public:

	MyAlgorithm(const Problem&, const SetUpParams&);						//Constructeur valué
	~MyAlgorithm();															//Destructeur

	friend ostream& operator << (ostream&, const MyAlgorithm&);				//Opérateur de flux sortant
	friend istream& operator >> (istream&, MyAlgorithm&);					//Opérateur de flux entrant

	MyAlgorithm& operator = (const MyAlgorithm&);							//Opérateur d'affectation

	const Problem& problem() const;											//Renvoie le problème de l'algorithme
	const SetUpParams& setup() const;										//Renvoie les paramètres de l'algorithme
	double upper_cost() const;												//Renvoie la fitness maximum
	double lower_cost() const;												//Renvoie la fitness minimum

	const vector<Solution*>& solutions() const;								//Renvoie la population de solutions
	Solution& solution(const unsigned int index) const;						//Renvoie un individu de la population
	vector<struct particle>& fitness_values();								//Renvoie la liste des particules (fitness + index)
	double fitness(const unsigned int index) const;							//Renvoie une fitness de la population

	double best_cost() const;												//Renvoie la meilleure fitness parmis la population
	double worst_cost() const;												//Renvoie la pire fitness parmis la population
	Solution& best_solution() const;										//Renvoie la meilleure solution parmis la population
	Solution& worst_solution() const;										//Renvoie la pire solution parmis la population

	void initialize();														//Génère une population aléatoirement
	void evaluate();														//Construit le tableau de fitness de la population

	void evolution(unsigned int); 											//Effectue une itération (contient l'algorithme génétique)

private:

	const Problem& _pbm;													//Problème traité par l'algorithme
	const SetUpParams& _setup;												//Paramètres de l'algorithme
	vector<Solution*> _solutions;    										//Population de solutions
	vector<struct particle> _fitness_values;								//Fitness de la population
	double _upper_cost, _lower_cost;										//Plus haute et basse fitness
	double mixrate;															//Paramètre de contrôle du crossover

};

#endif
