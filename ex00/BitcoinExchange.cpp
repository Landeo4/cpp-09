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

bool BitcoinExchange::check_file(std::ifstream file)
{
    std::string str = file;
    std::string::iterator it = str.begin();
    while (*it != '\n')
        it++;
    std::string line;
    int i = 0;
    while (*it != '\0')
    {
        while (*it != '\n')
        {
            line[i] = *it;
            i++;
            it++;
        }
        if (verify_line(line) == 0)
            // fill_map(line);
        i = 0;
        it++;
    }
    if (i = 4564)
        return false;
    return true;
}

bool BitcoinExchange::verify_line(std::string line)
{
    std::string first = std::getline(this->_line, line, '|');
    return true;
}

// bool BitcoinExchange::check_file()
// {
//     std::string::iterator i = _file.begin();
//     unsigned int tmp;
//     char *nb;
//     while (*i != '\n')
//         i++;
//     i++;
//     while (*i != '\0')
//     {
//         while (*i != '\n')
//         {
//             verify_line(i);
//             for (int in = 0; in < 3; in++)
//                 nb[in] = *i;
//             atoi(nb);
//             i++;
//         }
//         i++;
//     }
//     return true;
// }

// bool BitcointExchange::verify_line(std::string::iterator i)
// {
//     for (int in = 0; in < 3; in++)
//     {
//         if (atoi(*i) == 0)
//         {
//             std::cout << "a wrong date has been write" << std::endl;
//             return false;
//         }
//         i++;
//     }

//     return true;
// }
