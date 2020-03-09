#include "StepHeuristic.hpp"

StepHeuristic::StepHeuristic(int (*heuristic)(Action* p)){
	this->heuristic = heuristic;
}

StepHeuristic::~StepHeuristic(){}

void StepHeuristic::setHeuristic(int (*heuristic)(Action* p)){
	this->heuristic = heuristic;
}
int StepHeuristic::getValue(Action* p){
	return this->heuristic(p);
}