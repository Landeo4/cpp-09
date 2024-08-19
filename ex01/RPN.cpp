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
    char    *str = argv[1];
    int len, i = 0;
    while (str[i])
        i++;
    len = i;
    i = 0;
    while (i < len)
    {
        if (i == len)
            break;
        std::cout << str[i];
        char buf[2];
        buf[0] = str[i];
        buf[1] = str[i + 1];
        // std::cout << " et voici mon buf " << buf[1] << std::endl;
        if (buf[0] >= 48 && buf[0] <= 57)
        {
            int nb = atoi(buf);
            std::cout << " voici mon nb " << nb << std::endl;
            this->_st.push(nb);
        }
        i += 2;
    }
}

// idee pour le projet, mettre dans la structure le premier nombre
// prendre l'operateur, faire le calcul, stocker le nouveau nombre etc