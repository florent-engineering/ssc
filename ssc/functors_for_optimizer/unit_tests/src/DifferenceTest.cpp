/*
 * DifferenceTest.cpp
 *
 * \date 1 f�vr. 2013, 09:20:24
 *  \author cec
 */

#include "DifferenceTest.hpp"
#include "Difference.hpp"
#include "StateGenerator.hpp"
#include "test_macros.hpp"

DifferenceTest::DifferenceTest() : a(DataGenerator(121212)), generate(StateGenerator())
{
}

DifferenceTest::~DifferenceTest()
{
}

void DifferenceTest::SetUp()
{
}

void DifferenceTest::TearDown()
{
}
#define X (**x)
#define Y (**y)

TEST_F(DifferenceTest, example)
{
//! [DifferenceTest example]
    const auto x = generate.state("x");
    const auto y = generate.state("y");
    const Difference d(x,y);
//! [DifferenceTest example]
//! [DifferenceTest expected output]
    const auto dv = d.get_value();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        Y = a.random<double>();
        ASSERT_DOUBLE_EQ(X-Y, dv());
    }
//! [DifferenceTest expected output]
}

TEST_F(DifferenceTest, derivative)
{
    const auto x = generate.state("x");
    const auto y = generate.state("y");
    const Difference d(x,y);
    const auto dx = d.diff(x)->get_value();
    const auto dy = d.diff(y)->get_value();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X = a.random<double>();
        Y = a.random<double>();
        ASSERT_DOUBLE_EQ(1, dx());
        ASSERT_DOUBLE_EQ(-1, dy());
    }
}

