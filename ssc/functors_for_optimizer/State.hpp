#ifndef STATES_HPP
#define STATES_HPP

#include "ssc/functors_for_optimizer/Parameter.hpp"
#include <string>

namespace ssc
{
    namespace functors_for_optimizer
    {
        class State : public Parameter
        {
            public:
              State(const std::string& name_, const size_t& index_);
              //State(const State& rhs);
              NodePtr diff(const StatePtr& state) const;
              std::string get_name() const;
              ~State();
              void accept(NodeVisitor& v) const;
              NodePtr clone() const;
              bool is_null() const;
              bool equals(const Node& rhs) const;
              using Parameter::equals_derived;
              bool equals_derived(const State& rhs) const;
              std::string get_type() const;
              void update_lambda();
              State& operator=(const double& a);


            private:
                State(); // Private & without implementation to disable the use of the default constructor
                std::string name;
        };

        typedef TR1(shared_ptr)<State> StatePtr;
    }
}

#endif
