#include "OperatorHeuristic.hpp"

OperatorHeuristic::OperatorHeuristic(int (*heuristic)(ActionInstanciator* p)){
	this->heuristic = heuristic;
}

OperatorHeuristic::~OperatorHeuristic(){}

void OperatorHeuristic::setHeuristic( int (*heuristic)(ActionInstanciator* p)){
	this->heuristic = heuristic;
}

int OperatorHeuristic::getValue(ActionInstanciator* p){
	return this->heuristic(p);
}