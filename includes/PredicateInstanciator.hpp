#ifndef PREDICATEINSTANCIATOR_HPP
#define PREDICATEINSTANCIATOR_HPP
#include "Predicate.hpp"
#include <unordered_map>

/**
 * class that represents an predicate to instanciate
 */
class PredicateInstanciator{
	public:
		PredicateInstanciator(string name,vector<int> vars,LogicSignal sign);
		PredicateInstanciator();
		~PredicateInstanciator();

		/**
		 * @brief intanciate the predicate
		 * @details  instanciate the predicate using the indexs to know which variables must be the same
		 * 
		 * @param converter maps each index to an real index on binds
		 * @param binds , binding table
		 * 
		 * @return an Predicate
		 */
		Predicate* instanciate(unordered_map<int,int>& converter,Bindings* binds);

		void setSign(LogicSignal sign);
		void setName( string name);
		void addVar(const int var);
		void addVar(const string var);

		bool operator==(const Predicate& other) const;
	protected:
	private:
		/* identifier of literal*/
		std::string name;
  		/*indexofparamvalue*/
		std::vector<int> vars;
		/* sign represents if literal is negated */
		LogicSignal sign;
		/*constants list*/
		vector<string> constants;

};
#endif