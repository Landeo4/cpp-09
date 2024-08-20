#include "PmergeME.hpp"

template <typename T>
Algo<T>::Algo()
{

}

template <typename T>
Algo<T>::~Algo()
{

}

template <typename T>
Algo<T>&Algo::operator=(const Algo & copy)
{
    if (this != &copy)
        *this = copy;
    return *this;
}

template <typename T>
Algo<T>::Algo(const Algo & copy)
{
    *this = copy;
}

template <typename T>
bool Algo<T>::check_element_vector(char **argv, int argc)
{
    int cpt = 1;
    while (cpt < argc)
    {
        int i = 1;
        int nb = atoi(argv[1]);
        while (argv[i])
        {
            if (nb == atoi(argv[i]))
            {
                std::cout << "Error: two numbers are equal" << std::endl;
                return true;
            }
            else if (argv[i][0] == '-')
            {
                std::cout << "Error" << std::endl;
                return true;
            }
            else if (atof(argv[i]) > 2147483647)
            {
                std::cout << "Error: numbers are bigger than INT_MAX" << std::endl;
                return true;
            }
            i++;
        }
        cpt++;
    }
    return false;
}

template <typename T>
bool Algo<T>::check_duplicate(char **argv, int argc)
{
    int cpt = 1;
    while (cpt < argc)
    {
        int i = 1;
        int nb = atoi(argv[1]);
        while (argv[i])
        {
            if (nb == atoi(argv[i]))
            {
                std::cout << "Error: two numbers are equal" << std::endl;
                return true;
            }
            else if (argv[i][0] == '-')
            {
                std::cout << "Error" << std::endl;
                return true;
            }
            else if (atof(argv[i]) > 2147483647)
            {
                std::cout << "Error: numbers are bigger than INT_MAX" << std::endl;
                return true;
            }
            i++;
        }
        cpt++;
    }
    return false;
}

template <typename T>
void Algo<T>::Swap()
{
    T.swap()
}// en gros faire une fonction swap qui fonctionne avec les deux containers
