#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

template <typename T>
class Algo
{
    public:
    Algo();
    ~Algo();
    Algo&operator=(const Algo & copy);
    Algo(const Algo & copy);

    bool check_element_vector(char **argv, int argc);
    void print_container();
    void start_algo(size_t pair);
    void swap(size_t pair_buf, T vec);
    // void swap(double even);
    // void Algo<T>::Swap();

    private:
    std::vector<double> _vec;
    std::deque<double> _deq;

}   ;

//insertion binarie 
//insertion dycotomique
// 4 1 2 3
// 41 23 -> faire des paires
// 14 23 -> mettre l eplus grand a droite
// Recursion => 4 3 -> prendre les plus grands
// (2)3 (1)4 -> prendre les petits pour les deplacer a droite
// 1 2 3 4

template <typename T>
Algo<T>::Algo()
{

}

template <typename T>
Algo<T>::~Algo()
{

}

template <typename T>
Algo<T> &Algo<T>::operator=(const Algo<T> & copy)
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
    int cpt = 0;
    int i = cpt;
    while (cpt < argc - 1)
    {
        cpt++;
        i = cpt;
        double nb = atof(argv[i]);
        i++;
        while (argv[i])
        {
            if (nb == atof(argv[i]))
            {
                std::cout << "Error: two numbers are equal " << nb << " " << atof(argv[i]) << std::endl;
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
        _vec.push_back(nb);
    }
    return false;
}

template<typename T>
void Algo<T>::print_container()
{
    std::cout << "hello voici back " << _vec.back() << std::endl;
    size_t i = 0;
    while (i < _vec.back())
    {
        if (_vec[i] == _vec.back())
            break;
        std::cout << _vec[i] << " ";
        i++;
    }
    std::cout << _vec[i] << std::endl;
}

template<typename T>
void Algo<T>::start_algo(size_t pair)
{
    // size_t tab[pair];
    size_t pair_buf = pair;
    while (pair_buf * 2 < _vec.size())
    {

        if (_vec[pair_buf] > _vec[pair_buf * 2])
            swap(pair_buf, _vec);
        pair_buf *= 2;
    }

    if (pair * 2 < _vec.size())
        start_algo(pair * 2);
    else
        return ;
}
// donc je dois prendre la taille de ma pair

template<typename T>
void Algo<T>::swap(size_t pair_buf, T vec)
{
    T tmp;
    size_t i = 0;
    size_t j = 0;
    while (i < vec.size())
    {
        if (j == pair_buf)
        {
            tmp.push_back(vec[j + 1]);
            j++;
            i++;
            tmp.push_back(vec[j - 1]);
        }
        else
            tmp.push_back(vec[j]);
        i++;
        j++;
    }
    vec.swap(tmp);
    print_container();
}

// template<typename T>
// void Algo<T>::start_algo()
// {
//     size_t i = 0;
//     while (i < _vec.size())
//         i++;
//     std::cout << i << std::endl;
//     size_t j = 1;
//     double even = 0;
//     double odd = 1;
//     while (j < _vec.size())
//     {
//         if (_vec[odd] < _vec[even])
//             swap(even);
//         odd += 2;
//         even += 2;
//         j += 2;
//     }

// }// pour le systheme de pair, je pourrai utiliser % == 0 pour pair

// //faire une fonction swap
// template<typename T>
// void Algo<T>::swap(double even)
// {
//     std::vector<double> tmp;
//     size_t i = 0;
//     int j = 0;
//     while (i < _vec.size())
//     {
//         if (j == even)
//         {
//             tmp.push_back(_vec[j + 1]);
//             j++;
//             i++;
//             tmp.push_back(_vec[j - 1]);
//         }
//         else
//             tmp.push_back(_vec[j]);
//         i++;
//         j++;
//     }
//     _vec.swap(tmp);
//     print_container();
// }

#endif