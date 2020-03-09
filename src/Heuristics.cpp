#include "Heuristics.hpp"

Heuristics::Heuristics(){
	this->sub = new SubGoalpHeuristic( [](Predicate* p){return p->getId();});
	this->op = new OperatorHeuristic( [](ActionInstanciator* p){return 1;});
	this->step = new StepHeuristic( [](Action* p){return p->getId();});
}

Heuristics::~Heuristics(){
	delete(this->sub);
	delete(this->op);
	delete(this->step);
}

void Heuristics::setHeuristic(int (*heuristic)(Predicate* p)){
	this->sub->setHeuristic(heuristic);
}
void Heuristics::setHeuristic(int (*heuristic)(ActionInstanciator* p)){
	this->op->setHeuristic(heuristic);
}
void Heuristics::setHeuristic(int (*heuristic)(Action* p)){
	this->step->setHeuristic(heuristic);
}


int Heuristics::getValue(Predicate* p){
	return this->sub->getValue(p);
}
int Heuristics::getValue(ActionInstanciator* p){
	return this->op->getValue(p);
}
int Heuristics::getValue(Action* p){
	return this->step->getValue(p);
}