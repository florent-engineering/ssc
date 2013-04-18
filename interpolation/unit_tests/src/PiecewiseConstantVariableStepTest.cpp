/*
 * PiecewiseConstantVariableStep.cpp
 *
 * \date 11 avr. 2013, 08:44:14
 *  \author cec
 */

#include "PiecewiseConstantVariableStepTest.hpp"
#include "PiecewiseConstantVariableStep.hpp"
#include "random_increasing_vector.hpp"

PiecewiseConstantVariableStepTest::PiecewiseConstantVariableStepTest() : a(DataGenerator(7631))
{
}

PiecewiseConstantVariableStepTest::~PiecewiseConstantVariableStepTest()
{
}

void PiecewiseConstantVariableStepTest::SetUp()
{
}

void PiecewiseConstantVariableStepTest::TearDown()
{
}

TEST_F(PiecewiseConstantVariableStepTest, example)
{
//! [PiecewiseConstantVariableStepTest example]
    const std::vector<double> x = {2,5,7,7.5,11,13};
    const std::vector<double> y = {2,2,5,4  ,8 ,7};
    PiecewiseConstantVariableStep<double> interpolate(x,y);
    interpolate.set_computed_value(7.5);
//! [PiecewiseConstantVariableStepTest example]
//! [PiecewiseConstantVariableStepTest expected output]
    ASSERT_DOUBLE_EQ(4, interpolate.f());
//! [PiecewiseConstantVariableStepTest expected output]
}


TEST_F(PiecewiseConstantVariableStepTest, should_be_able_to_retrieve_initial_values)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        PiecewiseConstantVariableStep<double> interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            interpolate.set_computed_value(x.at(i));
            ASSERT_DOUBLE_EQ(y.at(i), interpolate.f());
        }
    }
}

TEST_F(PiecewiseConstantVariableStepTest, should_throw_if_x_and_y_have_different_sizes)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const size_t different_n = a.random<size_t>().between(2,100).but_not(n);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(different_n);
        ASSERT_THROW(PiecewiseConstantVariableStep<double>(x,y), PiecewiseConstantVariableStepException);
    }
}

TEST_F(PiecewiseConstantVariableStepTest, should_throw_if_x_is_not_in_strictly_increasing_order)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        ASSERT_NO_THROW(PiecewiseConstantVariableStep<double>(x,y));
        const size_t idx = a.random<size_t>().between(1,n-1);
        x.at(idx) = x.at(idx-1);
        ASSERT_THROW(PiecewiseConstantVariableStep<double>(x,y), PiecewiseConstantVariableStepException);
        x.at(idx) = x.at(idx-1)-1;
        ASSERT_THROW(PiecewiseConstantVariableStep<double>(x,y), PiecewiseConstantVariableStepException);
    }
}

TEST_F(PiecewiseConstantVariableStepTest, should_throw_if_there_are_not_at_least_two_points)
{
    ASSERT_THROW(PiecewiseConstantVariableStep<double>(std::vector<double>(),std::vector<double>()), PiecewiseConstantVariableStepException);
    ASSERT_THROW(PiecewiseConstantVariableStep<double>(std::vector<double>(1,a.random<double>()),std::vector<double>(1,a.random<double>())), PiecewiseConstantVariableStepException);
}

TEST_F(PiecewiseConstantVariableStepTest, should_throw_if_querying_an_x_outside_bounds)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        PiecewiseConstantVariableStep<double> interpolate(x,y);
        ASSERT_THROW(interpolate.set_computed_value(a.random<double>().outside(x.front(),x.back())), PiecewiseConstantVariableStepException);
    }
}

