#ifndef RECORDMANAGER_HPP


#define RECORDMANAGER_HPP
#include "RecordFrame.hpp"

/**
 * class that manages the set of recordsFrames we have
 * 
 */
class RecordManager{
	public:
		RecordManager();
		/**
		 * @brief creates a new record
		 * @details a new record is created using the state , choice and bindings and put in the top of stack
		 * 
		 * @param state that origins the record
		 * @param choice that origins the record
		 * @param binds that origins the record
		 */
		void addRecord(State* state, Choice* choice,Bindings* binds);
		/**
		 * @brief removes an record
		 * @details record in the top of stack is removed
		 * @return the record removed
		 */
		RecordFrame* removeAndGetFrame();
		/**
		 * @brief looks on record on the top of stack
		 * @return record on the top of stack
		 */
		RecordFrame* top();
		/**
		 * @brief checks if stack is empty
		 * @return true if stack is empty ,false otherwise
		 */
		bool isEmpty();
		~RecordManager();
	protected:
	private:
		/**
		 * stack of records
		 */
		vector<RecordFrame*> frames;


};
#endif