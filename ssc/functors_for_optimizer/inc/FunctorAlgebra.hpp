/*
 * FunctorAlgebra.hpp
 *
 * \date 1 f�vr. 2013, 15:29:46
 *  \author cec
 */

#ifndef FUNCTORALGEBRA_HPP_
#define FUNCTORALGEBRA_HPP_

#include "tr1_macros.hpp"
#include TR1INC(memory)

#include "Exception.hpp"

class FunctorAlgebraException : public Exception
{
    public:
        FunctorAlgebraException(const char* s) :
                Exception(s)
        {
        }
};

class Node;
class Parameter;
class Difference;
class Sum;
class Divide;
class Multiply;
class State;
class Pow;
class Null;
class Constant;
typedef std::tr1::shared_ptr<Node> NodePtr;
typedef std::tr1::shared_ptr<Parameter> ParameterPtr;
typedef std::tr1::shared_ptr<Difference> DifferencePtr;
typedef std::tr1::shared_ptr<Sum> SumPtr;
typedef std::tr1::shared_ptr<Divide> DividePtr;
typedef std::tr1::shared_ptr<Multiply> Mult;
typedef std::tr1::shared_ptr<State> StatePtr;
typedef std::tr1::shared_ptr<Pow> PowPtr;
typedef std::tr1::shared_ptr<Null> NullPtr;
typedef std::tr1::shared_ptr<Constant> ConstantPtr;




Mult operator*(const Node& n1, const Node& n2);
Mult operator*(const Node& n1, const NodePtr& n2);
Mult operator*(const NodePtr& n1, const NodePtr& n2);
Mult operator*(const NodePtr& n1, const Node& n2);
NodePtr operator*(const NodePtr& n, const double& d);
NodePtr operator*(const double& d, const NodePtr& n);
NullPtr operator*(const NodePtr& n1, const Null& n2);
NullPtr operator*(const Null& n1, const NodePtr& n2);
NullPtr operator*(const Node& n1, const Null& n2);
NullPtr operator*(const Null& n1, const Node& n2);

NodePtr operator*(const Node& n1, const Constant& n2);
NodePtr operator*(const Constant& n1, const Node& n2);
NodePtr operator*(const NodePtr& n1, const Constant& n2);

/*
NodePtr operator*(const NodePtr& n1, const ConstantPtr& n2);
NodePtr operator*(const ConstantPtr& n1, const NodePtr& n2);
NodePtr operator*(const Constant& n1, const NodePtr& n2);
NodePtr operator*(const Node& n1, const ConstantPtr& n2);
NodePtr operator*(const ConstantPtr& n1, const Node& n2);
*/

SumPtr operator+(const Node& n1, const Node& n2);
SumPtr operator+(const Node& n1, const NodePtr& n2);
SumPtr operator+(const NodePtr& n1, const NodePtr& n2);
SumPtr operator+(const NodePtr& n1, const Node& n2);
NodePtr operator+(const NodePtr& n, const double& d);
NodePtr operator+(const double& d, const NodePtr& n);
NodePtr operator+(const NodePtr& n1, const Null& n2);
NodePtr operator+(const Null& n1, const NodePtr& n2);
NodePtr operator+(const Node& n1, const Null& n2);
NodePtr operator+(const Null& n1, const Node& n2);

NodePtr operator-(const double& d, const NodePtr& n);
NodePtr operator-(const NodePtr& n, const double& d);
NodePtr operator-(const NodePtr& n1, const NodePtr&n2);
NodePtr operator-(const NodePtr& n, const Parameter&p);

DividePtr operator/(const Node& n1, const Node& n2);
DividePtr operator/(const Node& n1, const NodePtr& n2);
DividePtr operator/(const NodePtr& n1, const NodePtr& n2);
DividePtr operator/(const NodePtr& n1, const Node& n2);
NodePtr operator/(const NodePtr& n, const double& d);
NodePtr operator/(const double& d, const NodePtr& n);
NullPtr operator/(const NodePtr& n1, const Null& n2);
NullPtr operator/(const Null& n1, const NodePtr& n2);
NullPtr operator/(const Node& n1, const Null& n2);
NullPtr operator/(const Null& n1, const Node& n2);
/*
NodePtr operator/(const NodePtr& n1, const Constant& n2);
NodePtr operator/(const Node& n1, const ConstantPtr& n2);
NodePtr operator/(const NodePtr& n1, const ConstantPtr& n2);
*/

PowPtr pow(const Node& n1, const double& d);
PowPtr pow(const NodePtr& n1, const double& d);
PowPtr pow(const Node& n1, const Node& n2);
PowPtr pow(const NodePtr& n1, const Node& n2);
PowPtr pow(const Node& n1, const NodePtr& n2);
PowPtr pow(const NodePtr& n1, const NodePtr& n2);
NullPtr pow(const Null& n1, const Node& n2);
NullPtr pow(const Null& n1, const NodePtr& n2);
NullPtr pow(const NullPtr& n1, const Node& n2);
NullPtr pow(const NullPtr& n1, const NodePtr& n2);

bool operator==(const NodePtr& n, const double& v);
bool operator==(const double& v, const NodePtr& n);
bool operator!=(const NodePtr& n, const double& v);
bool operator!=(const double& v, const NodePtr& n);


bool operator==(const NodePtr& n1, const NodePtr& n2);
bool operator!=(const NodePtr& n1, const NodePtr& n2);
bool operator==(const Node& n1, const Node& n2);
bool operator!=(const Node& n1, const Node& n2);
bool operator==(const NodePtr& n1, const double& n2);
bool operator!=(const Node& n1, const double& n2);
#endif /* FUNCTORALGEBRA_HPP_ */
