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

bool Algo::check_element_vector(char **argv, int argc, std::vector<double> vec)
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
        vec.push_back(nb);
    }
    print_container(vec);
    return false;
}

void Algo::start_algo(size_t pair_ratio, std::vector<double> vec)
{
    size_t actual_pair = pair_ratio - 1;
    std::cout << vec.size() << std::endl;
    // std::cout  << "voici mes donnees " << pair_ratio << " " << actual_pair << std::endl;
    while (actual_pair + pair_ratio < vec.size())
    {
        // std::cout << std::endl << "actual pair " << actual_pair << " " << actual_pair + pair_ratio << std::endl;
        // std::cout << vec[actual_pair] << " " << vec[actual_pair + pair_ratio]<< std::endl;
        // std::cout << "voici mon actual pair moins 1 et mon actual pair " << vec[actual_pair - 1] << " " << vec[actual_pair] << std::endl;
        if (vec[actual_pair] > vec[actual_pair + pair_ratio])
        {
            for(size_t i = 0; i < pair_ratio; i++)
            {
                // std::cout << " |voici mes switch " << vec[actual_pair - i] << " " << vec[actual_pair + pair_ratio - i] << "| ";
                std::swap(vec[actual_pair - i], vec[actual_pair + pair_ratio - i]);
            }
            // std::cout << "nouveau tab: ";
            // print_container(vec);
        }
        actual_pair += pair_ratio * 2;
    }
    // std::cout << "============ voici donc mon prochain ratio " << pair_ratio * 2 << "============" << std::endl;
    print_container(vec);
    if (pair_ratio * 2 < vec.size())
        start_algo(pair_ratio * 2, vec);
    else
        return ;
    tri_dicoto(pair_ratio, vec);
}

void Algo::tri_dicoto(size_t pair_ratio, std::vector<double> &vec)
{
    std::vector<double> vec_buf;
    std::vector<double>::iterator vec_it = vec.begin();
    std::vector<double, double>::iterator buf_it;
    int pl_check = 2;
    int index = 0;

    while (vec_it < vec.begin())
    {
        if (index == pl_check)
        {
            for(size_t i = 0; i < pair_ratio; i++)
            {
                vec_buf.push_back(*vec_it);
                vec_it++;
            }
            for(size_t i = 0; i < pair_ratio; i++)
            {
                // std::cout << " |voici mes switch " << vec[actual_pair - i] << " " << vec[actual_pair + pair_ratio - i] << "| ";
                std::swap(vec[actual_pair - i], vec[actual_pair + pair_ratio - i]);
                vec_it.pop();
                vec_it++;

            }
            pl_check += 2;
        }
        vec_it += pair_ratio;
    }

    size_t len = vec.size();
    size_t bot = vec[len];
    size_t top = 0;
    size_t pos, pos_top;
    pos = 0;
    pos_top = 0;
    if (len % 2 == 0)
        top = vec[len + pair_ratio / 2];
    else
        top = vec[len + pair_ratio / 2];
    size_t ac_pair = vec[len + pair_ratio];
    std::cout << "======= VOICI TRI_DICOTO =======" << std::endl;
    print_container(vec);
    std::cout << "len = " << len << " et voici pair_ratio " << pair_ratio;
    std::cout << " voici mon bot top " << bot << " " << top << std::endl;
    std::cout << "ac_pair " << ac_pair << std::endl;
    // std::cout << "===voici les comparaison dans le tri dicotomique ===" << std::endl;
    // std::cout << "ac_pair :" << ac_pair << " bot " << bot << " grand " << top << std::endl;
    // if (pair_ratio == 4)
    // {
    while (ac_pair < bot || ac_pair > top)
    {
        if (ac_pair > bot && ac_pair < top)
            break;
        if (ac_pair > bot)
        {
            bot = top;
            top = vec[top + pair_ratio];
        }
        else if (ac_pair < top)
        {
            top = bot;
            bot = vec[bot - pair_ratio];
        }
        usleep(100000);
        std::cout << "===voici les comparaison dans le tri dicotomique ===" << std::endl;
        std::cout << "pair_ratio " << pair_ratio << std::endl;
        std::cout << "ac_pair: " << ac_pair << " bot " << vec[bot] << " grand " << vec[top] << std::endl;
    }
    len = len * 2;
    while (pos < len - ac_pair)
        pos += ac_pair;
    while (vec[pos_top] != top)
        pos_top++;
    std::cout << "voici mon pos_top et bot " << pos_top << " " << bot << std::endl;
    // trouver une methode pour swap ma pair a droite, a sa dest
    // pour ca je dois avoir comme donnees:
    // ma position de pair a switch
    // Sa destination
    // les iterations por toutes la pairs
    // trouver une autre methode pour savoir quel pairs n'ont pas ete comparer
    // -> surement un rapport avec la suite de Jacob Sthall 1,3,5 etc
    // ajouter un systeme pour que toutes les trois paires je place ma pair dans un nouveau
    // tableau qui contiendra les pairs non triers
    for(size_t i = 0; i < pair_ratio / 2; i++)
    {
        std::cout << " pos_top " << pos_top << std::endl;
        std::cout << " |voici mes switch " << vec[pos - i] << " " << vec[pos_top - i] << "| " << std::endl;
        std::swap(vec[pos - i], vec[pos_top - i]);
    }
    std::cout << "fin de la boucle while " << std::endl;
    // }
    // faire le swap ici

    std::cout << "======= FIN TRI_DICOTO =======" << std::endl;
}

