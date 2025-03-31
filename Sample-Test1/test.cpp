#include "gtest/gtest.h"
#include "Vector.h"
#include <limits>

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

	void ExpectAllDefaultValues()
	{
		EXPECT_EQ(vec[0], 30);
		EXPECT_EQ(vec[1], 10432042);
		EXPECT_EQ(vec[2], -4325325);
		EXPECT_EQ(vec[3], 0);
	}
};

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenShouldReturnValuesInPushBackOrder)
{
	ExpectAllDefaultValues();
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAccessOperatorIsCalled_ThenCapacityAndSizeShouldReturnFour)
{
	EXPECT_EQ(vec.Size(), 4);
	EXPECT_EQ(vec.Capacity(), 4);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenAnotherPushBackIsCalled_ThenCapacityShouldReturnEightAndSizeShouldReturnFive)
{
	vec.PushBack(1430254);
	EXPECT_EQ(vec.Size(), 5);
	EXPECT_EQ(vec.Capacity(), 8);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenReserveToTenIsCalled_ThenCapacityShouldReturnTenAndSizeShouldReturnFour)
{
	vec.Reserve(10);
	EXPECT_EQ(vec.Size(), 4);
	EXPECT_EQ(vec.Capacity(), 10);

	ExpectAllDefaultValues();
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenResizeToTenIsCalled_ThenCapacityAndSizeShouldReturnTen)
{
	vec.Resize(10);
	EXPECT_EQ(vec.Size(), 10);
	EXPECT_EQ(vec.Capacity(), 10);

	ExpectAllDefaultValues();
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenReserveToZeroIsCalled_ThenCapacityAndSizeShouldReturnTen)
{
	vec.Reserve(0);
	EXPECT_EQ(vec.Size(), 4);
	EXPECT_EQ(vec.Capacity(), 4);

	ExpectAllDefaultValues();
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenResizeToZeroIsCalled_ThenCapacityShouldReturn4AndSizeShouldReturnZero)
{
	vec.Resize(0);
	EXPECT_EQ(vec.Size(), 0);
	EXPECT_EQ(vec.Capacity(), 4);
}

TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenShrinkToFitIsCalledAfterResizingToZero_ThenCapacityAndSizeShouldReturnZero)
{
	vec.Resize(0);
	vec.ShrinkToFit();
	EXPECT_EQ(vec.Size(), 0);
	EXPECT_EQ(vec.Capacity(), 0);
}

//TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenReserveToNumberBiggerThanMaxVectorSizeIsCalled_ThenExceptionShouldBeThrown)
//{
//	EXPECT_THROW(vec.Reserve(std::numeric_limits<vectorSize>::max() + 10021), std::length_error);
//}
//
//TEST_F(VectorTest, GivenVectorWithFourValuesInsertedByPushBack_WhenResizeToNumberBiggerThanMaxVectorSizeIsCalled_ThenExceptionShouldBeThrown)
//{
//	EXPECT_THROW(vec.Resize(std::numeric_limits<vectorSize>::max() + 1), std::length_error);
//}