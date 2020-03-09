#include "PlanningProblem.hpp"	
#include <iostream>
#include <cassert>

#define IDS_SIZE 64

int numberOfBacktracks =0;


PlanningProblem::PlanningProblem(Action* initial,Action* target,vector<ActionInstanciator*> operators,Bindings* binds){
	this->initial = initial;
	this->operators = operators;
	this->target = target;
	this->binds = binds;
	this->plan = new State();
	this->heuristics = nullptr;

}
PlanningProblem::PlanningProblem(Bindings* binds){
	this->heuristics = nullptr;
	this->binds = binds;
	vector<Predicate*> init;

	init.push_back(new Predicate("Robot",{string("Roon1")},LogicSignal::POSITIVE,this->binds));
	init.push_back(new Predicate("Door",{string("Roon1"),"Roon2"},LogicSignal::POSITIVE,this->binds));
	init.push_back(new Predicate("Door",{string("Roon2"),"Roon3"},LogicSignal::POSITIVE,this->binds));
	init.push_back(new Predicate("Door",{string("Roon3"),"Roon2"},LogicSignal::POSITIVE,this->binds));
	init.push_back(new Predicate("Door",{string("Roon2"),"Roon1"},LogicSignal::POSITIVE,this->binds));
	vector<Predicate*>  finish;
	finish.push_back(new Predicate("Robot",{string("Roon3")},LogicSignal::POSITIVE,this->binds));

	
	this->initial = new Action(vector<Predicate*>(),init,new Predicate("Initial",{"initial"}	,LogicSignal::POSITIVE,this->binds));

	this->target = new Action(finish,vector<Predicate*>(),new Predicate("Final",{"final"}	,LogicSignal::POSITIVE,this->binds));

	vector<PredicateInstanciator*> pre_cond;
	vector<PredicateInstanciator*> pos_cond;
	PredicateInstanciator* args = new PredicateInstanciator("Go",{1,2},LogicSignal::POSITIVE);

	pre_cond.push_back(new PredicateInstanciator("Robot",{1},LogicSignal::POSITIVE));
	pre_cond.push_back(new PredicateInstanciator("Door",{1,2},LogicSignal::POSITIVE));
	pos_cond.push_back(new PredicateInstanciator("Robot",{2},LogicSignal::POSITIVE));
	pos_cond.push_back(new PredicateInstanciator("Robot",{1},LogicSignal::NEGATIVE));

	ActionInstanciator* go = new ActionInstanciator(pre_cond,pos_cond,args);
	this->operators.push_back(go);

	this->plan = new State();

}
PlanningProblem::~PlanningProblem(){
	delete(plan);
	delete(heuristics);
	for(ActionInstanciator* op: operators)
		delete(op);
	delete(binds);
	Action::resetIds();
	Predicate::resetIds();
	
}




bool PlanningProblem::is_Solution(){
	for(Action* step:plan->getSteps()){
		for(int i=0;i<step->getPre_Condiction().size();i++){
			if(!step->getSolved(i))
				return false;
		}
	}


	return true;


}

pair<Action*,Predicate*> PlanningProblem::selectSubgoal(State* s,int iterator){
	for(Action* step:plan->getSteps()){
		for(int i=iterator;i<step->getPre_Condiction().size();i++){
			if(!step->getSolved(i)){

				/*cout<<"<SUBPROBLEM>\n";
				cout<<string(*step)<<endl;
				cout<<string(*step->getPre_Condiction()[i])<<endl;
				cout<<"</SUBPROBLEM>\n\n";*/
				return make_pair(step,step->getPre_Condiction()[i]);
			}
		}
	}
	return make_pair(nullptr,nullptr);
}
Action* PlanningProblem::chooseStep(Action* Sneed,Predicate* c,IdsContainer* ids){

	
	int bestStepIndex = -1;
	int heuristicOfStep = 1000;
	//iterate all steps on plan
	for(int i=0;i<plan->getSteps().size();i++)	
		//we can't solve something with itself
		if(plan->getSteps()[i]->getId() != Sneed->getId()){
			//here we must choice by heuristic value
			if( !ids->isIn(i) ){
				//if the value of heuristic is lower(better) then we change values
				if(heuristicOfStep > heuristics->getValue(plan->getSteps()[i])){ 
					heuristicOfStep = heuristics->getValue(plan->getSteps()[i]);
					bestStepIndex = i;
				}
			}

		}
	if(bestStepIndex == -1)
		return nullptr;

	//iterate for poscondictions of the step choosed
	for(Predicate* solver: plan->getSteps()[bestStepIndex]->getResult())
		//the predicates must be the same kind and have the same sign
		if(solver->isSameKind(*c) && solver->getSign() == LogicSignal::POSITIVE ){
			bool isValid = true;
			for(int i=0;i<solver->getVars().size();i++)
				if(solver->whatKind(i) == c->whatKind(i) && solver->whatKind(i) ==varKind::V_CONST && solver->getVar(i)!=c->getVar(i) ){
					isValid=false;

				}
				if(isValid){
					/*cout<<"<STEP>\n";
					cout<<"\t<Sneed>\n";
					cout<<string(*Sneed)<<endl;
					cout<<"\t</Sneed>\n";
					cout<<"C: "<<string(*c)<<endl;
					cout<<string(*plan->getSteps()[bestStepIndex])<<endl;
					cout<<"</STEP>\n\n";
					*/

					//save
					Bindings* newBinds = this->binds->copy();
					State* newPlan = plan->copy(newBinds);
					Action* newSneed = newPlan->searchStep(Sneed->getId());
					Predicate* newCneed = newSneed->searchPrecondiction(c->getId());
					
					//create a set of ids
					ids->setId(bestStepIndex);
						

					//record
					recordmanager.addRecord(newPlan,new Choice(C_ASSOCIATE,bestStepIndex,newCneed,newSneed,nullptr,ids),newBinds);

					return plan->getSteps()[bestStepIndex];
					}
				}
		
	return nullptr;

}

