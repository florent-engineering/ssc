/*
 * SimplifyTest.cpp
 *
 * \date 13 f�vr. 2013, 08:57:25
 *  \author cec
 */

#include "SimplifyTest.hpp"
#include "Serialize.hpp"
#include "Constant.hpp"
#include "Null.hpp"
#include "Sum.hpp"
#include "FunctorAlgebra.hpp"

SimplifyTest::SimplifyTest() : a(DataGenerator(22)),
                               generate(StateGenerator()),
                               x1(generate.state("x1")),
                               x2(generate.state("x2"))
{
}

SimplifyTest::~SimplifyTest()
{
}

void SimplifyTest::SetUp()
{
}

void SimplifyTest::TearDown()
{
}

TEST_F(SimplifyTest, states_should_not_be_simplified)
{
    std::stringstream ss;
    Serialize v(ss);
    x1->simplify()->accept(v);
    ASSERT_EQ("x1", ss.str());
}

TEST_F(SimplifyTest, parameters_should_not_be_simplified)
{
    std::stringstream ss;
    std::stringstream ss_ref;
    Serialize v(ss);
    Parameter p(a.random<double>());
    *p = a.random<double>();
    ss_ref << *p;
    p.simplify()->accept(v);
    ASSERT_EQ(ss_ref.str(), ss.str());
}

TEST_F(SimplifyTest, constants_should_not_be_simplified)
{
    std::stringstream ss;
    std::stringstream ss_ref;
    Serialize v(ss);
    const double cst = a.random<double>();
    Constant c(cst);
    c.simplify()->accept(v);
    ss_ref << cst;
    ASSERT_EQ(ss_ref.str(), ss.str());
}

TEST_F(SimplifyTest, null_should_not_be_simplified)
{
    std::stringstream ss;
    Serialize v(ss);
    Null().simplify()->accept(v);
    ASSERT_EQ("0", ss.str());
}

TEST_F(SimplifyTest, simplify_sums)
{
    std::stringstream ss;
    Serialize v(ss);
    auto s = x1+x1+x2+x1;
    s->simplify()->accept(v);
    COUT(ss.str());
    ASSERT_TRUE((ss.str()=="x2 + 3*x1") || (ss.str()=="3*x1 + x2"));
}
