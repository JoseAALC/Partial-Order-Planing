#ifndef SUBGOALPHEURISTIC_HPP
#define SUBGOALPHEURISTIC_HPP
#include "Predicate.hpp"

class SubGoalpHeuristic{
	public:
		SubGoalpHeuristic(int (*heuristic)(Predicate* p));

		~SubGoalpHeuristic();
		void setHeuristic(int (*heuristic)(Predicate* p));
		int getValue(Predicate* p);
	protected:
	private:
		int (*heuristic)(Predicate* p);


};
#endif