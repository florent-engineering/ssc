/*
 * AngleTest.hpp
 *
 * \date 14 mars 2013, 10:45:36
 *  \author cec
 */

#ifndef ANGLETEST_HPP_
#define ANGLETEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class AngleTest : public ::testing::Test
{
    protected:
        AngleTest();
	    virtual ~AngleTest();
        virtual void SetUp();
        virtual void TearDown();
		DataGenerator a;

};

#endif  /* ANGLETEST_HPP_ */