//a chaque recursion faire un tri dichotomique ->
// prendre au milieu et regarder si inf ou sup, faire ca jusqu'a plus possible

// probleme actuel, mon swap swap uniquement une valeur a la fois

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

// void Algo::start_algo(size_t pair)
// {
//     // size_t tab[pair];
//     size_t pair_buf = pair;
//     std::cout << _vec.size() << std::endl;
//     std::cout  << "voici mes donnees " << pair << " " << pair_buf << std::endl;
//     while (pair_buf * 2 < _vec.size())
//     {
//         std::cout << "debut boucle: valeur pair buf et double " << _vec[pair_buf] << " " << _vec[pair_buf * 2] << " valeur de pauir_buf " << pair_buf << std::endl;
//         if (pair == 0 && _vec[pair_buf] > _vec[pair_buf + 1])
//         {
//             std::swap(_vec[pair_buf], _vec[pair_buf + 1]);
//             std::cout << "nouveau tab: ";
//             print_container(_vec);
//         }
//         else if ((pair_buf == 0 && _vec[0] > _vec[1])
//         ||  (_vec[pair_buf] > _vec[pair_buf * 2]))
//         {
//             std::swap(_vec[pair_buf], _vec[pair]);
//             std::cout << "nouveau tab: ";
//             print_container(_vec);
//         }
//         // std::cout << "voici mon pair " << pair_buf<< std::endl;
//         // std::cout << "voici le nombre " << pair << " " <<  _vec[pair_buf] << " " << _vec[pair_buf * 2] << std::endl;
//         if (pair_buf == 0)
//             pair_buf = 2;
//         else
//             pair_buf *= 2;
//     }
//     std::cout << "============" << std::endl;
//     if (pair * 2 == 0)
//         start_algo(pair + 2);
//     else if (pair * 2 < _vec.size())
//         start_algo(pair * 2);
//     else
//     {
//         std::cout << "je sors" << std::endl;
//         print_container(_vec);
//         return ;
//     }
// }

