#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <list>
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
    int check_char(std::string::iterator it);

    private:
    std::stack<double, std::list<double> >   _st;
    int _i;
    const char *_c;

};

#endif