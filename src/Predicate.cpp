#include "Predicate.hpp"
#include "Action.hpp"
#include <iostream>

int Predicate::idGiver=0;


Predicate::Predicate(string name,vector<string> vars,LogicSignal sign,Bindings* binds){
	this->name=name;
	this->binds = binds;
	this->id = idGiver++;
	for(int i=0;i<vars.size();i++)
		this->vars.push_back( binds->getNewBind(vars[i]));
	this->sign = sign;
	//this->binded = true;

}

void Predicate::addConst(string var){
	this->vars.push_back( binds->getNewBind(var));
}


Predicate::Predicate(string name,vector<int> vars,LogicSignal sign,Bindings* binds){
	this->name=name;
	this->id = idGiver++;
	this->binds = binds;
	this->vars = vars;
	this->sign = sign;
	//this->binded = true;

}

Predicate::~Predicate(){}

Predicate* Predicate::copy() const{
	
	Predicate* pre = new Predicate(name,vars,sign,binds);
	idGiver--;
	pre->id = this->id ;

	return pre;
}

Predicate* Predicate::copy(Bindings* binds) const{
	
	Predicate* pre = new Predicate(this->name,this->vars,this->sign,binds);
	idGiver--;
	pre->id = this->id ;
	return pre;
}

bool Predicate::isSameKind(const Predicate& other) const{
	return this->name == other.name && this->vars.size() == other.vars.size();
}
  
bool Predicate::operator==(const Predicate& other) const{
	if(!this->isSameKind(other))
    	return false;
	return other.id == this->id;
}

std::vector<int> Predicate::getVars() const{
	return this->vars;
}

LogicSignal Predicate::getSign() const{
	return this->sign;
}

std::string Predicate::getName() const{
	return this->name;
}

void Predicate::setVar(std::vector<int>& vars){
	for(int i=0;i<vars.size();i++)
		this->vars[i]=vars[i];
}

void Predicate::setVar(int pos , int var){
	this->vars[pos]=var;

}

void Predicate::setSign(LogicSignal sign){
	this->sign = sign;
}


std::string Predicate::getVar(int index) const{
	return binds->getValue(vars[index]);
}

Predicate::operator string() const{
	string s = ((sign==LogicSignal::NEGATIVE) ? "!":"") + name+"(";
  	for(int i=0;i<vars.size()-1;i++){
  		if(getVar(i)=="")
  			s+="x"+to_string(vars[i]);
    	s+= getVar(i)+",";
    }
    if(getVar(vars.size()-1)=="")
  		s+="x"+to_string(vars[vars.size()-1]);
  	s+= getVar(vars.size()-1) +")";
  	return s;

}

varKind Predicate::whatKind(int index) throw(logic_error){
	if(binds->getValue(vars[index])!="")
		return varKind::V_CONST;
	else
		return varKind::V_VAR;

}



bool Predicate::unify(Predicate& p){
	
	for(int i=0;i<vars.size();i++){
		if(p.getSign() == LogicSignal::NEGATIVE || this->sign == LogicSignal:: NEGATIVE)
			return false;
		if( p.whatKind(i) == varKind::V_CONST && whatKind(i) == varKind::V_CONST  ){
			if(getVar(i)!=p.getVar(i))
				return false;
		}
	}
	
	for(int i=0;i<vars.size();i++){
		if(p.whatKind(i)==varKind::V_CONST){
			this->binds->setReference(this->vars[i],p.vars[i]);
		}

		else{
			//cout<<string(*this)<<endl;
			//cout<<*this->binds<<endl;
			//cout<<string(p)<<endl;
			//cout<<*p.binds<<endl;
			//cout<<p.vars[i]<<" "<<this->vars[i]<<endl;
			if(this->vars[i] == 84 || p.vars[i] == 84){
				cout<<"ola\n";
			}
			this->binds->setReference(p.vars[i],this->vars[i]);
		}
	}
	return true;

};	


int Predicate::getId(){
	return id;
}


void Predicate::resetIds(){
	idGiver=0;
}