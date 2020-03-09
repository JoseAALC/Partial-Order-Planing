/*
* @Author: ze
* @Date:   2017-04-10 23:09:55
* @Last Modified by:   ze
* @Last Modified time: 2017-09-28 19:47:56
*/
#include "gtest/gtest.h"
#include "Parser.hpp"


int lessResults(ActionInstanciator* a){ return a->getResult().size();}

int moreResults(ActionInstanciator* a){ return -a->getResult().size();}



int main(int argc, char **argv) 
{






	cout<<"argv:" << argv[1]<<endl;
	Parser p;
	PlanningProblem* problem = p.parse(argv[1]);

	cout<<"3 Rooms Scenario:\n";

	cout<<"Operators with less poscondictions first\n";


	Heuristics* h1 = new Heuristics();
	

	problem->POP(h1);
	State* state = problem->POP(h1);
 	state->printPath();
	delete(problem);




	//testing::InitGoogleTest(&argc, argv);
	return 0;//RUN_ALL_TESTS();
}