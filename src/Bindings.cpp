#include "Bindings.hpp"
#include <algorithm>
#include <iostream>
#include <exception>
Bindings::Bindings(){}

Bindings::~Bindings(){}

Bindings* Bindings::copy() const{
	Bindings* instance = new Bindings();
	instance->binds.resize(this->binds.size());
	//std::copy(binds.begin(), binds.end(),instance->binds.begin());
	for(int i=0;i<this->binds.size();i++)
		instance->binds[i] = this->binds[i];
	for ( auto it = this->constants.begin(); it != this->constants.end(); ++it )
		instance->constants[it->first] = it->second;
	return instance;


};
int Bindings::getNewBind(){
	int newIndex = binds.size();
	binds.push_back(newIndex);
	return newIndex;
}
int Bindings::getNewBind(string constant){
	int newIndex  = getNewBind();
	constants[newIndex] = constant;
	return newIndex;

}
bool Bindings::isConst(int index){
	if(index >= binds.size())
		throw out_of_range("isConst out of range");
	int indexer = index;
	while(binds[indexer]!=indexer){
		indexer = binds[indexer];
	}
	
	return constants.find(indexer)!= constants.end();
}

string Bindings::getValue(int index){
	if(index >= binds.size())
		throw out_of_range("value out of range");
	int indexer = index;
	
	while(binds[indexer]!=indexer){
		indexer = binds[indexer];
	}
	
	if(constants.find(indexer)!= constants.end())
		return constants[indexer];
	return "";

}
void Bindings::setReference(int index,int reference){
	



	if(index >= binds.size())
		throw out_of_range("index out of range");
	if(reference >= binds.size())
		throw out_of_range("reference out of range");
	
	while(binds[index]!=index){
		index = binds[index];
	}
	while(binds[reference]!=reference){
		reference = binds[reference];
	}

		binds[index] = reference;
	
	
}



ostream& operator<<(ostream& os, const Bindings& dt){
	for(int i=0;i<dt.binds.size();i++)
		os<<i<<" "<<dt.binds[i]<<endl;
	return os;
}