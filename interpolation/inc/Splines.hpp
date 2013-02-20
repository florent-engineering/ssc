/*
 * Splines.hpp
 *
 * \date 8 juin 2012, 17:14:15
 *  \author cec
 */

#ifndef SPLINES_HPP_
#define SPLINES_HPP_

#include <vector>
#include "Exception.hpp"
#include "ParabolicCoefficients.hpp"
#include <functional>

class SplinesException: public Exception {
public:
    SplinesException(const char* s) :
            Exception(s) {
    }
};

struct CubicCoefficients
{
    public:
        CubicCoefficients(const double& a_, const double& b_, const double& c_, const double& d_) : a(a_),b(b_),c(c_),d(d_){}
        double a;
        double b;
        double c;
        double d;

    private:
        CubicCoefficients();
};


/** \author cec
 *  \brief This class was created to interpolate data from tables.
 *  \details It has the following responsibilities:
 *  - Resp. 1: Store the x & y values from the table
 *  - Resp. 2: Compute the value of the interpolated data
 *  - Resp. 3: Compute the first derivative of the interpolated data
 *  - Resp. 4: Compute the second derivative of the interpolated data
 *  cf. Cubic Spline Interpolation by Sky McKinley and Megan Levine
 *  \section ex1 Example
 *  \snippet splines/unit_tests/src/SplinesTest.cpp SplinesTest example
 *  \section ex2 Expected output
 *  \snippet splines/unit_tests/src/SplinesTest.cpp SplinesTest expected output
 */
class Splines
{
	public:
		Splines();
		virtual ~Splines() {}
		Splines(const double& xmin_, const double& xmax_, const std::vector<double>& y);
		void set_computed_value(const double& x0);
		double f() const;
		double df() const;
		double d2f() const;
		std::vector<ParabolicCoefficients> get_parabolic_coefficients() const;

	protected:
		std::vector<double> compute_second_derivative() const;
		virtual double get_endpoint_value() const = 0;
		std::vector<double> M;
		double h;

	private:
		CubicCoefficients compute_cubic_coeff_for_x0(const double& x0, double& xxi) const;
		double get_x_intervals(const std::vector<double>& x) const;
		size_t compute_interval_index(const double& x) const;
		CubicCoefficients get_cubic_coefficients(const double& M1, const double& M2, const double& y1, const double& y2) const;

		double xmin;
		double xmax;
	protected:
		size_t n;
	private:
		std::vector<double> y_;
		double x_xi;
		double a;
		double b;
		double c;
		double d;
};

#endif /* SPLINES_HPP_ */