Action* PlanningProblem::chooseOperator(Action* Sneed,Predicate*Cneed,IdsContainer* ids){
	//heuristic variables
	int bestOperatorIndex = -1;
	int heuristicOfOperator = 1000;

	//iterate for all operators
	for(int i=0;i<operators.size();i++)
		//iterate from results
		for(PredicateInstanciator* solver: operators[i]->getResult()){
			//if an result can solve the cneed
			if(*solver == *Cneed){
				//if it's index was not tried yet!
				if( !ids->isIn(i) ){
					if(heuristicOfOperator > heuristics->getValue(operators[i])){ 
						heuristicOfOperator = heuristics->getValue(operators[i]);
						bestOperatorIndex = i;
					}
				}
			}
		}

	if(bestOperatorIndex == -1)
		return nullptr;	

			

	Bindings* newBinds = this->binds->copy();
	State* newPlan = plan->copy(newBinds);
	Action* newSneed = newPlan->searchStep(Sneed->getId());
	Predicate* newCneed = newSneed->searchPrecondiction(Cneed->getId());

	//create a set of ids
	ids->setId(bestOperatorIndex);

	//record
	recordmanager.addRecord(newPlan,new Choice(C_CREATE,bestOperatorIndex,newCneed,newSneed,nullptr,ids),newBinds);

	Action* Sadd = operators[bestOperatorIndex]->instanciate(this->binds);
	/*cout<<"<OPERATOR>\n";
	cout<<string(*Sadd)<<endl;
	cout<<"C: "<<string(*Cneed)<<endl;

	cout<<"</OPERATOR>\n\n";
	*/


	plan->addStep(Sadd);
				
	plan->setOrder(initial,Sadd);
	plan->setOrder(Sadd,target);

				
				
	return Sadd;

}




pair<Action*,Predicate*> PlanningProblem::chooseUnification(Action* Sneed,Predicate* c,Action* resolver,int iterator){
	for(int i=iterator;i<resolver->getResult().size();i++)
		if(resolver->getResult()[i]->isSameKind(*c)){
			/*cout<<"<UNIFY>\n";
			cout<<string(*resolver)<<endl;
			cout<<string(*c)<<" "<<c->getVars()[0]<<" SneedId: "<<Sneed->getId()<<endl;
			cout<<string(*resolver->getResult()[i])<<" "<<resolver->getId()<<endl;
			cout<<"</UNIFY>\n\n";
			cout<<"STEPS: "<<plan->getSteps().size()<<endl;
			//cout<<"UNIFY: "<<string(*c)<<endl;
			*/
			Bindings* newBinds = this->binds->copy();
			
			State* newPlan = plan->copy(newBinds);
			Action* newSneed = newPlan->searchStep(Sneed->getId());
			Predicate* newCneed = newSneed->searchPrecondiction(c->getId());
			

			IdsContainer* ids = new IdsContainer();
			ids->resize(IDS_SIZE);
			ids->setId(i);
			
			//record
			recordmanager.addRecord(newPlan,new Choice(C_UNIFY,i,newCneed,newSneed,resolver,ids),newBinds);
			
			if(!c->unify(*resolver->getResult()[i])){
				//cout<<"HERE2\n";
				
				delete(recordmanager.removeAndGetFrame());
				
				continue;
				
			}
			else{
				
				plan->setOrder(resolver,Sneed);
				plan->setLink(resolver,resolver->getResult()[i],Sneed);
				

				for(int i=0;i<Sneed->getPre_Condiction().size();i++)
					if(*Sneed->getPre_Condiction()[i]== *c)
						Sneed->setSolved(i);
				//saves
				
				return make_pair(resolver,resolver->getResult()[i]);
			}

		}
		return make_pair(nullptr,nullptr);
}



