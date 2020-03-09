#include "PredicateInstanciator.hpp"
#include <iostream>
PredicateInstanciator::PredicateInstanciator(string name,vector<int> vars,LogicSignal sign){
	this->name = name;
	this->vars = vars;
	this->sign = sign;
}
PredicateInstanciator::PredicateInstanciator(){}

void PredicateInstanciator::setSign(LogicSignal sign){
	this->sign =sign;
}
void PredicateInstanciator::setName( string name){
	this->name = name;
}


PredicateInstanciator::~PredicateInstanciator(){

}

Predicate* PredicateInstanciator::instanciate(unordered_map<int,int>& converter,Bindings* binds){
	vector<int> tmp = vars; 
	int c =0;
	for(int i=0;i<vars.size();i++){
		if(vars[i]==-1){
			tmp[i] =binds->getNewBind(constants[c++]);
			continue;
		}
		if( converter.find(tmp[i]) == converter.end())
			converter[tmp[i]] = binds->getNewBind();
		tmp[i]  = converter[tmp[i]];
	}
	Predicate* newPredicate =  new Predicate(this->name,tmp,this->sign,binds);
	
	return newPredicate;
}

bool PredicateInstanciator::operator==(const Predicate& other) const{
	return name == other.getName() && 
		sign == other.getSign() &&
		vars.size() == other.getVars().size();
}


void PredicateInstanciator::addVar(const int var){
	this->vars.push_back(var);

}
void PredicateInstanciator::addVar(const string var){
	this->vars.push_back(-1);
	this->constants.push_back(var);
}