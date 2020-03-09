#include "Parser.hpp"

Parser::Parser(){
	
	
	
}
enum Phase{P_ACTION,P_FINAL,P_INIT,P_EMPTY};
enum Phase2{P2_EMPTY,P2_PREDICATE};
enum ActionPhase{P_START,P_PRE,P_POS};

PlanningProblem* Parser::parse(string file){
	Action::resetIds();
	Predicate::resetIds();
	Bindings* binds = new Bindings();
	vector<ActionInstanciator*> operators;
	vector<Predicate*> init;
	vector<Predicate*> fini;
	Phase phase  = P_EMPTY;
	Phase2 phase2 = P2_EMPTY;
	string name ="";

	ifstream fileStream(file);
	if(fileStream.is_open()){
		string line;
		while(getline(fileStream,line)){
			if(line == "---"){
					break;
				}
			else if(phase == P_EMPTY){
				if(line == "Final"){
					phase = P_FINAL;
				}
				else if(line == "Initial")
					phase = P_INIT;
				else if(line == "Action")
					phase = P_ACTION;
				else if(line == "")
					continue;
				else{

					cout<<"Invalid simbol: "+line+"\n";
					return nullptr;
				}
			}



			//Read the final state
			else if(phase == P_FINAL){
				if(phase2 == P2_EMPTY){
					if(line == ";"){
						phase = P_EMPTY;
						continue;
					}

					name = line;
					vector<string> vars;
					while(getline(fileStream,line) && line!=";"){
						if(line=="")
							continue;
						if(line == "---"){
							break;
					}
						vars.push_back(line);
					}
					fini.push_back(new Predicate(name,vars,LogicSignal::POSITIVE,binds));


				}

			}

			//Read the initial state
			else if(phase == P_INIT){
				if(phase2 == P2_EMPTY){
					if(line == ";"){
						phase = P_EMPTY;
						continue;
					}

					string name = line;
					vector<string> vars;
					while(getline(fileStream,line) && line!=";"){
						if(line=="")
							continue;
						if(line == "---"){
							break;
					}
						vars.push_back(line);
					}
					init.push_back(new Predicate(name,vars,LogicSignal::POSITIVE,binds));


				}

			}




			else if(phase == P_ACTION){
				ActionPhase phase3 = P_START;
				vector<PredicateInstanciator*> pre;
				vector<PredicateInstanciator*> pos;
				PredicateInstanciator* args;

				
				do{
					
					LogicSignal signal = LogicSignal::POSITIVE;
					if(line=="")
						continue;
					else if(line=="P" && phase3 == P_START){
						phase3 = P_PRE;
						continue;
					}
					else if(line=="R" && phase3 == P_PRE){
						phase3 = P_POS;
						continue;
					}
					else if(line=="---")
						break; 
				
					else{
						if(line=="!"){
							signal = LogicSignal::NEGATIVE;
							getline(fileStream,line);

							
						}
						string name = line;
						vector<int> vars;
						PredicateInstanciator* tmp = new PredicateInstanciator();
						
						while(getline(fileStream,line) && line!=";"){
							
							if(isdigit(line[0]))
								tmp->addVar(atoi(line.c_str()));
							else{
								tmp->addVar(line);

							}
							//vars.push_back(atoi(line.c_str()));


						}
						tmp->setName(name);
						tmp->setSign(signal);

						if(phase3 == P_START){
							args = tmp;
							tmp = nullptr;
							//args = new PredicateInstanciator(name,vars,signal);
							
						}
						else if(phase3 == P_PRE){
							//pre.push_back(new PredicateInstanciator(name,vars,signal));
							pre.push_back(tmp);
							tmp = nullptr;
						}

						else if(phase3 == P_POS){
							//pos.push_back(new PredicateInstanciator(name,vars,signal));
							pos.push_back(tmp);
							tmp = nullptr;	
						}


					}
				} while(getline(fileStream,line) && line!="E");
					phase  = P_EMPTY;
					phase2 = P2_EMPTY;
					operators.push_back(new ActionInstanciator(pre,pos,args));
					
				
			}

				
		}

	}
			
	else{
		cout<<"Fail to open file\n";
	}
	return new PlanningProblem(new Action(vector<Predicate*>(),init,new Predicate("Initial",{"initial"}	,LogicSignal::POSITIVE,binds))
		,new Action(fini,vector<Predicate*>(),new Predicate("Final",{"final"}	,LogicSignal::POSITIVE,binds)),
		operators,binds);
}




Parser::~Parser(){}

