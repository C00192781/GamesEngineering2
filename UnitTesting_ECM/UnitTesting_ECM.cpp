// unitTestECM.cpp : Defines the entry point for the console application.
//

#include "gtest\gtest.h"
#include "AISystem.h"
#include "HealthComponent.h"

// For first for loop 
TEST(ECMtest, StartTest)
{
	// system
	AISystem* ai = new AISystem();
	EXPECT_EQ(true, ai->getStart());
}

// For second for loop 
// we know that the temporary vector holding component(s) has been created
TEST(ECMtest, StartTest2)
{
	// system
	AISystem* ai = new AISystem();
	EXPECT_EQ(true, ai->getStart2());
}



TEST(ECMtest, CheckVal1)
{
	// system
	AISystem* ai = new AISystem();

	// entity
	Entity* dog = new Entity();

	// component - health
	HealthComponent* dogHealth = new HealthComponent();

	dogHealth->setComponentID(4);

	dog->addComponent(dogHealth);

	EXPECT_EQ(false, ai->getCheck());
}


TEST(ECMtest, CheckVal2)
{
	// system
	AISystem* ai = new AISystem();

	// entity
	Entity* cat = new Entity();

	// component - health
	HealthComponent* catHealth = new HealthComponent();

	catHealth->setComponentID(5);

	cat->addComponent(catHealth);

	EXPECT_EQ(true, ai->getCheck());
}


TEST(ECMtest, EndTest)
{
	// system
	AISystem* ai = new AISystem();
	EXPECT_EQ(true, ai->getEnd());
}

TEST(ECMtest, EndTest2)
{
	// system
	AISystem* ai = new AISystem();
	EXPECT_EQ(true, ai->getEnd2());
}



