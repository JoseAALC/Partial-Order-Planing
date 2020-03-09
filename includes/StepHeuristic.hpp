#ifndef STEPHEURISTIC_HPP
#define STEPHEURISTIC_HPP
#include "Action.hpp"

class StepHeuristic{
	public:
		StepHeuristic(int (*heuristic)(Action* p));

		~StepHeuristic();
		void setHeuristic(int (*heuristic)(Action* p));
		int getValue(Action* p);
	protected:
	private:
		int (*heuristic)(Action* p);

};
#endif