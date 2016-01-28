#include <iostream>
#include "backtracking.h"

using namespace std;

int main()
{
	const Problem pb = Problem(0);
	const SetUpParams setup = SetUpParams(30, 30, 30, 30);
	MyAlgorithm algo = MyAlgorithm(pb, setup);
	algo.initialize();
	algo.evaluate(pb);
	cout << "Hello World!" << endl << endl;

    return 0;
}
