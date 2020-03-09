#ifndef BINDINGS_HPP
#define BINDINGS_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include "Copiable.hpp"
using namespace std;
	

/**
 * class that represents an binding table
 */
class Bindings: public Copiable<Bindings> {
	public:
		Bindings();

		~Bindings();
		/**
		 * @brief copy the binding table
		 * @return an copy of this binding table
		 */
		Bindings* copy() const;
		/**
		 * @brief gets a new Binding
		 * @return an index to the new binding
		 */
		int getNewBind();
		/**
		 * @brief gets a new Binding to a constant so we save that index as constants
		 * @return an index to the new binding
		 */
		int getNewBind(string constant);
		/**
		 * @brief checks if it is a constant
		 * @details  recursive check if in the last index points to a constant
		 * 
		 * @param index that we want to check if is constant
		 * @return  true if is a constant false otherwise
		 */
		bool isConst(int index);
		/**
		 * @brief gets the constant value
		 * @details  recursive go to the last index points to a constant
		 * 
		 * @param index that we want get the value 
		 * @return  the constant value if is a constant , "" otherwise
		 */
		string getValue(int index);
		/**
		 * @brief makes an index point to another
		 * 
		 * @param index to point to reference
		 * @param reference  pointed index
		 */
		void setReference(int index,int reference);

		/**
		 * binds table
		 */
		vector<int> binds;


		friend ostream& operator<<(ostream& os, const Bindings& dt);  
	protected:
	private:
		/**
		 * constants container
		 */
		unordered_map<int,string> constants;


};
#endif