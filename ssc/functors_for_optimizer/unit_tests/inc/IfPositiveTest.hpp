/*
 * IfPositiveTest.hpp
 *
 * \date Mar 3, 2016
 * \author cec
 */


#ifndef FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_ABSTEST_HPP_
#define FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_ABSTEST_HPP_

#include "gtest/gtest.h"
#include "ssc/random_data_generator/DataGenerator.hpp"
#include "ssc/functors_for_optimizer/StateGenerator.hpp"

class IfPositiveTest : public ::testing::Test
{
    protected:
        IfPositiveTest();
        virtual ~IfPositiveTest();
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
        ssc::functors_for_optimizer::StateGenerator generate;
};

#endif  /* FUNCTORS_FOR_OPTIMIZER_UNIT_TESTS_INC_ABSTEST_HPP_ */
