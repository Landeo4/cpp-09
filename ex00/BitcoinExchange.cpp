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
        std::cout << "Failed to open file" << std::endl;
        return false;
    }
    getline(file, str, '\n');
    for (; file.eof() != 1;)
    {
        getline(file, str, '\n');
        std::cout << str << std::endl;
        verify_line(str);
    }
    return true;
}

bool BitcoinExchange::verify_line(std::string str)
{
    std::string buf = str;
    char *buf1 = NULL;
    int tmp[4];
    str.copy(buf1, 4, 0);
    try
    {
        tmp[0] = atoi(buf1);
    }
    catch(const std::exception & e)
    {
        std::cout << "Error, wrong date" << std::endl;
        return 1;
    }
    int i = buf.find('-');
    buf = buf.substr(i, str.length());
    std::cout << buf << std::endl;
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
