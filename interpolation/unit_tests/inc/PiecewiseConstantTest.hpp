/*
 * PiecewiseConstantTest.hpp
 *
 * \date 18 f�vr. 2013, 12:59:14
 *  \author cec
 */

#ifndef PIECEWISECONSTANTTEST_HPP_
#define PIECEWISECONSTANTTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class PiecewiseConstantTest : public ::testing::Test
{
    protected:
        PiecewiseConstantTest();
	    virtual ~PiecewiseConstantTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* PIECEWISECONSTANTTEST_HPP_ */
