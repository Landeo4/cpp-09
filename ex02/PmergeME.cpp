#include "PmergeME.hpp"

Algo::Algo()
{

}

Algo::~Algo()
{

}

Algo &Algo::operator=(const Algo & copy)
{
    if (this != &copy)
        *this = copy;
    return *this;
}

Algo::Algo(const Algo & copy)
{
    *this = copy;
}

bool Algo::check_element_vector(char **argv, int argc)
{
    int i = 1;
    int j = 2;
    while (i < argc)
    {
        j = 1 + i;
        double nb = atof(argv[i]);
        while (argv[j])
        {
            if (nb == atof(argv[j]))
            {
                std::cout << "Error: two numbers are equal " << nb << " " << atof(argv[j]) << std::endl;
                return true;
            }
            else if (argv[j][0] == '-')
            {
                std::cout << "Error" << std::endl;
                return true;
            }
            else if (atof(argv[j]) > 2147483647)
            {
                std::cout << "Error: numbers are bigger than INT_MAX" << std::endl;
                return true;
            }
            // std::cout << argv[j] << std::endl;
            j++;
        }
        i++;
        _vec.push_back(nb);
    }
    print_container(_vec);
    return false;
}

void Algo::start_algo(size_t pair)
{
    // size_t tab[pair];
    size_t pair_buf = pair;
    std::cout << _vec.size() << std::endl;
    std::cout  << "voici mes donnees " << pair << " " << pair_buf << std::endl;
    while (pair_buf * 2 < _vec.size())
    {
        std::cout << "debut boucle: valeur pair buf et double " << _vec[pair_buf] << " " << _vec[pair_buf * 2] << " valeur de pauir_buf " << pair_buf << std::endl;
        if (pair == 0 && _vec[pair_buf] > _vec[pair_buf + 1])
        {
            std::swap(_vec[pair_buf], _vec[pair_buf + 1]);
            std::cout << "nouveau tab: ";
            print_container(_vec);
        }
        else if ((pair_buf == 0 && _vec[0] > _vec[1])
        ||  (_vec[pair_buf] > _vec[pair_buf * 2]))
        {
            std::swap(_vec[pair_buf], _vec[pair]);
            std::cout << "nouveau tab: ";
            print_container(_vec);
        }
        // std::cout << "voici mon pair " << pair_buf<< std::endl;
        // std::cout << "voici le nombre " << pair << " " <<  _vec[pair_buf] << " " << _vec[pair_buf * 2] << std::endl;
        if (pair_buf == 0)
            pair_buf = 2;
        else
            pair_buf *= 2;
    }
    std::cout << "============" << std::endl;
    if (pair * 2 == 0)
        start_algo(pair + 2);
    else if (pair * 2 < _vec.size())
        start_algo(pair * 2);
    else
    {
        std::cout << "je sors" << std::endl;
        print_container(_vec);
        return ;
    }
}
// donc je dois prendre la taille de ma pair
// donc ici je dois faire une recursive pour trier la premiere partis de l'algo
// donc je prend mes pairs (2 au debut) je compare les deux nb, je met le plus grand a gauche
// par la suite je double grace a ma recursive ma range (donc 4), je compare les deux plus grands
// des nouvelles pairs (donc les 4 premiers puis les 4 suivants). Ainsi de suite jusqu'a
// que mon double de pairs sois superieur a mon max

template<typename T>
void print_container(T vec)
{
    size_t i = 0;

    std::cout << "voici print cointainer: ";
    while (vec[i] != vec.back())
    {
        if (vec[i] == vec.back())
            break;
        std::cout << vec[i] << " ";
        i++;
    }
    std::cout << vec[i] << std::endl;
}

// template<typename T>
// void Algo::start_algo()
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
// void Algo::swap(double even)
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


//insertion binarie 
//insertion dycotomique
// 4 1 2 3 FAIT
// 41 23 -> faire des paires FAIT
// 14 23 -> mettre le plus grand a droite FAIT
// Recursion => 4 3 -> prendre les plus grands
// (2)3 (1)4 -> prendre les petits pour les deplacer a droite
// 1 2 3 4
