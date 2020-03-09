#ifndef STATE_HPP
#define STATE_HPP

#include "Action.hpp"
#include <utility>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


/**
 * class that saves an plan
 * 
 */
class State{
	public:
		State();
    State(vector<Action*>& steps,vector<tuple<Action*,Predicate*,Action*>> links,unordered_map<int,vector<int>> ordering);

		~State();
		
  	std::vector<Action*> getSteps();
    /**
     * @brief add an Action to list of steps
     * 
     * 
     * @param a  the action to add
     */
  	void addStep(Action* a);
  	void setLink(Action* a ,Predicate* c,Action* b);
    /**
     * @brief sets an order to action a and b
     * @details sets a before b
     * 
     * @param a an action
     * @param b an action
     */
  	void setOrder(Action* a,Action* b);
    /**
     * @brief prints a plan
     * 
     */
    void printPath();
    /**
     * @brief copies a state ans uses binds as list of binds for that state
     * 
     * 
     * @param binds  the list of binds
     * @return an copy of actual state
     */
    State* copy(Bindings* binds) const;
	
    bool checkConsistence(int start);


    Action* searchStep(int id) const;

    vector<tuple<Action*,Predicate*,Action*>> getLinks();

    bool resolveThreat(pair<Action*,Predicate*>& negative,tuple<Action*,Predicate*,Action*>& positive);
    bool resolveAllThreats();
    vector<pair<Action*,Predicate*>> getNegativePredicates();
    vector<tuple<Action*,Predicate*,Action*>> getPositivePredicates(pair<Action*,Predicate*>& negative);
    bool reachable(int index1,int index2);
    bool dfs(int index,int target);
    protected:
	private:
    /**
     * list of steps
     */
	vector<Action*> steps;

  	vector<tuple<Action*,Predicate*,Action*>> links;
    /**
     * hashmap to save the order
     */
    unordered_map<int,vector<int>> ordering;
    

};


#endif