#include "gtest/gtest.h"
#include "PlanningProblem.hpp"

class PlanningProblemTest : public testing::Test{
	
	public:
		PlanningProblem* p;
		virtual void SetUp(){
			p = new PlanningProblem(new Bindings());
		}

		virtual void TearDown(){
			delete(p);

		}

};

TEST_F(PlanningProblemTest,create){
	p->POP(new Heuristics());
	
}