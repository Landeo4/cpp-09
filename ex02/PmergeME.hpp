#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>

template <typename T>
class Algo
{
    public:
    Algo();
    ~Algo();
    Algo&operator=(const Algo & copy);
    Algo(const Algo & copy);

    bool check_duplicate(char **argv, int argc);
    void Algo<T>::Swap();

    private:
    std::vector<double> vec;
    std::deque<double> deq;

}   ;

//insertion binarie 
//insertion dycotomique
// 4 1 2 3
// 41 23 -> faire des paires
// 14 23 -> mettre l eplus grand a droite
// Recursion => 4 3 -> prendre les plus grands
// (2)3 (1)4 -> prendre les petits pour les deplacer a droite
// 1 2 3 4

#endif