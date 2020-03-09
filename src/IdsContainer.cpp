#include "IdsContainer.hpp"
#include <iostream>
IdsContainer::IdsContainer(){


}

IdsContainer::~IdsContainer(){}

bool IdsContainer::isIn(int id){
	int offset = id/32;
	int bit = id%32;



	if(this->_32bitscontainer.size() <= offset)
		resize(id);

	return (1<<(bit)) == (this->_32bitscontainer[offset] & (1<<(bit)));
}

void IdsContainer::setId(int id){
	int offset = id/32;
	int bit = id%32;


	if(this->_32bitscontainer.size() <= offset)
		resize(id);
	

	this->_32bitscontainer[offset] |= (1<<(bit)); 
}
void IdsContainer::resize(int maxid){
	int offset = maxid/32;
	if(offset >= this->_32bitscontainer.size())
		this->_32bitscontainer.resize(offset+1);

}
void IdsContainer::forceResize(int maxid){
	int offset = maxid/32;
	cout<<"offset: "<<offset<<endl;
	this->_32bitscontainer.resize(offset+1);
}

vector<int> IdsContainer::getContainer(){
	return this->_32bitscontainer;
}