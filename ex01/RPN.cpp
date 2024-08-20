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
    _i = 0;
    while (it < str.end())
    {
        int check = check_char(it);
        if (check == 3)
        {
            std::cout << "Error, bad character in the list: " << *it << std::endl;
            return true;
        }
        else if (*it != ' ')
        {
            if (check == 1)
            {
                //mettre nb
                std::string tmp = str.substr(_i, str.length());
                _c = tmp.c_str();
                double nb = atoi(_c);
                _st.push(nb);
            }
            else if (check == 2)
            {
                int nb1 = _st.top();
                _st.pop();
                int nb2 = _st.top();
                _st.pop();
                if (*it == '+')
                     nb2 = nb2 + nb1;
                else if (*it == '-')
                    nb2 = nb2 - nb1;
                else if (*it == '/')
                {
                    if (nb2 == 0)
                        nb2 = nb1;
                    else if (nb1 == 0)
                        nb2 = nb2 + 0;
                    else
                        nb2 = nb2 / nb1;
                }
                else if (*it == '*')
                    nb2 = nb2 * nb1;
                _st.push(nb2);
            }
        }
        it++;
        _i++;
    }
    std::cout << _st.top() << std::endl;
    return false;
}

int RPN::check_char(std::string::iterator it)
{
    if (*it >= 48 && *it <= 57)
        return 1;
    else if (*it == '*' || *it == '+'
            || *it == '/' || *it == '-'
            || *it == ' ')
        return 2;
    return 3;
}
