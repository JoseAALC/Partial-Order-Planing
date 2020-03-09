#include "Choice.hpp"

Choice::Choice(ChoiceKind kind,int iter,Predicate* Cneed,Action* Sneed,Action* resolver,IdsContainer* ids){
	this->kind = kind;
	this->iteraction=iter;
	this->Cneed = Cneed;
	this->Sneed = Sneed;
	this->resolver = resolver;
	this->ids = ids;
}

Choice::~Choice(){
	delete(this->ids);

}

ChoiceKind Choice::getKind(){
	return kind;
}

tuple<ChoiceKind,int,Predicate*,Action*,Action*> Choice::getChoice(){
	return make_tuple(this->kind,this->iteraction,this->Cneed,this->Sneed,this->resolver);
}


IdsContainer* Choice::getIds(){
	return this->ids;
}