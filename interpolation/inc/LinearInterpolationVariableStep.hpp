/*
 * LinearInterpolationVariableStep.hpp
 *
 * \date 10 avr. 2013, 12:54:12
 *  \author cec
 */

#ifndef LINEARINTERPOLATIONVARIABLESTEP_HPP_
#define LINEARINTERPOLATIONVARIABLESTEP_HPP_

#include <vector>
#include <tr1/memory>

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/LinearInterpolationVariableStepTest.cpp LinearInterpolationVariableStepTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/LinearInterpolationVariableStepTest.cpp LinearInterpolationVariableStepTest expected output
 */
class LinearInterpolationVariableStep
{
    public:
        LinearInterpolationVariableStep(const std::vector<double>& x, const std::vector<double>& y);
        double f() const;
        double df() const;
        double d2f() const;
        void set_computed_value(const double& x0);

    private:
        LinearInterpolationVariableStep();
        class LinearInterpolationVariableStepImpl;
        std::tr1::shared_ptr<LinearInterpolationVariableStepImpl> pimpl;
};

#endif /* LINEARINTERPOLATIONVARIABLESTEP_HPP_ */
