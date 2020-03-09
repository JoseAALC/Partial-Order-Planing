#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP
#include "SubGoalpHeuristic.hpp"
#include "OperatorHeuristic.hpp"
#include "StepHeuristic.hpp"


class Heuristics{
	public:
		Heuristics();

		~Heuristics();
		void setHeuristic(int (*heuristic)(Predicate* p));
		void setHeuristic(int (*heuristic)(ActionInstanciator* p));
		void setHeuristic(int (*heuristic)(Action* p));
		int getValue(Predicate* p);
		int getValue(ActionInstanciator* p);
		int getValue(Action* p);

	protected:
	private:
		SubGoalpHeuristic* sub;
		OperatorHeuristic* op;
		StepHeuristic* step;


};
#endif