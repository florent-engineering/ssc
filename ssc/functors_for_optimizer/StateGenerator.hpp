#ifndef __STATE_GENERATOR_HPP__
#define __STATE_GENERATOR_HPP__

#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/exception_handling/Exception.hpp"
#include <set>

namespace ssc
{
    namespace functors_for_optimizer
    {
        class StateGeneratorException : public ssc::exception_handling::Exception
        {
            public:
                StateGeneratorException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                                                Exception(message, file, function, line){}
        };



        class StateGenerator
        {
            public:
                StateGenerator();
                StatePtr state(const std::string& name);
                ParameterPtr parameter(const double value);
                void reset();
                size_t total_number_of_states() const;
                size_t total_number_of_parameters() const;

            private:
                size_t current_state_index;
                std::set<std::string> state_names;
                size_t current_parameter_index;
        };
    }
}

#endif
