#ifndef IDSCONTAINER_HPP
#define IDSCONTAINER_HPP
#include <vector>

using namespace std;


/**
 * @brief container to fast check if an id from 0 to size of the contained is marked
 * the space used by this container is int_size * (size/32)
 * 
 */
class IdsContainer{
	public:
		
		IdsContainer();
		

		/**
		 * @brief checks if an id is inside of the container O(1)
		 * 
		 * 
		 * @param id to check
		 * @return true if the id is in otherwise false
		 */
		bool isIn(int id);
		/**
		 * @brief marks an id as inside , best case O(1) ,worst O(n) if needs to rezise 
		 * 
		 * 
		 * 
		 */
		void setId(int id);
		/**
		 * @brief rezises the container until can put inside the maxid  
		 * 
		 * @param maxid 
		 */
		void resize(int maxid);
		/**
		 * @brief same as rezize but shrinks if the space is exceed
		 * 
		 * 
		 * @param maxid 
		 */
		void forceResize(int maxid);
		/**
		 * @brief gets te inside of container (debug purpose)
		 * @return an vector
		 */
		vector<int> getContainer();
		~IdsContainer();
	protected:
	private:
		vector<int> _32bitscontainer;


};
#endif