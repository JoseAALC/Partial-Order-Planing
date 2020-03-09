#ifndef COPIABLE_HPP
#define COPIABLE_HPP

template<class T>
class Copiable{
	public:
		/**
		* makes an copy of this object and returns it
		**/
		virtual T* copy() const=0;
	protected:
	private:


};
#endif