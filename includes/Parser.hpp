#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <regex>
#include "PlanningProblem.hpp"

using namespace std;
enum Token{T_SEMC,T_NOT,T_RES,T_PRE,T_POINTS,T_ACTION,T_INIT,T_FIN,T_ID,T_LP,T_RP,T_COMA,T_AND,T_CONST,T_SPACE};
class Parser{
	public:
		Parser();
		PlanningProblem* parse(string file);
		~Parser();
	protected:
	private:

		



};
#endif