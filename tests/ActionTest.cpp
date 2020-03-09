#include "gtest/gtest.h"
#include "ActionInstanciator.hpp"

class ActionTest : public testing::Test{

	public:
		vector<ActionInstanciator*> actions;
		Bindings* binds;
		virtual void SetUp(){
			vector<PredicateInstanciator*> pre_cond;
			vector<PredicateInstanciator*> pos_cond;
			PredicateInstanciator* args = new PredicateInstanciator("Go",{1,2},LogicSignal::POSITIVE);

			pre_cond.push_back(new PredicateInstanciator("At",{1},LogicSignal::POSITIVE));
			pre_cond.push_back(new PredicateInstanciator("Door",{1,2},LogicSignal::POSITIVE));
			pos_cond.push_back(new PredicateInstanciator("At",{2},LogicSignal::POSITIVE));
			pos_cond.push_back(new PredicateInstanciator("At",{1},LogicSignal::NEGATIVE));
			actions.push_back(new ActionInstanciator(pre_cond,pos_cond,args));
			binds = new Bindings();
		}

		virtual void TearDown(){
			for (auto action: actions)
				delete(action);
			delete(binds);
		}

};


TEST_F(ActionTest,create){
	Action* go = actions[0]->instanciate(binds);

	EXPECT_EQ(string(*go->getPre_Condiction()[0]),"At(x0)");
	EXPECT_EQ(string(*go->getPre_Condiction()[1]),"Door(x0,x1)");

	EXPECT_EQ(string(*go->getParams()),"Go(x0,x1)");

	EXPECT_EQ(string(*go->getResult()[0]),"At(x1)");
	EXPECT_EQ(string(*go->getResult()[1]),"!At(x0)");

	cout<<string(*go)<<endl;



	delete(go);


}