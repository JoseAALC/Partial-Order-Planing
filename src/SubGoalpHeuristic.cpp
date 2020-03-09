#include "SubGoalpHeuristic.hpp"

SubGoalpHeuristic::SubGoalpHeuristic(int (*heuristic)(Predicate* p)){
	this->heuristic = heuristic;
}

SubGoalpHeuristic::~SubGoalpHeuristic(){}

int SubGoalpHeuristic::getValue(Predicate* p){
	return this->heuristic(p);
}

void SubGoalpHeuristic::setHeuristic(int (*heuristic)(Predicate* p)){
	this->heuristic = heuristic;
}