#include "gtest/gtest.h"
#include "Bindings.hpp"
#include <iostream>

class BindingsTest : public testing::Test{

	public:
		Bindings* bind; 



		virtual void SetUp(){
			bind = new Bindings();

		}

		virtual void TearDown(){
			delete(bind);

		}

};


TEST_F(BindingsTest,getNewBind){

	EXPECT_EQ(bind->getNewBind(),0);
	EXPECT_EQ(bind->getNewBind(),1);
	EXPECT_EQ(bind->getNewBind(),2);
	EXPECT_EQ(bind->getNewBind(),3);
	EXPECT_EQ(bind->getNewBind("Roon4"),4);
	EXPECT_EQ(bind->getNewBind("Roon2"),5);
	EXPECT_EQ(bind->getNewBind("Roon3"),6);

	

}

TEST_F(BindingsTest,isConstant){
	bind->getNewBind();
	bind->getNewBind("Roon2");

	EXPECT_TRUE(bind->isConst(1));
	EXPECT_FALSE(bind->isConst(0));
	EXPECT_FALSE(bind->isConst(0));
	bind->setReference(0,1);
	
	EXPECT_TRUE(bind->isConst(1));
	EXPECT_TRUE(bind->isConst(0));
}

TEST_F(BindingsTest,reference){
	bind->getNewBind();
	bind->getNewBind();
	bind->getNewBind();
	bind->getNewBind("Roon2");

	EXPECT_TRUE(bind->isConst(3));
	EXPECT_FALSE(bind->isConst(0));
	EXPECT_FALSE(bind->isConst(1));
	EXPECT_FALSE(bind->isConst(2));
	EXPECT_EQ(bind->getValue(3),"Roon2");
	
	bind->setReference(2,3);
	EXPECT_TRUE(bind->isConst(2));
	EXPECT_TRUE(bind->isConst(3));
	EXPECT_FALSE(bind->isConst(0));
	EXPECT_FALSE(bind->isConst(1));
	
	EXPECT_EQ(bind->getValue(3),"Roon2");
	EXPECT_EQ(bind->getValue(2),"Roon2");
	
	bind->setReference(1,2);
	EXPECT_TRUE(bind->isConst(1));
	EXPECT_TRUE(bind->isConst(2));
	EXPECT_TRUE(bind->isConst(3));
	EXPECT_FALSE(bind->isConst(0));
	EXPECT_EQ(bind->getValue(3),"Roon2");
	EXPECT_EQ(bind->getValue(2),"Roon2");
	EXPECT_EQ(bind->getValue(1),"Roon2");

	bind->setReference(0,3);
	EXPECT_TRUE(bind->isConst(1));
	EXPECT_TRUE(bind->isConst(2));
	EXPECT_TRUE(bind->isConst(3));
	EXPECT_TRUE(bind->isConst(0));
	EXPECT_EQ(bind->getValue(0),"Roon2");
	EXPECT_EQ(bind->getValue(1),"Roon2");
	EXPECT_EQ(bind->getValue(2),"Roon2");
	EXPECT_EQ(bind->getValue(3),"Roon2");


}

TEST_F(BindingsTest,copy){
	bind->getNewBind();
	bind->getNewBind();
	bind->getNewBind("Roon4");
	bind->getNewBind("Roon2");
	bind->setReference(1,3);

	Bindings* bind2	= bind->copy();
	EXPECT_EQ(bind2->getValue(0),"");
	EXPECT_EQ(bind2->getValue(1),"Roon2");
	EXPECT_EQ(bind2->getValue(2),"Roon4");
	EXPECT_EQ(bind2->getValue(3),"Roon2");
	
	bind->getNewBind("Roon3");
	bind2->getNewBind("Roon5");
	
	EXPECT_EQ(bind->getValue(4),"Roon3");
	EXPECT_EQ(bind2->getValue(4),"Roon5");

	bind->setReference(0,4);
	EXPECT_EQ(bind->getValue(0),"Roon3");
	EXPECT_EQ(bind2->getValue(0),"");



	delete(bind2);


}
