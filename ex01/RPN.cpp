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

bool RPN::check_args(char **argv)
{
    std::string str = argv[1];
    std::string::iterator it = str.begin();
    while (it < str.end())
    {
        if (check_char(it) == 1)
        {
            std::cout << "Error, bad character in the list: " << *it << std::endl;
            return true;
        }
        std::cout << *it;
        it++;
    }
    std::cout << std::endl;
    return false;
}

bool RPN::check_char(std::string::iterator it)
{
    if (*it >= 48 && *it <= 57)
        return false;
    else if (*it == '*' || *it == '+'
            || *it == '/' || *it == '-'
            || *it == ' ')
        return false;
    return true;
}

void RPN::fill_struct(char **argv)
{
    std::string str = argv[1];
    for (size_t i = 0; i < str.length(); i++)
    {
        std::cout << str[i];
        std::string tmp = str[i];
        atoi(str[i]);
        // int nb = atoi(str[i]);
        // std::cout << "voici mon nb " << nb << std::endl;
        // this->_st.push(nb);
    }
}
