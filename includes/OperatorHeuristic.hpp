#ifndef OPERATORHEURISTIC_HPP
#define OPERATORHEURISTIC_HPP
#include "ActionInstanciator.hpp"

class OperatorHeuristic{
	public:
		OperatorHeuristic(int (*heuristic)(ActionInstanciator* p));

		~OperatorHeuristic();
		void setHeuristic( int (*heuristic)(ActionInstanciator* p));
		int getValue(ActionInstanciator* p);
	protected:
	private:
		int (*heuristic)(ActionInstanciator* p);


};
#endif