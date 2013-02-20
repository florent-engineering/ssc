/*
 * LinearInterpolationTest.cpp
 *
 * \date 8 nov. 2012, 14:31:52
 *  \author cec
 */

#include "LinearInterpolationTest.hpp"
#include "test_macros.hpp"
#include "LinearInterpolation.hpp"

LinearInterpolationTest::LinearInterpolationTest() : a(DataGenerator(23))
{
}

LinearInterpolationTest::~LinearInterpolationTest()
{
}

void LinearInterpolationTest::SetUp()
{
}

void LinearInterpolationTest::TearDown()
{
}

TEST_F(LinearInterpolationTest, example)
{
//! [LinearInterpolationTest example]
    LinearInterpolation interpolate(0,10,{0,1,2,3,4,5,6,7,8,9,10});
//! [LinearInterpolationTest example]
//! [LinearInterpolationTest expected output]
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>().between(0,10);
        interpolate.set_computed_value(val);
        ASSERT_DOUBLE_EQ(val, interpolate.f());
    }
//! [LinearInterpolationTest expected output]
}

TEST_F(LinearInterpolationTest, f_should_work_properly)
{
    LinearInterpolation interpolate(0,10,{10,0});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>().between(0,10);
        interpolate.set_computed_value(val);
        ASSERT_DOUBLE_EQ(10-val, interpolate.f());
    }
}

TEST_F(LinearInterpolationTest, df_should_work_properly)
{
    LinearInterpolation interpolate(0,10,{10,0});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>().between(0,10);
        interpolate.set_computed_value(val);
        ASSERT_DOUBLE_EQ(-1, interpolate.df());
    }
}

TEST_F(LinearInterpolationTest, d2f_should_work_properly)
{
    const size_t n = a.random<size_t>().no().greater_than(30);
    LinearInterpolation interpolate(0,10,a.random_vector_of<double>().of_size(n));
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double val = a.random<double>();
        interpolate.set_computed_value(val);
        ASSERT_EQ(0, interpolate.d2f());
    }
}

TEST_F(LinearInterpolationTest, bug_detected_in_EONAV_PiecewiseLinearFunctor)
{
    LinearInterpolation pl(0, 10, {3,6,5,8,7,4,5,6,9,72,-56});
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(0,1));
        ASSERT_DOUBLE_EQ(3,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(1,2));
        ASSERT_DOUBLE_EQ(-1,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(2,3));
        ASSERT_DOUBLE_EQ(3,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(3,4));
        ASSERT_DOUBLE_EQ(-1,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(4,5));
        ASSERT_DOUBLE_EQ(-3,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(5,6));
        ASSERT_DOUBLE_EQ(1,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(6,7));
        ASSERT_DOUBLE_EQ(1,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(7,8));
        ASSERT_DOUBLE_EQ(3,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(8,9));
        ASSERT_DOUBLE_EQ(63,pl.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        pl.set_computed_value(a.random<double>().between(9,10));
        ASSERT_DOUBLE_EQ(-128,pl.df());
    }
}