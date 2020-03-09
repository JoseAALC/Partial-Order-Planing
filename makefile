#AUTO GENERATED MAKEFILE

INCLUDES=./includes
CC=clang++ -std=c++14

all: Rule1 Rule2 Rule3 Rule4 Rule5 Rule6 Rule7 Rule8 Rule9 Rule10 Rule11 Rule12 Rule13 Rule14 Rule15 Rule16 Rule17 Rule18 Rule19 Rule20 Rule21 Rule22 Rule23 
	$(CC) -g  -I$(INCLUDES)   *.o$  -lgtest -lgtest_main -lpthread 

Rule1: ./tests/IdsContainerTest.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./tests/IdsContainerTest.cpp

Rule2: ./tests/StateTest.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./tests/StateTest.cpp

Rule3: ./tests/PlanningProblemTest.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./tests/PlanningProblemTest.cpp

Rule4: ./tests/ActionTest.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./tests/ActionTest.cpp

Rule5: ./tests/PredicateTest.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./tests/PredicateTest.cpp

Rule6: ./tests/BindingTest.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./tests/BindingTest.cpp

Rule7: ./src/Choice.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/Choice.cpp

Rule8: ./src/Heuristics.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/Heuristics.cpp

Rule9: ./src/IdsContainer.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/IdsContainer.cpp

Rule10: ./src/main.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/main.cpp

Rule11: ./src/PredicateInstanciator.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/PredicateInstanciator.cpp

Rule12: ./src/Parser.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/Parser.cpp

Rule13: ./src/PlanningProblem.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/PlanningProblem.cpp

Rule14: ./src/RecordManager.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/RecordManager.cpp

Rule15: ./src/ActionInstanciator.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/ActionInstanciator.cpp

Rule16: ./src/RecordFrame.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/RecordFrame.cpp

Rule17: ./src/StepHeuristic.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/StepHeuristic.cpp

Rule18: ./src/SubGoalpHeuristic.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/SubGoalpHeuristic.cpp

Rule19: ./src/Bindings.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/Bindings.cpp

Rule20: ./src/State.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/State.cpp

Rule21: ./src/Predicate.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/Predicate.cpp

Rule22: ./src/Action.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/Action.cpp

Rule23: ./src/OperatorHeuristic.cpp 
	 $(CC) -g -I$(INCLUDES)  -c ./src/OperatorHeuristic.cpp

clean:
	rm -f .*\.o