#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN &RPN::operator=(const RPN & cpy)
{
    if (this != &cpy)
        *this = cpy;
    return *this;
}

RPN::RPN(const RPN & cpy)
{
    *this = cpy;
}

void RPN::check_args(char **argv)
{
    std::string str = argv[1];
    // if (str.length() > 9)
    // {
    //     std::cout << "too much "
    // }
    std::string::iterator it = str.begin();
    while (it < str.begin())
    {
        
    }
}

void RPN::fill_struct()
{

}
