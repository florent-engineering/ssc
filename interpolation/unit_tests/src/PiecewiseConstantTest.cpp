/*
 * PiecewiseConstantTest.cpp
 *
 * \date 18 f�vr. 2013, 12:59:23
 *  \author cec
 */

#include "PiecewiseConstantTest.hpp"
#include "PiecewiseConstant.hpp"

#include "test_macros.hpp"

#define min(a,b) (a)>(b)?b:a
#define max(a,b) (a)>(b)?a:b

PiecewiseConstantTest::PiecewiseConstantTest() : a(DataGenerator(22338888))
{
}

PiecewiseConstantTest::~PiecewiseConstantTest()
{
}

void PiecewiseConstantTest::SetUp()
{
}

void PiecewiseConstantTest::TearDown()
{
}

TEST_F(PiecewiseConstantTest, example)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
//! [PiecewiseConstantTest example]
    const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
    const std::vector<double> vals = a.random_vector_of<double>().of_size(n);
    const double xmin = a.random<double>();
    const double xmax = a.random<double>().greater_than(xmin);
    PiecewiseConstant cst(xmin, xmax, vals);
//! [PiecewiseConstantTest example]
//! [PiecewiseConstantTest expected output]
    const double val = a.random<double>().between(xmin,xmax);
    cst.set_computed_value(val);
//! [PiecewiseConstantTest expected output]
    }
}

TEST_F(PiecewiseConstantTest, should_throw_if_y_has_too_few_elements)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        const size_t n = a.random<size_t>().no().greater_than(1);
        ASSERT_THROW(PiecewiseConstant(xmin, xmax, a.random_vector_of<double>().of_size(n)), PiecewiseConstantException);
    }
}

TEST_F(PiecewiseConstantTest, should_throw_if_xmin_greater_than_xmax)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double xmax = a.random<double>();
        const double xmin = a.random<double>().greater_than(xmax);
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        ASSERT_THROW(PiecewiseConstant(xmin, xmax, a.random_vector_of<double>().of_size(n)), PiecewiseConstantException);
    }
}

TEST_F(PiecewiseConstantTest, should_not_throw_if_xmin_equals_xmax)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = xmin;
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        ASSERT_NO_THROW(PiecewiseConstant(xmin, xmax, a.random_vector_of<double>().of_size(n)));
    }
}


TEST_F(PiecewiseConstantTest, second_derivative_should_be_zero)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        const std::vector<double> vals = a.random_vector_of<double>().of_size(n);
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        PiecewiseConstant cst(xmin, xmax, vals);
        const double val = a.random<double>().between(xmin,xmax);
        cst.set_computed_value(val);
        ASSERT_EQ(0, cst.d2f());
    }
}

TEST_F(PiecewiseConstantTest, first_derivative_should_be_zero)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        const std::vector<double> vals = a.random_vector_of<double>().of_size(n);
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        PiecewiseConstant cst(xmin, xmax, vals);
        const double val = a.random<double>().between(xmin,xmax);
        cst.set_computed_value(val);
        ASSERT_EQ(0, cst.df());
    }
}

TEST_F(PiecewiseConstantTest, computed_values_should_be_correct)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        const std::vector<double> vals = a.random_vector_of<double>().of_size(n);
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        PiecewiseConstant cst(xmin, xmax, vals);
        const double val = a.random<double>().between(xmin,xmax);
        const size_t idx = max(0,min(floor((val-xmin)/(xmax-xmin)*(n-1)),n-2));
        cst.set_computed_value(val);
        ASSERT_DOUBLE_EQ(vals.at(idx), cst.f());
    }
}
