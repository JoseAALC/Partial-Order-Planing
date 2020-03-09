/*
* @Author: ze
* @Date:   2017-04-09 19:04:25
* @Last Modified by:   ze
* @Last Modified time: 2017-06-18 10:38:40
*/
#include "RecordManager.hpp"
#include <iostream>
#include <string>
RecordManager::RecordManager(){}

RecordManager::~RecordManager(){		
	for (RecordFrame* frame: frames)
		delete(frame);
}		

void RecordManager::addRecord(State* state, Choice* choice,Bindings* binds){
	RecordFrame* frame = new RecordFrame(state,choice,binds);
	frames.push_back(frame);


}
RecordFrame* RecordManager::removeAndGetFrame(){
	RecordFrame* result = frames[frames.size()-1];
	frames.pop_back();
	return result;
}

bool RecordManager::isEmpty(){
	return frames.size()==0;
}

RecordFrame* RecordManager::top(){
	return frames[frames.size()-1];
}