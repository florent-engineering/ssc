/*
 * TrapezoidalIntegrationTest.cpp
 *
 * \date 23 avr. 2013, 14:46:33
 *  \author cec
 */

#include "TrapezoidalIntegrationTest.hpp"
#include "TrapezoidalIntegration.hpp"
#include "extra_test_assertions.hpp"

TrapezoidalIntegrationTest::TrapezoidalIntegrationTest() : a(DataGenerator(11))
{
}

TrapezoidalIntegrationTest::~TrapezoidalIntegrationTest()
{
}

void TrapezoidalIntegrationTest::SetUp()
{
}

void TrapezoidalIntegrationTest::TearDown()
{
}

#define EPS 1E-6
#define NINT 2000
TEST_F(TrapezoidalIntegrationTest, should_be_able_to_integrate_x)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
//! [TrapezoidalIntegrationTest example]
    TrapezoidalIntegration integrator([](const double& x){return x;});
    const double xa = a.random<double>().between(-100,100);
    const double xb = a.random<double>().between(xa,100);
//! [TrapezoidalIntegrationTest example]
//! [TrapezoidalIntegrationTest expected output]
    ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb,NINT), (xb*xb-xa*xa)/2., EPS);
//! [TrapezoidalIntegrationTest expected output]
    }
}

TEST_F(TrapezoidalIntegrationTest, should_be_able_to_integrate_a_constant)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double c = a.random<double>();
        TrapezoidalIntegration integrator([c](const double& x)->double{(void)x;return c;});
        const double xa = a.random<double>().between(-100,100);
        const double xb = a.random<double>().between(xa,100);
        ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb,NINT), (xb-xa)*c, EPS);
    }
}

TEST_F(TrapezoidalIntegrationTest, should_be_able_to_integrate_a_parabola)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double lambda = a.random<double>();
        const double mu = a.random<double>();
        TrapezoidalIntegration integrator([&lambda,&mu](const double& x)->double{return lambda*x*x+mu;});
        const double xa = a.random<double>().between(-100,100);
        const double xb = a.random<double>().between(xa,100);
        ASSERT_SMALL_RELATIVE_ERROR(integrator.integrate(xa,xb,NINT), lambda*(pow(xb,3)-pow(xa,3))/3.+mu*(xb-xa), EPS);
    }
}





