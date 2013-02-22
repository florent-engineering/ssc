/*
 * PiecewiseParabolicFunctor.cpp
 *
 * \date 19 f�vr. 2013, 14:44:08
 *  \author cec
 */

#include "PiecewiseParabolicFunctor.hpp"
#include "PiecewiseLinearFunctor.hpp"
#include "ParabolicInterpolation.hpp"
#include "State.hpp"
#include "NodeVisitor.hpp"

PiecewiseParabolicFunctor::PiecewiseParabolicFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<ParabolicCoefficients>& coeffs) :
Unary(state),
f(new ParabolicInterpolation(xmin,xmax,coeffs)),
xmin_(xmin),
xmax_(xmax),
dy(std::vector<double>())
{
    auto func = [f,state]()->double
        {
            f->set_computed_value(**state);
            return f->f();
        };
    set_value(func);
    const size_t n = coeffs.size();
    const double delta = (xmax-xmin)/n;
    for (size_t i = 0 ; i < n+1 ; ++i)
    {
        f->set_computed_value(xmin+i*delta);
        dy.push_back(f->df());
    }
}

NodePtr PiecewiseParabolicFunctor::diff(const StatePtr& state) const
{
    return NodePtr(new PiecewiseLinearFunctor(state, xmin_, xmax_, dy));
}

void PiecewiseParabolicFunctor::accept(NodeVisitor& v) const
{
    v.visit(*this);
}

NodePtr PiecewiseParabolicFunctor::clone() const
{
    return NodePtr(new PiecewiseParabolicFunctor(*this));
}

bool PiecewiseParabolicFunctor::is_null() const
{
    return false;
}


bool PiecewiseParabolicFunctor::equals_derived(const PiecewiseParabolicFunctor& rhs) const
{
    (void) rhs;
    return false;
}

std::string PiecewiseParabolicFunctor::get_type() const
{
    return "PiecewiseParabolic";
}

std::string PiecewiseParabolicFunctor::get_operator_name() const
{
    return "piecewise_parabolic";
}