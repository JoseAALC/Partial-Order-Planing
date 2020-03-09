#ifndef RECORDFRAME_HPP
#define RECORDFRAME_HPP

#include "State.hpp"

#include "Choice.hpp"

/**
 * 
 * class that represents an record
 */
class RecordFrame{
	public:
		RecordFrame(State* state, Choice* choice,Bindings* binds);
		/**
		 * @return  the state of the record
		 */
		State* getState() const;
		/**
		 * @return  the binds of the record
		 */
		Bindings* getBinds() const;
		/**
		 * @return  the choice of the record
		 */
		Choice* getChoice() const;
		~RecordFrame();

		operator string() const;
	protected:
	private:
		State* state;
		Choice* choice;
		Bindings* binds;


};
#endif