/*
 * SplinesException.hpp
 *
 * \date 13 juin 2013, 11:04:40
 *  \author cec
 */

#ifndef SPLINESEXCEPTION_HPP_
#define SPLINESEXCEPTION_HPP_

#include "Exception.hpp"

class SplinesException : public Exception
{
    public:
        SplinesException(const char* s) :
                Exception(s)
        {
        }
};


#endif  /* SPLINESEXCEPTION_HPP_ */
