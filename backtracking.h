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

class Problem {																//Contient la d�claration du probl�me

public:

	double LowerLimit, UpperLimit; 											//Les limites de l'ensemble d'arriv�e suivant chaque coordonn�e

	Problem();																//Constructeur par d�faut
	Problem(unsigned int, unsigned int, bool); 								//Constructeur valu�
	~Problem(); 															//Destructeur

	friend ostream& operator << (ostream&, const Problem&);					//Op�rateur de flux sortant
	friend istream& operator >> (istream&, Problem&);						//Op�rateur de flux entrant

	Problem& operator = (const Problem&); 									//Op�rateur d'affectation
	bool operator == (const Problem&) const; 								//Op�rateur de comparaison
	bool operator != (const Problem&) const; 								//Op�rateur de comparaison inverse

	unsigned int id() const; 												//Renvoie l'id de la fonction du probl�me
	unsigned int dimension() const; 										//Renvoie la dimension du probl�me
	bool direction() const; 												//Renvoie le direction du probl�me

	double evaluate(vector<double>&) const; 								//Evalue le vecteur d'entr�e

	void rosenbrock_limits();												//Modifie les limites du probl�me pour la fonction de Rosenbrock
	double rosenbrock_function(vector<double>&) const;						//Evalue le vecteur d'entr�e par la fonction de Rosenbrock
	void rastrigin_limits();												//Modifie les limites du probl�me pour la fonction de Rastrigin
	double rastrigin_function(vector<double>&) const;						//Evalue le vecteur d'entr�e par la fonction de Rastrigin
	void ackley_limits();													//Modifie les limites du probl�me pour la fonction de Ackley
	double ackley_function(vector<double>&) const;							//Evalue le vecteur d'entr�e par la fonction de Ackley
	void schwefel_limits();													//Modifie les limites du probl�me pour la fonction de Schwefel
	double schwefel_function(vector<double>&) const;						//Evalue le vecteur d'entr�e par la fonction de Schwefel
	void schaffer_limits();													//Modifie les limites du probl�me pour la fonction de Schaffer
	double schaffer_function(vector<double>&) const;						//Evalue le vecteur d'entr�e par la fonction de Schaffer
	void weierstrass_limits();												//Modifie les limites du probl�me pour la fonction de Weierstrass
	double weierstrass_function(vector<double>&) const;						//Evalue le vecteur d'entr�e par la fonction de Weierstrass

	void test_limits();														//---!!!---Limites pour la fonction de test---!!!---
	double test_function(vector<double>&) const; 							//---!!!-----------Fonction de test-----------!!!---

private:

	unsigned int fct_id; 													//Id de la fonction choisie
	unsigned int _dimension; 												//Dimension du probl�me
	bool _direction; 														//true si on cheche le maximum, false sinon

};

//===========================================================================================================================================

class Solution {															//Contient la d�claration d'une solution

public:

	Solution(const Problem&);												//Constructeur valu�
	Solution(const Solution&);												//Constructeur par recopie
	~Solution();															//Destructeur

	friend ostream& operator << (ostream&, const Solution&);				//Op�rateur de flux sortant
	friend istream& operator >> (istream&, Solution&);						//Op�rateur de flux entrant

	Solution& operator = (const Solution&);									//Op�rateur d'affectation
	bool operator == (const Solution&) const;								//Op�rateur de comparaison
	bool operator != (const Solution&) const;								//Op�rateur de comparaison inverse

	const Problem& problem() const;											//Renvoie le probl�me de la solution
	vector<double>& solution();												//Renvoie le vecteur solution
	unsigned int size() const;												//Renvoie la dimension de la solution
	double& position(const unsigned int) const; 							//Renvoie une coordonn�e de la solution
	double get_fitness() const;												//Renvoie la fitness de la solution

	void set_solution(vector<double>&);										//Modifie le vecteur solution
	void position(const unsigned int, const double);						//Modifie une coordonn�e du vecteur solution
	double fitness();														//Calcule la fitness du vecteur solution

	void initialize(int = 0);												//G�n�re un vecteur solution al�atoire

private:

	const Problem& _pbm;													//Probl�me associ� � la solution
	vector<double> _solution;												//Vecteur solution (de m�me dimension que le probl�me)
	double _current_fitness;												//Fitness de la solution

};

//===========================================================================================================================================

class SetUpParams {															//Contient diff�rents param�tres utiles

public:

	SetUpParams(unsigned int runs = 30, unsigned int steps = 2000000,
			unsigned int pop = 40, unsigned int sol = 20);					//Constructeur
	~SetUpParams();															//Destructeur

	friend ostream& operator << (ostream&, const SetUpParams&);				//Op�rateur de flux sortant
	friend istream& operator >> (istream&, SetUpParams&p);					//Op�rateur de flux entrant

	const unsigned int independent_runs() const;							//Renvoie le nombre d'�x�cutions ind�pendantes
	const unsigned int nb_evolution_steps() const;							//Renvoie le nombre d'it�rations par �x�cution
	const unsigned int population_size() const;								//Renvoie le nombre de solutions dans une population
	const unsigned int solution_size() const;								//Renvoie la taille de chaque particule

	void independent_runs(const unsigned int val);							//Modifie le nombre d'�x�cutions ind�pendantes
	void nb_evolution_steps(const unsigned int val);						//Modifie le nombre d'it�rations par �x�cution
	void population_size(const unsigned int val);							//Modifie le nombre de solutions dans une population
	void solution_size(const unsigned int val);								//Modifie la taille de chauqe particule

private:

	unsigned int _independent_runs;											//Nombre d'�x�cutions ind�pendantes
	unsigned int _nb_evolution_steps;										//Nombre d'it�rations par �x�cution
	unsigned int _population_size;											//Nombre de solutions dans une population
	unsigned int _solution_size;											//Taille de chaque particule

};

//===========================================================================================================================================

class MyAlgorithm {															//Contient l'instanciation d'une �x�cution

public:

	MyAlgorithm(const Problem&, const SetUpParams&);						//Constructeur valu�
	~MyAlgorithm();															//Destructeur

	friend ostream& operator << (ostream&, const MyAlgorithm&);				//Op�rateur de flux sortant
	friend istream& operator >> (istream&, MyAlgorithm&);					//Op�rateur de flux entrant

	MyAlgorithm& operator = (const MyAlgorithm&);							//Op�rateur d'affectation

	const Problem& problem() const;											//Renvoie le probl�me de l'algorithme
	const SetUpParams& setup() const;										//Renvoie les param�tres de l'algorithme
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

	void initialize();														//G�n�re une population al�atoirement
	void evaluate();														//Construit le tableau de fitness de la population

	void evolution(unsigned int); 											//Effectue une it�ration (contient l'algorithme g�n�tique)

private:

	const Problem& _pbm;													//Probl�me trait� par l'algorithme
	const SetUpParams& _setup;												//Param�tres de l'algorithme
	vector<Solution*> _solutions;    										//Population de solutions
	vector<struct particle> _fitness_values;								//Fitness de la population
	double _upper_cost, _lower_cost;										//Plus haute et basse fitness
	double mixrate;															//Param�tre de contr�le du crossover

};

#endif
