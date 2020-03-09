#include "Action.hpp"

int Action::idGiver=0;

Action::~Action(){
	for(Predicate* pre: result)
		delete(pre);
	for(Predicate* pre: pre_condictions)
		delete(pre);
	delete(params);
}

Action::Action(std::vector<Predicate*> pre_condictions,std::vector<Predicate*> result,Predicate* params){
	this->id = idGiver++;
	this->pre_condictions = pre_condictions;
	this->result = result;
	this->params = params;
	this->is_solved.resize(pre_condictions.size());

}



    
std::vector<Predicate*> Action::getPre_Condiction() const{
	return this->pre_condictions;
}

std::vector<Predicate*> Action::getResult() const{
	return this->result;
}

Predicate* Action::getParams() const{
	return this->params;
}

bool Action::operator<(const Action& other) const{
	return this->id < other.id;

}

Action::operator std::string() const{
	string s = "PRECONDICTIONS: ";
	for(auto pre:pre_condictions)
		s+=string(*pre)+"^";
	s.pop_back();
	s+="\n"+ string(*params)+"\n";
	s+="RESULTS: ";
	for(auto pre:result)
		s+=string(*pre)+"^";
	s.pop_back();
	return s;

}
  
bool Action::getSolved(int index){
	return is_solved[index];
}

void Action::setSolved(int index){
	is_solved[index]=true;

}

int Action::getId(){
	return id;
}


Action* Action::copy(Bindings* binds) const{
	vector<Predicate*> pre;
	vector<Predicate*> results;
	for(Predicate* p:  getPre_Condiction())
		pre.push_back(p->copy(binds));

	for(Predicate* p:  getResult())
		results.push_back(p->copy(binds));

	Action* result = new Action(pre,results,getParams()->copy(binds));
	idGiver--;
	result->id = this->id ;
	for(int i=0;i<this->is_solved.size();i++)
		result->is_solved[i] = this->is_solved[i];

	return result;
}




Predicate* Action::searchPrecondiction(int id){
	for(Predicate* pre:pre_condictions)
		if(pre->getId() == id){
			return pre;
		}
	return nullptr;
}


void Action::resetIds(){
	idGiver=0;
}