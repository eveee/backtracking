#ifndef PROBLEM_H
#define PROBLEM_H
#include <vector>

class Problem
{
	public:
		Problem(int);
		~Problem();
/*
		friend ostream& operator<< (ostream& os, const Problem& pbm);
		friend istream& operator>> (istream& is, Problem& pbm);

		Problem& operator=  (const Problem& pbm);
		bool operator== (const Problem& pbm) const;
		bool operator!= (const Problem& pbm) const;
*/
		//Direction direction () const; //Maximize or Minimize
		int dimension() const;
		double LowerLimit, UpperLimit;
		double evaluate(std::vector<double>);
	private:
		int _dimension;
		int fct_id;
};

#endif // PROBLEM_H
