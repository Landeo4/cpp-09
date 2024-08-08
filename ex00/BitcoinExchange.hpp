#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>

class BitcoinExchange
{
    public:
    ~BitcoinExchange();
    BitcoinExchange &operator=(const BitcoinExchange & copy);
    BitcoinExchange(const BitcoinExchange & copy);

    BitcoinExchange(char **argv);
    bool check_file(std::ifstream file);
    bool verify_line(std::string line);

    private:
    // std::ifstream _file;
    std::map<int, int> _ma;
    BitcoinExchange();

}   ;

#endif