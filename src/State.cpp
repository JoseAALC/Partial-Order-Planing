/*
* @Author: ze
* @Date:   2017-04-09 19:04:25
* @Last Modified by:   ze
* @Last Modified time: 2017-06-18 10:50:02
*/
#include "State.hpp"
#include <iostream>
#include <algorithm>
State::State(){}
State::State(vector<Action*>& steps,vector<tuple<Action*,Predicate*,Action*>> links,unordered_map<int,vector<int>> ordering){
	this->steps = steps;
	this->links = links;
	this->ordering = ordering;
}

State::~State(){
	for(Action* step:steps)
		delete(step);	
}

void State::addStep(Action* a){
	steps.push_back(a);
}
void State::setLink(Action* a ,Predicate* c,Action* b){
	links.push_back(make_tuple(a,c,b));

}
void State::setOrder(Action* a,Action* b){
	if(find(ordering[a->getId()].begin(),ordering[a->getId()].end(),(b->getId())) == ordering[a->getId()].end())
		ordering[a->getId()].push_back(b->getId());
}

std::vector<Action*> State::getSteps(){
	return steps;
}



void State::printPath(){
	sort(steps.begin(),steps.end(),[&](Action* a,Action* b){
		for(auto id :ordering[a->getId()])
			if(id == b->getId())
				return true;
		for(auto id :ordering[b->getId()])
			if(id == a->getId())
				return false;
		return true;
	});

	for(Action* step:steps)
		cout<<string(*step->getParams())<<" "<<step->getId()<<endl<<endl;


	
	

}


State* State::copy(Bindings* binds) const{
	vector<Action*> steps2;
	vector<tuple<Action*,Predicate*,Action*>> links2;
	for(Action* step: steps)
		steps2.push_back(step->copy(binds));
	for(auto link:links){
		Action* left = nullptr;
		Action* right = nullptr;
		Predicate* solved = nullptr;
		for(Action* step:steps2)
			if( get<0>(link)->getId() == step->getId() ){
				left = step;
				for(Predicate* p:left->getResult())
					if(p->getId() == get<1>(link)->getId()){
						solved = p;
						break;
					}
				break;
			}
		for(Action* step:steps2)
			if( get<2>(link)->getId() == step->getId() ){
				right=step;
				break;
			}

		links2.push_back(make_tuple(left,solved,right));
	}

	
	return new State(steps2,links2,ordering);


}




bool State::checkConsistence(int start){
	vector<int> v(steps[steps.size()-1]->getId()+1);
	vector<int> stack;
	
	
	v[start] =0;
	stack.push_back(start);
	while(!stack.empty()){
		int node = stack.back();
		stack.pop_back();

		for(int n :ordering[node]){
			if(v[node]+1<steps.size()){
				stack.push_back(n);
				v[n]=v[node]+1;
			}
			else{
	
				return false;
			}
		}
		
	}

	return true;


}


Action* State::searchStep(int id) const{
	for(Action* step:steps)
		if(step->getId() == id)
			return step;
	return nullptr;

}


bool State::dfs(int index,int target){
	



	vector<int> visited(steps[steps.size()-1]->getId()+1);

	
	//cout<<"SIZE: "<<visited.size()<<endl;
	//cout<<"INDEX: "<<index-error<<endl;
	vector<int> stack;
	visited[index] =1;

	stack.push_back(index);
	while(!stack.empty()){
		int node = stack.back();
		stack.pop_back();
		if(node == target){
			return true;
		}
		
		for(int n:ordering[node]){


			if(!visited[n]){
				stack.push_back(n);
				visited[n]=1;
			}
		}
	}
	return false;

}

bool State::reachable(int index1,int index2){
	return this->dfs(index1,index2) || this->dfs(index2,index1); 
}

vector<tuple<Action*,Predicate*,Action*>> State::getPositivePredicates(pair<Action*,Predicate*>& negative){
	vector<tuple<Action*,Predicate*,Action*>> positives;
	for(auto link: links)
			if(get<1>(link)->getSign() == LogicSignal::POSITIVE && get<1>(link)->isSameKind(*negative.second)){
				bool same =true;
				for(int i=0;i<get<1>(link)->getVars().size();i++)
					if(get<1>(link)->getVar(i) != negative.second->getVar(i)){
						same = false;
						break;

					}
				if(same)
					positives.push_back(make_tuple(get<0>(link),get<1>(link),get<2>(link) ));	
				}


	return positives;
}

vector<pair<Action*,Predicate*>> State::getNegativePredicates(){
	vector<pair<Action*,Predicate*>> negatives;
	for(Action* step: steps)
		for(Predicate* pre:step->getResult())
			if(pre->getSign() == LogicSignal::NEGATIVE ){
				bool negativeAccepted=true;
				for(int i=0;i<pre->getVars().size();i++)
					if(pre->getVar(i)=="")
						negativeAccepted=false;
				if(negativeAccepted)
					negatives.push_back(make_pair(step,pre));
			}
	return negatives;


}

vector<tuple<Action*,Predicate*,Action*>> State::getLinks(){
	return links;
}

bool State::resolveThreat(pair<Action*,Predicate*>& negative,tuple<Action*,Predicate*,Action*>& positive){
	//cout<<"IDS: "<<negative.first->getId()<<" "<<get<2>(positive)->getId()<<endl;
	if(reachable(negative.first->getId(),get<2>(positive)->getId() )){
	//	cout<<"REACHING------------------!\n";
		return true;
	}

	
	else if(get<0>(positive)->getParams()->getName() == "Initial" ){
		if(get<2>(positive)->getParams()->getName() == "Final")
			return false;
		else{
			this->setOrder(get<2>(positive),negative.first);
	//		cout<<"PROMOTION: "<<get<2>(positive)->getId()<<" "<<negative.first->getId()<<endl;
		}

	}
	else{
		this->setOrder(negative.first,get<0>(positive));
		

		for(int i =0;i<ordering[get<0>(positive)->getId()].size();i++){
			
			if(ordering[get<0>(positive)->getId()][i] == negative.first->getId()){
	//			cout<<"ELIMINATEDP "<<ordering[get<0>(positive)->getId()][i]<<" "<<negative.first->getId()<<endl;
				ordering[get<0>(positive)->getId()].erase(ordering[get<0>(positive)->getId()].begin() +i);
			}
		}

		for(auto& step:steps)
			for(int i=0;i<ordering[step->getId()].size();i++)
				if(step->getParams()->getName() != "Initial" && step->getId() !=  negative.first->getId() && ordering[step->getId()][i] == get<0>(positive)->getId()){
					
					ordering[step->getId()][i] = negative.first->getId();
				}




	//	cout<<"DEMOTION: "<<negative.first->getId()<<" "<<get<0>(positive)->getId()<<endl;
	}
	return true;

}


bool State::resolveAllThreats(){
	for(auto neg: getNegativePredicates()){
	//	cout<<"NEGATIVE: "<<string(*neg.second)<<endl;
		for(auto pos: getPositivePredicates(neg)){
	//		cout<<"POSITIVE: "<<string(*get<1>(pos))<<endl;

			if(!resolveThreat(neg,pos)){
	//			cout<<endl;cout<<endl;
				return false;
			}
		}
	}



	return true;
}