bool PlanningProblem::backtracking(){
	if(recordmanager.isEmpty() )
		return false;

	numberOfBacktracks++;
	
	RecordFrame* frame = recordmanager.removeAndGetFrame();

	this->plan = frame->getState();

	this->binds = frame->getBinds();
	

	Choice* choice = frame->getChoice();
	ChoiceKind kind = choice->getKind();

	//	cout<<"BACKTRACK: "<<(kind == 0 ? "C_CREATE" : (kind== 1 ? "C_ASSOCIATE":"C_UNIFY") ) <<endl<<endl;
	
	//things maded during the choice 
	tuple<ChoiceKind,int,Predicate*,Action*,Action*> choicedMatter = choice->getChoice();

	if(kind == C_CREATE){
		Action* result = chooseOperator(get<3>(choicedMatter),get<2>(choicedMatter),choice->getIds());
		if(result == nullptr)
			return backtracking();
		else{
			pair<Action*,Predicate*> result2 = chooseUnification(get<3>(choicedMatter),get<2>(choicedMatter),result,0);
			if(result2.first == nullptr || !plan->resolveAllThreats()|| !plan->checkConsistence(result2.first->getId() ) ){
				return backtracking();
			}

		}
	} 
	else if(kind ==C_ASSOCIATE){
		
		Action* result = chooseStep(get<3>(choicedMatter),get<2>(choicedMatter),choice->getIds());
		
		if(result == nullptr){
			result = chooseOperator(get<3>(choicedMatter),get<2>(choicedMatter),new IdsContainer());
			
			if(result == nullptr)
				return backtracking();

			else{
				
				pair<Action*,Predicate*> result2 = chooseUnification(get<3>(choicedMatter),get<2>(choicedMatter),result,0);
				if(result2.first == nullptr || !plan->resolveAllThreats()|| !plan->checkConsistence(result2.first->getId() )){
					return backtracking();
				}

			}
		}
		else{
			pair<Action*,Predicate*> result2 = chooseUnification(get<3>(choicedMatter),get<2>(choicedMatter),result,0);
			if(result2.first == nullptr || !plan->resolveAllThreats()|| !plan->checkConsistence(result2.first->getId() )){
				return backtracking();
			}
		}
	}
	else if(kind ==C_UNIFY){
		
		pair<Action*,Predicate*> result = chooseUnification(get<3>(choicedMatter),get<2>(choicedMatter),get<4>(choicedMatter),get<1>(choicedMatter)+1);
		if(result.first == nullptr  ||!plan->resolveAllThreats()|| !plan->checkConsistence(result.first->getId() ) ){
			return backtracking();
		}

	}

	cout<<"BACKTRACK END\n\n";
			
	

	return true;
}


State* PlanningProblem::POP(Heuristics* heuristics){
	plan->addStep(initial);
	plan->addStep(target);
	
	
	this->heuristics = heuristics;


	plan->setOrder(initial,target);
	
	while(true){
		if(is_Solution()){
			plan->printPath();
			cout<<"statisctics-----------\n";
			cout<<"backtrack times: "<<numberOfBacktracks<<"\nnumberOfSteps: "<<plan->getSteps().size()-2<<"\n";



			/*cout<<endl<<endl;
			for(auto link:plan->getLinks()){
				cout<<string(*get<0>(link)->getParams())
				<<" "<<get<0>(link)->getId()<<endl<<string(*get<1>(link))<<endl<<string(*get<2>(link)->getParams())<<
				" "<<get<2>(link)->getId()<<endl;
			cout<<endl;
			}

			cout<<plan->getLinks().size()<<endl;*/
			numberOfBacktracks =0;
		
			
		
			return plan;
			}
		
		pair<Action*,Predicate*> toSolve = selectSubgoal(plan,0);
		
		
		Action* choosed = chooseStep(toSolve.first,toSolve.second,new IdsContainer());
		
		if(choosed == nullptr){
			choosed =chooseOperator(toSolve.first,toSolve.second,new IdsContainer());
		}
		
		if(choosed == nullptr){
			//backtrack
			cout<<"backtrack1\n";
			if(!backtracking()){
				cout<<"FAIL!\n";
				return nullptr;
			}
			continue;
		}
		pair<Action*,Predicate*> solver = chooseUnification(toSolve.first,toSolve.second,choosed,0);
		
		if(solver.first == nullptr || !plan->resolveAllThreats()|| !plan->checkConsistence(solver.first->getId() )){
			//backtrack
			cout<<"backtrack2\n";
			if(!backtracking()){
				cout<<"FAIL!\n";
				return nullptr;
			}
		}
		//cout<<endl<<"next iteraction\n\n";
	}

	
	return plan;
}


bool PlanningProblem::isConsistent(){
	bool result = true;
	for(Action* a : plan->getSteps()){
		result = result && plan->checkConsistence(a->getId());
	}
	return result;
}