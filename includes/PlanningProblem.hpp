#ifndef PLANNINGPROBLEM_HPP
#define PLANNINGPROBLEM_HPP
#include "ActionInstanciator.hpp"
#include "State.hpp"
#include "RecordManager.hpp"
#include "Heuristics.hpp"

/**
 * class that represents the plan we wanna solve
 */
class PlanningProblem{
	public:
		PlanningProblem(Action* initial,Action* target,vector<ActionInstanciator*> operators,Bindings* binds);

		PlanningProblem(Bindings* binds);
		~PlanningProblem();

		//not check consistence
		bool is_Solution();

		/**
		 * @brief  search for a open precondiction
		 * @details  go to steps to find an precondiction no yet solved for another pos condiction
		 * 
		 * @param s  the plan
		 * @param iterator which index to start the search
		 * 
		 * @return  an pair <Step,Predicate> with the action to solve and the predicate to solve
		 */
		pair<Action*,Predicate*> selectSubgoal(State* s,int iterator);
		/**
		 * @brief choose an step to solve
		 * @details takes the open precondiction and tries to solve with an post condiction of an step already on plan
		 * 
		 * @param Sneed Action to solve
		 * @param c Predicate to solve
		 * @param iterator  where to start search
		 * @return  the step that solves the problem
		 */
		Action* chooseStep(Action* Sneed,Predicate* c,IdsContainer* ids);

		/**
		 * @brief choose an operator to solve
		 * @details takes the open precondiction and tries to solve with an new post condiction of an operator
		 * 
		 * @param c precondiction to solve
		 * @param iterator where to start the search
		 * 
		 * @return  the operator that solves the problem
		 */
		Action* chooseOperator(Action* Sneed,Predicate*c,IdsContainer* ids);
		
		/**
		 * @brief serach for the predicate that solved the problem on resolver
		 * 
		 * @param Sneed action to solve
		 * @param c  predicate to solve
		 * @param resolver action that resolves the problem
		 * @param iterator where to find
		 * @return the action and predicate that solves the problem
		 */
		pair<Action*,Predicate*> chooseUnification(Action* Sneed,Predicate* c,Action* resolver,int iterator);



		/**
		 * @brief the POP algorithm
		 * @return the plan solved
		 */
		State* POP(Heuristics* heuristics);


		bool backtracking();

		bool isConsistent();

	protected:
	private:	
		/**
		 * initial state
		 */		
		Action* initial;
		/**
		 * the final state
		 */
		Action* target;
		/**
		 * set of operators
		 */
		vector<ActionInstanciator*> operators;
		/**
		 * the plan
		 */
		State* plan;
		/**
		 * the binds
		 */
		Bindings* binds;
		/**
		 * the stack that saves the choices
		 */
		RecordManager recordmanager;


		Heuristics* heuristics;

};
#endif