#ifndef ACTIONINSTANCIATOR_HPP
#define ACTIONINSTANCIATOR_HPP
#include "Action.hpp"
#include "PredicateInstanciator.hpp"

/**
 * class that represents an istanciable action
 */ 
class ActionInstanciator{
	public:
		ActionInstanciator(std::vector<PredicateInstanciator*> pre_condictions,std::vector<PredicateInstanciator*> result,PredicateInstanciator* params);

		~ActionInstanciator();

		std::vector<PredicateInstanciator*> getPre_Condiction();

    	std::vector<PredicateInstanciator*> getResult();

    	PredicateInstanciator* getParams();

    	/**
    	 * @brief intanciate action
    	 * @details using the bindings instanciate the action making the same indexes to have the same real index
    	 * 
    	 * @param binds the binds table from we will get the indexs
    	 * @return an Action based on this object
    	 */
		Action* instanciate(Bindings* binds);
	protected:
	private:
		/**
		 * precondictions list
		 */
		vector<PredicateInstanciator*> pre_condictions;
		/**
		 * post condictions list
		 */
    	vector<PredicateInstanciator*> result;
    	/**
    	 * params o action
    	 */
    	PredicateInstanciator* params;


};
#endif		