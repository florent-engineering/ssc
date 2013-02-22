/*
 * OptimizationProblemTest.cpp
 *
 * \date 21 f�vr. 2013, 10:15:03
 *  \author cec
 */

#include "OptimizationProblemTest.hpp"
#include "OptimizationProblem.hpp"
#include "GradHes.hpp"

#define X1 (**x1)
#define X2 (**x2)
#define X3 (**x3)
#define X4 (**x4)

OptimizationProblemTest::OptimizationProblemTest() : a(DataGenerator(1)),
                                                     generate(StateGenerator()),
                                                     x1(generate.state("x1")),
                                                     x2(generate.state("x2")),
                                                     x3(generate.state("x3")),
                                                     x4(generate.state("x4"))
{
}

OptimizationProblemTest::~OptimizationProblemTest()
{
}

void OptimizationProblemTest::SetUp()
{
}

void OptimizationProblemTest::TearDown()
{
}

TEST_F(OptimizationProblemTest, example)
{
//! [OptimizationProblemTest example]
    OptimizationProblem hs71;
//! [OptimizationProblemTest example]
//! [OptimizationProblemTest expected output]
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40);
//! [OptimizationProblemTest expected output]
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_list_of_states)
{
    OptimizationProblem problem;
    problem.minimize(x1*x4)
        .subject_to(25,x1*x3)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40);

    const StateList states = problem.get_states();

    ASSERT_EQ(4, states.size());
    ASSERT_EQ(*x1, *states.at(0));
    ASSERT_EQ(*x2, *states.at(1));
    ASSERT_EQ(*x3, *states.at(2));
    ASSERT_EQ(*x4, *states.at(3));
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_objective_function)
{
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3);
    const auto F = hs71.get_objective_function();
    const auto objective_function = F->get_lambda();
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X1 = a.random<double>();
        X2 = a.random<double>();
        X3 = a.random<double>();
        X4 = a.random<double>();
        ASSERT_DOUBLE_EQ(X1*X4*(X1+X2+X3)+X3, objective_function());
    }
}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraint_bounds)
{
    double g_l[2];
    double g_u[2];
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40);
    hs71.get_constraint_bounds(2, g_l, g_u);
    ASSERT_EQ(25, g_l[0]);
    ASSERT_EQ(40, g_l[1]);
    ASSERT_EQ(INFTY, g_u[0]);
    ASSERT_EQ(40, g_u[1]);
}

TEST_F(OptimizationProblemTest, method_to_retrieve_constraint_bounds_should_throw_if_any_pointers_are_null)
{
    double g_l[2];
    double g_u[2];
    OptimizationProblem pb;
    ASSERT_THROW(pb.get_constraint_bounds(2, NULL, g_u), OptimizationProblemException);
    ASSERT_THROW(pb.get_constraint_bounds(2, g_l, NULL), OptimizationProblemException);
    ASSERT_THROW(pb.get_constraint_bounds(2, NULL, NULL), OptimizationProblemException);
}

TEST_F(OptimizationProblemTest, should_be_able_to_set_and_retrieve_state_bounds_bug)
{
    OptimizationProblem pb;
    pb.bound_state(1,x1,2);
    pb.bound_state(3,x2,4);
    const size_t nb_of_states = 2;
    double x_l[nb_of_states];
    double x_u[nb_of_states];
    pb.get_state_bounds(nb_of_states,x_l,x_u);
    ASSERT_EQ(1, x_l[0]);
    ASSERT_EQ(2, x_u[0]);
    ASSERT_EQ(3, x_l[1]);
    ASSERT_EQ(4, x_u[1]);
}

TEST_F(OptimizationProblemTest, should_be_able_to_set_and_retrieve_state_bounds_bug_02)
{
    OptimizationProblem pb;
    pb.minimize(x1*x4*(x1+x2+x3)+x3).bound_state(1,x1,2);
    const size_t nb_of_states = 4;
    double x_l[nb_of_states];
    double x_u[nb_of_states];
    pb.get_state_bounds(nb_of_states,x_l,x_u);
    ASSERT_EQ(1, x_l[0]);
}

TEST_F(OptimizationProblemTest, should_be_able_to_set_and_retrieve_state_bounds)
{
    OptimizationProblem hs71;

    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .bound_state(1,x1,2)
        .bound_state(x2,3)
        .bound_state(4,x3)
        .bound_state(6,x4,7);

    double x_l[4];
    double x_u[4];
    hs71.get_state_bounds(4,x_l,x_u);
    ASSERT_EQ(1, x_l[0]);
    ASSERT_EQ(-INFTY, x_l[1]);
    ASSERT_EQ(4, x_l[2]);
    ASSERT_EQ(6, x_l[3]);
    ASSERT_EQ(2, x_u[0]);
    ASSERT_EQ(3, x_u[1]);
    ASSERT_EQ(INFTY, x_u[2]);
    ASSERT_EQ(7, x_u[3]);
}

TEST_F(OptimizationProblemTest, should_throw_if_attempting_to_retrieve_state_bounds_with_an_invalid_number_of_states)
{
    OptimizationProblem pb;
    pb.minimize(x1*x4*(x1+x2+x3)+x3);
    double x_l[4];
    double x_u[4];
    ASSERT_THROW(pb.get_state_bounds(a.random<size_t>().but_not(4),x_l,x_u), OptimizationProblemException);
    ASSERT_THROW(pb.get_state_bounds(4,NULL,x_u), OptimizationProblemException);
    ASSERT_THROW(pb.get_state_bounds(4,NULL,NULL), OptimizationProblemException);
    ASSERT_THROW(pb.get_state_bounds(4,x_l,NULL), OptimizationProblemException);
    ASSERT_NO_THROW(pb.get_state_bounds(4,x_l,x_u));
}

TEST_F(OptimizationProblemTest, should_throw_if_attempting_to_set_the_same_constraint_twice)
{
    OptimizationProblem problem;
    problem.subject_to(25,x1*x3);
    ASSERT_THROW(problem.subject_to(x1*x3,25), OptimizationProblemException);
}

TEST_F(OptimizationProblemTest, should_throw_if_attempting_to_set_the_same_state_bounds_twice)
{
    OptimizationProblem problem;
    problem.bound_state(1,x1,2);
    ASSERT_THROW(problem.bound_state(x1,2), OptimizationProblemException);
}

TEST_F(OptimizationProblemTest, different_ways_to_specify_constraint_bounds)
{
    OptimizationProblem problem;
    problem.minimize(x1*x4)
           .subject_to(25,x1*x3)
           .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
           .subject_to(x2*x3,50);
    double g_l[3];
    double g_u[3];
    problem.get_constraint_bounds(3, g_l, g_u);
    ASSERT_EQ(25, g_l[0]);
    ASSERT_EQ(40, g_l[1]);
    ASSERT_EQ(-INFTY, g_l[2]);
    ASSERT_EQ(INFTY, g_u[0]);
    ASSERT_EQ(40, g_u[1]);
    ASSERT_EQ(50, g_u[2]);
}
/*
TEST_F(OptimizationProblemTest, should_be_able_to_specify_constraints_bounds_with_parameters)
{

}


TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraints)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_gradient_of_objective_function)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_constraints_jacobian)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_hessian)
{

}

TEST_F(OptimizationProblemTest, should_be_able_to_retrieve_sigmaf_and_lambda_corresponding_to_hessian)
{

}
*/