/*
void Algo::start_algo(size_t pair_ratio)
{
    size_t actual_pair = pair_ratio;
    std::cout << _vec.size() << std::endl;
    std::cout  << "voici mes donnees " << pair_ratio << " " << actual_pair << std::endl;
    while (actual_pair + pair_ratio < _vec.size())
    {
        std::cout << "voici mon actual pair " << _vec[actual_pair] << " " << _vec[actual_pair * 2] << std::endl;
        if (_vec[actual_pair] < _vec[actual_pair + pair_ratio])
        {
            std::swap(_vec[actual_pair], _vec[actual_pair * 2]);
            std::cout << "nouveau tab: ";
            print_container(_vec);
        }
        actual_pair += pair_ratio;
    }
    std::cout << "============ voici donc mon prochain ratio " << pair_ratio * 2 << "============" << std::endl;
    if (pair_ratio * 2 < _vec.size())
        start_algo(pair_ratio * 2);
    else
    {
        std::cout << "je sors de ma recursion" << std::endl;
        print_container(_vec);
        return ;
    }
}
*/

//tri dicoto
/*
void Algo::tri_dicoto(size_t pair_ratio, std::vector<double> &vec)
{
    size_t len = vec.size();
    len /= 2 ;
    size_t bot = vec[len];
    size_t top = 0;
    size_t pos, pos_top;
    pos = 0;
    pos_top = 0;
    if (len % 2 == 0)
        top = vec[len + pair_ratio / 2];
    else
        top = vec[len + pair_ratio / 2];
    size_t ac_pair = vec[len + pair_ratio];
    std::cout << "======= VOICI TRI_DICOTO =======" << std::endl;
    print_container(vec);
    std::cout << "len = " << len << " et voici pair_ratio " << pair_ratio;
    std::cout << " voici mon bot top " << bot << " " << top << std::endl;
    std::cout << "ac_pair " << ac_pair << std::endl;
    // std::cout << "===voici les comparaison dans le tri dicotomique ===" << std::endl;
    // std::cout << "ac_pair :" << ac_pair << " bot " << bot << " grand " << top << std::endl;
    // if (pair_ratio == 4)
    // {
    while (ac_pair < bot || ac_pair > top)
    {
        if (ac_pair > bot && ac_pair < top)
            break;
        if (ac_pair > bot)
        {
            bot = top;
            top = vec[top + pair_ratio];
        }
        else if (ac_pair < top)
        {
            top = bot;
            bot = vec[bot - pair_ratio];
        }
        usleep(100000);
        std::cout << "===voici les comparaison dans le tri dicotomique ===" << std::endl;
        std::cout << "pair_ratio " << pair_ratio << std::endl;
        std::cout << "ac_pair: " << ac_pair << " bot " << vec[bot] << " grand " << vec[top] << std::endl;
    }
    len = len * 2;
    while (pos < len - ac_pair)
        pos += ac_pair;
    while (vec[pos_top] != top)
        pos_top++;
    std::cout << "voici mon pos_top et bot " << pos_top << " " << bot << std::endl;
    // trouver une methode pour swap ma pair a droite, a sa dest
    // pour ca je dois avoir comme donnees:
    // ma position de pair a switch
    // Sa destination
    // les iterations por toutes la pairs
    // trouver une autre methode pour savoir quel pairs n'ont pas ete comparer
    // -> surement un rapport avec la suite de Jacob Sthall 1,3,5 etc
    // ajouter un systeme pour que toutes les trois paires je place ma pair dans un nouveau
    // tableau qui contiendra les pairs non triers
    for(size_t i = 0; i < pair_ratio / 2; i++)
    {
        std::cout << " pos_top " << pos_top << std::endl;
        std::cout << " |voici mes switch " << vec[pos - i] << " " << vec[pos_top - i] << "| " << std::endl;
        std::swap(vec[pos - i], vec[pos_top - i]);
    }
    std::cout << "fin de la boucle while " << std::endl;
    // }
    // faire le swap ici

    std::cout << "======= FIN TRI_DICOTO =======" << std::endl;
}
*/

//insertion binarie 
//insertion dycotomique
// 4 1 2 3 FAIT
// 41 23 -> faire des paires FAIT
// 14 23 -> mettre le plus grand a droite FAIT
// Recursion => 4 3 -> prendre les plus grands
// (2)3 (1)4 -> prendre les petits pour les deplacer a droite
// 1 2 3 4
