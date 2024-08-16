#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
    public:
    RPN();
    ~RPN();
    RPN&operator=(const RPN & cpy);
    RPN(const RPN & cpy);

    void check_args(char **argv);
    void fill_struct();

    private:
    std::stack<int>   _st;

};

#endif