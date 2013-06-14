/*
 * Interpolator.hpp
 *
 * \date 12 juin 2013, 15:26:55
 *  \author cec
 */

#ifndef INTERPOLATOR_HPP_
#define INTERPOLATOR_HPP_

#include <vector>

/** \author cec
 *  \ingroup interpolation
 *  \brief Generic interface to interpolation classes
 *  \details 
 *  \section ex1 Example
 *  \snippet interpolation/unit_tests/src/InterpolatorTest.cpp InterpolatorTest example
 *  \section ex2 Expected output
 *  \snippet interpolation/unit_tests/src/InterpolatorTest.cpp InterpolatorTest expected output
 */

class Interpolator
{
    public:
        Interpolator();
        virtual ~Interpolator() {}
        Interpolator(const double& xmin_, const double& xmax_, const std::vector<double>& y);
        double f(const double x0);
        double df(const double x0, const size_t derivative_order=1);

    protected:
        virtual void update_coefficients_if_necessary(const double x0);
        virtual void find_index_of_interval_containing(const double val);
        virtual double get_f() const = 0;
        virtual double get_df(const size_t derivative_order) const = 0;

        double xmin;
        double xmax;
        std::vector<double> y;
        size_t n;
        double delta;
        size_t idx;
        double val_sat;

    private:
        virtual void compute_coefficients_for_ith_interval(const double x0, const size_t i) = 0;
        std::vector<bool> coefficients_have_been_computed_for_interval;
};

#endif /* INTERPOLATOR_HPP_ */
