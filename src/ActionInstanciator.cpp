#include "ActionInstanciator.hpp"

ActionInstanciator::ActionInstanciator(std::vector<PredicateInstanciator*> pre_condictions,std::vector<PredicateInstanciator*> result,PredicateInstanciator* params){
	this->result = result;
	this->pre_condictions = pre_condictions;
	this->params = params;
}

ActionInstanciator::~ActionInstanciator(){
	for(PredicateInstanciator* pre: result)
		delete(pre);
	for(PredicateInstanciator* pre: pre_condictions)
		delete(pre);
	delete(params);
}

std::vector<PredicateInstanciator*> ActionInstanciator::getPre_Condiction(){
	return pre_condictions;
}

std::vector<PredicateInstanciator*> ActionInstanciator::getResult(){
	return result;
}
	
PredicateInstanciator* ActionInstanciator::getParams(){
	return params;
}


Action* ActionInstanciator::instanciate(Bindings* binds){
	unordered_map<int,int> converter;
	vector<Predicate*> result;
	vector<Predicate*> pre_condictions;
	Predicate* params;

	params = this->params->instanciate(converter,binds);
	for(PredicateInstanciator* p: this->getPre_Condiction()){
		pre_condictions.push_back(p->instanciate(converter,binds));
	}

	for(PredicateInstanciator* p: this->getResult()){
		result.push_back(p->instanciate(converter,binds));
	}

	return new Action(pre_condictions,result,params);

}