/*
 * VariableStepInterpolation.cpp
 *
 * \date 10 sept. 2013, 11:55:04
 *  \author cec
 */

#include "VariableStepInterpolation.hpp"
#include "IndexFinder.hpp"

VariableStepInterpolation::VariableStepInterpolation() : index(std::tr1::shared_ptr<IndexFinder>(new IndexFinder(std::vector<double>()))), idx(0), x0(0)
{

}

VariableStepInterpolation::~VariableStepInterpolation()
{
}

VariableStepInterpolation::VariableStepInterpolation(const std::vector<double>& x) : index(std::tr1::shared_ptr<IndexFinder>(new IndexFinder(x))), idx(0), x0(0)
{
}

void VariableStepInterpolation::update_coefficients_if_necessary(const double x0_)
{
    x0 = x0_;
    idx = index->compute(x0);
}
