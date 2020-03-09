#ifndef CHOICE_HPP
#define CHOICE_HPP
#include <tuple>
#include "Action.hpp"
#include "IdsContainer.hpp"
using namespace std;

/**
 * enum that represents the kind of choice we make were we save
 */
enum ChoiceKind {C_CREATE,C_ASSOCIATE,C_UNIFY};


/**
 * class that represents an choice maded in the plan
 */
class Choice{
	public:
		Choice(ChoiceKind kind,int iter,Predicate* Cneed,Action* Sneed,Action* resolver,IdsContainer*ids);
		~Choice();
		//return point
		//where ,iteraction what to solve
		tuple<ChoiceKind,int,Predicate*,Action*,Action*> getChoice();
		/**
		 * @brief get choice kind
		 * @return choice kind
		 */
		ChoiceKind getKind();


		IdsContainer* getIds();
	protected:
		
	private:
		/**
		 * the kind of the choice
		 */
		ChoiceKind kind;
		/**
		 * iteraction where the choice was maded
		 */
		int iteraction;
		/**
		 * predicate that was need to solve
		 */
		Predicate* Cneed;
		/**
		 * Action of predicate that was need to solve
		 */
		Action* Sneed;
		/**
		 * Action that was need to resolve
		 */
		Action* resolver;

		/**
		 * a container with the ids that already are used
		 */
		IdsContainer* ids;

};
#endif