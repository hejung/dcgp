#ifndef DCGP_WRAPPED_FUNCTIONS_H
#define DCGP_WRAPPED_FUNCTIONS_H

#include <string>
#include <vector>
#include <audi/gdual.hpp>
#include <audi/functions.hpp>

namespace dcgp {

// SFINAE dust (to hide under the carpet)
template <typename T>
using f_enabler = typename std::enable_if<std::is_same<T,double>::value || std::is_same<T,audi::gdual>::value, int>::type;

// Allows to overload in templates std functions with audi functions
using namespace std;
using namespace audi;

/*--------------------------------------------------------------------------
*                                  BINARY FUNCTIONS
*------------------------------------------------------------------------**/
template <typename T, f_enabler<T> = 0>
T my_sum(const T &x, const T &y)
{
        return x + y;
}

std::string print_my_sum(const std::string& s1, const std::string& s2)
{
    if (s1 == s2) 
    {
        return "(2*"+s1+")";
    }
    else if (s1 == "0")
    {
        return s2;
    }
    else if (s2 == "0")
    {
        return s1;
    }
    return ("(" + s1 + "+" + s2 + ")");
}

template <typename T, f_enabler<T> = 0>
T my_diff(const T &x, const T &y)
{
        return x - y;
}

std::string print_my_diff(const std::string& s1, const std::string& s2)
{
    if (s1 == s2) 
    {
        return "0";
    }
    else if (s1 == "0")
    {
        return "(-" + s2 + ")";
    }
    else if (s2 == "0")
    {
        return s1;
    }
    return ("(" + s1 + "-" + s2 + ")");
}

template <typename T, f_enabler<T> = 0>
T my_mul(const T &x, const T &y)
{
        return (x * y);
}

std::string print_my_mul(const std::string& s1, const std::string& s2)
{
    if (s1 == "0" || s2 == "0")
    {
        return "0";
    }
    else if (s1 == s2)
    {
        return s1 + "^2";
    }
    else if (s1 == "1")
    {
        return s2;
    }
    else if (s2 == "1")
    {
        return s1;
    }
    return ("(" + s1 + "*" + s2 + ")");
}

template <typename T, f_enabler<T> = 0>
T my_div(const T &x, const T &y)
{
        return x / y;
}

std::string print_my_div(const std::string& s1, const std::string& s2)
{
    if (s1 == "0" && s2 != "0")
    {
        return "0";
    }
    else if (s1 == s2)
    {
        return "1";
    }
    else if (s2 == "1")
    {
        return s1;
    }
    return ("(" + s1 + "/" + s2 + ")");
}

template <typename T, f_enabler<T> = 0>
T my_pow(const T &x, const T &y)
{
        return pow(abs(x), y);
}

std::string print_my_pow(const std::string& s1, const std::string& s2)
{
    if (s1 == "0" && s2 != "0")
    {
        return "0";
    }
    else if (s1 == "1")
    {
        return "1";
    }
    else if (s2 == "0" && s1 != "0")
    {
        return "1";
    }
    else if (s2 == "1")
    {
        return s1;
    }
    return ("abs(" + s1 + ")^(" + s2 + ")");
}

// sigmoid function: 1 / (1 + exp(- a * b))
template <typename T, f_enabler<T> = 0>
T my_sig(const T &t, const T &beta)
{
        return 1 / (1 + exp(-beta * t));
}

std::string print_my_sig(const std::string& s1, const std::string& s2)
{
    if (s1 == "0" || s2 == "0")
    {
        return "0.5";
    }
    return "sig(" + s1 + "," + s2 + ")";
}

// square root
template <typename T, f_enabler<T> = 0>
T my_sqrt(const T &a, const T &b)
{
        return sqrt(abs(a + b));
}

std::string print_my_sqrt(const std::string& s1, const std::string& s2)
{
    if (s2 == "0" && s1 != "0")
    {
        return "sqrt(" + s1 + ")";
    }
    if (s1 == "0" && s2 != "0")
    {
        return "sqrt(" + s2 + ")";
    }
    if (s1 == "0" && s2 == "0")
    {
        return "0";
    }
    return "sqrt(" + s1 + " + " + s2 + ")";
}


/*--------------------------------------------------------------------------
*                                  UNARY FUNCTIONS
*------------------------------------------------------------------------**/

// sine of the first argument
template <typename T, f_enabler<T> = 0>
T my_sin(const T &a, const T &b)
{
    (void)b;
    return sin(a);
}

std::string print_my_sin(const std::string& s1, const std::string& s2)
{
    (void)s2;
    return "sin(" + s1 + ")";
}

// sine of the first argument
template <typename T, f_enabler<T> = 0>
T my_log(const T &a, const T &b)
{
    (void)b;
    return log(a);
}

std::string print_my_log(const std::string& s1, const std::string& s2)
{
    (void)s2;
    if (s1 == "1")
    {
        return "0";
    }
    return "log(" + s1 + ")";
}

} // dcgp namespace ends

#endif // DCGP_WRAPPED_FUNCTIONS_H