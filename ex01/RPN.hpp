#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <algorithm>

class RPN
{
    public:
    RPN();
    ~RPN();
    RPN&operator=(const RPN & cpy);
    RPN(const RPN & cpy);

    bool check_args(char **argv);
    void fill_struct(char **argv);
    bool check_char(std::string::iterator it);

    private:
    std::stack<int>   _st;

};

#endif