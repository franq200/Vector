#include "gtest/gtest.h"
#include "Vector.h"

class VectorTest : public ::testing::Test
{
protected:
	Vector<int> vec;
	void SetUp() override
	{
		vec.PushBack(30);
		vec.PushBack(10432042);
		vec.PushBack(-4325325);
		vec.PushBack(0);
	}
};

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenShouldReturnValuesInPushBackOrder)
{
	EXPECT_EQ(vec[0], 30);
	EXPECT_EQ(vec[1], 10432042);
	EXPECT_EQ(vec[2], -4325325);
	EXPECT_EQ(vec[3], 0);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenCapacityAndSizeShouldReturnFour)
{
	EXPECT_EQ(vec.Size(), 4);
	EXPECT_EQ(vec.Capacity(), 4);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenCapacityShouldReturnEightAndSizeShouldReturnFive)
{
	vec.PushBack(1430254);
	EXPECT_EQ(vec.Size(), 5);
	EXPECT_EQ(vec.Capacity(), 8);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenCapacityShouldReturnTenAndSizeShouldReturnFour)
{
	vec.Reserve(10);
	EXPECT_EQ(vec.Size(), 4);
	EXPECT_EQ(vec.Capacity(), 10);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenCapacityAndSizeShouldReturnTen)
{
	vec.Resize(10);
	EXPECT_EQ(vec.Size(), 10);
	EXPECT_EQ(vec.Capacity(), 10);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenCapacityAndSizeShouldReturnTen)
{
	vec.Reserve(0);
	EXPECT_EQ(vec.Size(), 4);
	EXPECT_EQ(vec.Capacity(), 4);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenCapacityAndSizeShouldReturnTen)
{
	vec.Resize(0);
	EXPECT_EQ(vec.Size(), 10);
	EXPECT_EQ(vec.Capacity(), 10);
}