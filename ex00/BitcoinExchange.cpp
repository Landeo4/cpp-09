#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::~BitcoinExchange()
{
    
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & copy)
{
    *this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange & copy)
{
    if (this != &copy)
        *this = copy;
    return *this;
}

bool BitcoinExchange::check_file(char **argv)
{
    std::ifstream file(argv[1]);
    std::string str;
    if (!file.is_open())
    {
        std::cout << "Error: could not open the file" << std::endl;
        return false;
    }
    getline(file, str, '\n');
    for (; file.eof() != 1;)
    {
        getline(file, str, '\n');
        if (verify_line(str) == 0)
        {
            fill_container(str);
        }
    }
    return true;
}

bool BitcoinExchange::verify_line(std::string str)
{
    char buf1[4];
    double tmp[4];
    str.copy(buf1, 4, 0);
    try
    {
        tmp[0] = atoi(buf1);
    }
    catch(const std::exception & e)
    {
        std::cout << "Error: bad input => " << tmp[0] << std::endl;
        return true;
    }
    for (int i = 0; buf1[i]; i++)
        buf1[i] = 0;
    str.copy(buf1, 2, 5);
    for (int i = 0; i < 2; i++)
    {
        try
        {
            tmp[i] = atoi(buf1);
            if (tmp[i] > 31 && i == 0)
            {
                std::cout << "Error: bad input => " << tmp[i] << std::endl;
                return true;
            }
            else if (tmp[i] < 0 && i == 0)
            {
                std::cout << "Error: not a positive number => " << tmp[i] << std::endl;
                return true;
            }
            else if (tmp[i] < 0 && i == 1)
            {
                std::cout << "Error: not a positive number => " << tmp[i] << std::endl;
                return true;
            }
            else if (tmp[i] > 12 && i == 1)
            {
                std::cout << "Error: bad input => " << tmp[i] << std::endl;
                return true;
            }
        }
        catch(const std::exception & e)
        {
            std::cout << "Error, wrong date" << std::endl;
            return true;
        }
        for (int i = 0; buf1[i]; i++)
            buf1[i] = 0;
        str.copy(buf1, 2, 8);
    }
    for (int i = 0; buf1[i]; i++)
        buf1[i] = 0;
    str.copy(buf1, 11, 13);
    try
    {
        tmp[3] = atof(buf1);
        if (tmp[3] > 1000)
        {
            std::cout << "Error: too large number => " << tmp[3] << std::endl;
            return true;
        }
        else if (tmp[3] < 0)
        {
            std::cout << "Error: not a positive number => " << tmp[3] << std::endl;
            return true;
        }
    }
    catch(const std::exception & e)
    {
        std::cout << "Error, wrong value" << std::endl;
        return true;
    }
    return false;
}

void BitcoinExchange::fill_container(std::string str)
{
    (void)str;
}
// fill le container avec les en string, les date puis en valeur double
// 2011-01-03 => 3 = 0.9
