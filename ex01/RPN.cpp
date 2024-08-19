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
                      nb2 = nb2 / nb1;
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

void RPN::fill_struct(char **argv)
{
    (void)argv;
    // std::cout << " " << _st.top() << std::endl;
    // std::string str = argv[1];
    // int i = 0;
    // int j = 0;
    // int len = str.length();
    // while (i < len)
    // {
    //     if (str[i] >= 48 && str[i] <= 57)
    //     {
    //         _st.top() = _nb[j];
    //         j++;
    //     }
    //     else if ((str[i] == '*' || str[i] == '+'
    //         || str[i] == '/' || str[i] == '-'
    //         || str[i] == ' ') && (i + 2 < len))
    //     {

    //         int nb1 = _st.top();
    //         _st.pop();
    //         int nb2 = _st.top();
    //         _st.pop();
    //         std::cout << "voici mes nb " << nb1 << " " << nb2 << std::endl;
    //     }
    //     std::cout << " voici mon nb dans la string " << str[i] << std::endl;
    //     i++;
    // }
}

// void RPN::fill_struct(char **argv)
// {
//     char    *str = argv[1];
//     int len, i = 0;
//     while (str[i])
//         i++;
//     len = i;
//     i = 2;
//     char buf[2];
//     buf[0] = str[0];
//     int nb = atoi(buf);
//     std::cout << " voici mon nb " << nb << std::endl;
//     this->_st.push(nb);
//     while (i < len)
//     {
//         if (i == len)
//             break;
//         std::cout << str[i];
//         buf[0] = str[i];
//         buf[1] = str[i + 1];
//         // std::cout << " et voici mon buf " << buf[1] << std::endl;
//         if (buf[0] >= 48 && buf[0] <= 57)
//         {
//             int nb = atoi(buf);
//             this->_st.pop();
//             this->_st.push(nb);
//             std::stack<double, std::list<double>>iterator it = _st.;
//             std::cout << " voici ce qu'il y a dans ma liste " << *it << std::endl;
//         }
//         i += 2;
//     }
// }

// idee pour le projet, mettre dans la structure le premier nombre
// prendre l'operateur, faire le calcul, stocker le nouveau nombre etc