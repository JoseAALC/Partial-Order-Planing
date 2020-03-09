#ifndef PREDICATE_HPP
#define PREDICATE_HPP

#include "Bindings.hpp"
#include "Copiable.hpp"
#include "unordered_map"
#include <vector>
#include <exception>
#include <stdexcept>


using namespace std;

/**
 * 
 * enum to the signal of predicate
 * 
 */
enum class LogicSignal: char
{ 
	NEGATIVE = '!',
	POSITIVE = '\0'
}; 

/**
 * 
 * enum that represent the type of paramter on a predicate
 */
enum varKind{V_VAR,V_CONST };

/**
 * class that represents an first order predicate
 */

class Predicate:public Copiable<Predicate>{
	public:

		Predicate(string name,int cardinality ,LogicSignal sign,Bindings* binds);
		Predicate(string name,vector<string> vars,LogicSignal sign,Bindings* binds);
		Predicate(string name,vector<int> vars,LogicSignal sign,Bindings* binds);

		~Predicate();


		/**
		 * @brief add a const variable to the predicate
		 * 
		 * @param var , the value of constant
		 */
		void addConst(string var);


		/**
		 * @brief creates a copy of the predicate
		 * 
		 * @return copy of the predicate
		 */
		Predicate* copy() const;

		/**
		 * @brief creates a copy of the predicate using binds
		 * 
		 * @param binds the binds table using on the copy	
		 * @return a copy of predicate
		 */
		Predicate* copy(Bindings* binds) const;


		/**
		 * @brief tests if two predicates are of same type
		 * @details two predicate will be of same type iff have same name and same number of vars
		 * 
		 * @param other , other predicate to compare
		 * @return true if they are sameKind, false otherwise
		 */
		bool isSameKind(const Predicate& other) const;
  		/**
  		 * @brief tests equality bettewen predicates
  		 * @details two predicates are equal iff they are of the same kind and have same vars
  		 * 
  		 * @param other ,  other predicate to compare
  		 * @return true if they are equal, false otherwise
  		 */
  		bool operator==(const Predicate& other) const;

  		/**
  		 * @brief getVars vector
  		 * 
  		 * @return return vars
  		 */
  		std::vector<int> getVars() const ;


  		LogicSignal getSign() const;


  		std::string getName() const;

  		/**
  		 * @brief get var value in binds database
  		 * 
  		 * 
  		 * @param index , the index in vars
  		 * @return  the string value on database
  		 */
  		std::string getVar(int index) const;
	  	/**
	  	* checks if an paramter is variable ( if is lower case)
	  	*
	  	**/
  		//kind what_kind(int index) const ;
  		varKind whatKind(int index) throw(logic_error);


  		operator string() const;

		/*set a vector of vars to vars*/
		void setVar(std::vector<int>& vars);
		/* set a var in position pos to var*/
		void setVar(int pos , int var);
		/* change the sign of predicate*/
		void setSign(LogicSignal sign); 

		int getId();
		/**
		 * @brief unifies that predicate with other
		 * 
		 * @param p other predicate
		 * @return true if the predicates can be unified ,false otherwise
		 */
	  	bool unify(Predicate& p) ;

	  	/**
	  	 * @brief makes the id generator return to 0
	  	 */
	  	static void resetIds();
	  
	  	/**
		 * table of binds
		 */
		Bindings* binds;
	protected:
	private:
		/**
		 * the id of preicate
		 */
		int id;
		/**
		 * flag if the predicate is binded
		 */
		bool binded;
		/**
		 * the id Giver responsible to give an different id to each different predicate
		 */
		static int  idGiver;
		/* identifier of literal*/
		std::string name;
  		/*indexofparamvalue*/
		std::vector<int> vars;
		/* sign represents if literal is negated */
		LogicSignal sign;
		




};
#endif	