/*
 * PhysicalQuantity.cpp
 *
 * \date 14 mars 2013, 08:49:49
 *  \author cec
 */



#include "PhysicalQuantity.hpp"
#include "Exception.hpp"

class PhysicalQuantityException : public Exception
{
    public:
        PhysicalQuantityException(const char* s) :
                Exception(s)
        {
        }
};

PhysicalQuantity::PhysicalQuantity() : val(std::vector<double>())
{}

PhysicalQuantity::~PhysicalQuantity()
{}


PhysicalQuantity::PhysicalQuantity(const std::vector<double>& v) : val(v)
{

}

void PhysicalQuantity::coerce(std::list<double>& ret) const
{
    for (std::vector<double>::const_iterator it = val.begin() ; it != val.end() ; ++it)
    {
        ret.push_back(*it);
    }
}

void PhysicalQuantity::decoerce(std::list<double>& ret)
{
    if (ret.size()<val.size())
    {
        THROW(__PRETTY_FUNCTION__, PhysicalQuantityException, "list should contain at least as many elements as val");
    }
    for (std::vector<double>::iterator it = val.begin() ; it != val.end() ; ++it)
    {
        *it = ret.front();
        ret.pop_front();
    }
}
