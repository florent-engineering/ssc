/*
 * LinearInterpolationVariableStepTest.hpp
 *
 * \date 10 avr. 2013, 12:52:45
 *  \author cec
 */

#ifndef LINEARINTERPOLATIONVARIABLESTEPTEST_HPP_
#define LINEARINTERPOLATIONVARIABLESTEPTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class LinearInterpolationVariableStepTest : public ::testing::Test
{
    protected:
        LinearInterpolationVariableStepTest();
	    virtual ~LinearInterpolationVariableStepTest();
        virtual void SetUp();
        virtual void TearDown();

		DataGenerator a;

};

#endif  /* LINEARINTERPOLATIONVARIABLESTEPTEST_HPP_ */