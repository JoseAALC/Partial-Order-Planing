#include "gtest/gtest.h"
#include "PredicateInstanciator.hpp"
#include "ActionInstanciator.hpp"
class PredicateTest : public testing::Test{


	public:
		
		Bindings* binds;
		PredicateInstanciator* pi;
		PredicateInstanciator* pi2;
		PredicateInstanciator* pi3;
		vector<Predicate*> p;
		Predicate* p1;
		Predicate* p2;
		Predicate* p3;
		Predicate* p4;
		Predicate* p5;
		Predicate* p6;
	
		
		virtual void SetUp(){
			binds = new Bindings();
			pi = new PredicateInstanciator("At",{1},LogicSignal::POSITIVE);
			pi2 = new PredicateInstanciator("At",{2},LogicSignal::POSITIVE);
			pi3 = new PredicateInstanciator("Go",{1,2},LogicSignal::POSITIVE);
			
			unordered_map<int,int> converter;

			p.push_back(pi->instanciate(converter,binds));
			p.push_back(pi->instanciate(converter,binds));
			p.push_back(pi2->instanciate(converter,binds));
			p.push_back(pi3->instanciate(converter,binds));

			p.push_back( new Predicate("At",{"Roon1"},LogicSignal::NEGATIVE,binds));
			p.push_back( new Predicate("At",{"Roon4"},LogicSignal::POSITIVE,binds));

			
		}

		virtual void TearDown(){
			for(auto pre:p)
				delete(pre);
			delete(binds);
			delete(pi);
			delete(pi2);
			delete(pi3);
		}	
};

TEST_F(PredicateTest,create){

	EXPECT_EQ(string(*p[0]),"At(x0)");
	EXPECT_EQ(string(*p[5]),"At(Roon4)");
	EXPECT_EQ(p[0]->getVars()[0],p[1]->getVars()[0]);
	EXPECT_EQ(p[4]->getVar(0),"Roon1");
	EXPECT_EQ(p[5]->getVar(0),"Roon4");

}


TEST_F(PredicateTest,isSameKind){
	EXPECT_TRUE(p[0]->isSameKind(*p[2]));
	EXPECT_TRUE(p[4]->isSameKind(*p[0]));
	EXPECT_TRUE(p[0]->isSameKind(*p[0]));

	EXPECT_FALSE(p[3]->isSameKind(*p[0]));
	EXPECT_FALSE(p[0]->isSameKind(*p[3]));
}

TEST_F(PredicateTest,equality){
	EXPECT_EQ(*p[0],*p[0]);
	EXPECT_FALSE(*p[0]==*p[1]);



}

TEST_F(PredicateTest,whatKind){
	EXPECT_NE(p[0]->whatKind(0),varKind::V_CONST);
	EXPECT_EQ(p[0]->whatKind(0),varKind::V_VAR);

	EXPECT_EQ(p[4]->whatKind(0),varKind::V_CONST);
	EXPECT_NE(p[4]->whatKind(0),varKind::V_VAR);


}


TEST_F(PredicateTest,copy){
	p.push_back(p[0]->copy());
	EXPECT_EQ(*p[6],*p[0]);
	EXPECT_NE(p[6],p[0]);
	EXPECT_EQ(p[6]->getSign(),p[0]->getSign());
	EXPECT_EQ(p[6]->getName(),p[0]->getName());
	for(int i=0;i<p[6]->getVars().size();i++)
		EXPECT_EQ(p[6]->getVar(i),p[0]->getVar(i));


	

}

TEST_F(PredicateTest,unify){

    EXPECT_TRUE(p[0]->unify(*p[5])); 
  	EXPECT_EQ(p[0]->getVar(0) ,p[5]->getVar(0) );
  	EXPECT_EQ(p[0]->getVar(0),"Roon4");
  	

  	EXPECT_EQ(p[0]->whatKind(0),varKind::V_CONST);
  	EXPECT_EQ(p[5]->whatKind(0),varKind::V_CONST);

  	EXPECT_FALSE(p[4]->unify(*p[5]));
  	EXPECT_EQ(p[0]->getVar(0) ,p[5]->getVar(0) );
  	EXPECT_EQ(p[0]->getVar(0),"Roon4");

  	p.push_back( new Predicate("Go",{string("Roon4"),"Roon3"},LogicSignal::POSITIVE,binds));

  	cout<<string(*p[6])<<endl;
  	EXPECT_TRUE(p[6]->unify(*p[3]));
  	EXPECT_EQ(p[6]->getVar(0) ,p[3]->getVar(0) );
  	EXPECT_EQ(p[6]->getVar(1) ,p[3]->getVar(1) );
  	EXPECT_EQ(p[6]->getVar(0),"Roon4");
  	EXPECT_EQ(p[6]->getVar(1),"Roon3");


}


TEST_F(PredicateTest,unifyAction){
	vector<PredicateInstanciator*> pre_cond;
	vector<PredicateInstanciator*> pos_cond;
	PredicateInstanciator* args = new PredicateInstanciator("Go",{1,2},LogicSignal::POSITIVE);

	pre_cond.push_back(new PredicateInstanciator("At",{1},LogicSignal::POSITIVE));
	pre_cond.push_back(new PredicateInstanciator("Door",{1,2},LogicSignal::POSITIVE));
	pos_cond.push_back(new PredicateInstanciator("At",{2},LogicSignal::POSITIVE));
	pos_cond.push_back(new PredicateInstanciator("At",{1},LogicSignal::NEGATIVE));

	ActionInstanciator* go = new ActionInstanciator(pre_cond,pos_cond,args);

	Action* goInstance = go->instanciate(binds); 

	
	p[5]->unify(*goInstance->getResult()[0]);
	
	p[4]->unify(*goInstance->getPre_Condiction()[0]);
	cout<<string(*goInstance)<<endl;

	delete(go);
	delete(goInstance);
}