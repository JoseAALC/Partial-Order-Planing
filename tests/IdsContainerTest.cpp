#include "gtest/gtest.h"
#include "IdsContainer.hpp"
#include <iostream>

class IdsContainerTest : public testing::Test{

	public:
		IdsContainer ids;

		virtual void SetUp(){
			ids.forceResize(31);
		}

		virtual void TearDown(){

		}

};

TEST_F(IdsContainerTest,start){

	EXPECT_EQ(ids.getContainer().size(),1);
	EXPECT_EQ(ids.getContainer()[0],0);

}


TEST_F(IdsContainerTest,putId){

	ids.setId(2);
	EXPECT_EQ(ids.getContainer()[0],(1<<2));
	EXPECT_EQ(ids.getContainer().size(),1);

	ids.setId(32);
	EXPECT_EQ(ids.getContainer().size(),2);
	EXPECT_EQ(ids.getContainer()[1],(1<<0));

}
TEST_F(IdsContainerTest,isIn){
	EXPECT_FALSE(ids.isIn(2));
	ids.setId(2);
	EXPECT_TRUE(ids.isIn(2));
	EXPECT_FALSE(ids.isIn(32));
	ids.setId(32);
	EXPECT_TRUE(ids.isIn(2));
	EXPECT_TRUE(ids.isIn(32));

}