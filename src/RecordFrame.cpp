#include "RecordFrame.hpp"
#include <iostream>
RecordFrame::RecordFrame(State* state, Choice* choice,Bindings* binds){
	this->binds = binds;
	this->state = state;
	this->choice = choice;
	
}

RecordFrame::~RecordFrame(){
	delete(binds);
	delete(choice);
	delete(state);
}

State* RecordFrame::getState() const{
	return this->state;
}
Bindings* RecordFrame::getBinds() const{
	return this->binds;
}
Choice* RecordFrame::getChoice() const{
	return this->choice;
}


RecordFrame::operator string() const{
	string s="(";
	Choice* choice = this->getChoice();
	ChoiceKind kind = choice->getKind();
	s+= (kind == 0 ? "C_CREATE" : (kind== 1 ? "C_ASSOCIATE":"C_UNIFY") );
	s+=")";
	return s;

}