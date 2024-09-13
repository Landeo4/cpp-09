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

void Algo::start_algo(size_t pair_ratio, std::vector<double> &vec)
{
    size_t actual_pair = pair_ratio - 1;
    std::cout << vec.size() << std::endl;
    std::cout  << "pair__ratio " << pair_ratio << std::endl;
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
    if (pair_ratio * 2 < vec.size())
        start_algo(pair_ratio * 2, vec);
    else
    {
        std::cout << "=====TRI FINALE=====" << std::endl;
        print_container(vec);
        return ;
    }
    tri_dicoto(pair_ratio, actual_pair, vec);
}

void Algo::tri_dicoto(size_t pair_ratio, size_t actual_pair, std::vector<double> &vec)
{
    std::vector<double> vec_buf;
    std::vector<double>::iterator vec_it = vec.begin();
    std::vector<double>::iterator buf_it;
    int pl_check = 2;
    int index = 0;
	size_t top;
    size_t nb;
    int size_buffer;
    (void)actual_pair;

    std::cout << "I === debut de tri_dicoto ===" << std::endl; 
    std::cout << "container au debut de tri_dicoto" << std::endl;
    print_container(vec);
    std::cout << "II et voici le pair_ratio " << pair_ratio << std::endl;
    while (vec_it < vec.end())
    {
        if (index == pl_check)
        {
			if (vec_it + pair_ratio < vec.end())
			{
				for(size_t i = 0; i < pair_ratio; i++)
				{
					std::cout << "valeur de vecteur " << *vec_it << std::endl;
					vec_buf.push_back(*vec_it);
					vec_it = vec.erase(vec_it);
				}
				// for(size_t i = 0; i < pair_ratio; i++)
				// {
				// 	// std::cout << vec[pl_check - i] << " " << vec[pl_check - i] << "| ";
				// 	// vec_it++;
				// }
				pl_check += 1;
			}
        }
        vec_it += pair_ratio;
        index++;
    } // ici je repere et je stock ou sont les nb a replacer
	if (vec_buf.size() < 1)
	{
		std::cout << " MON VECTEUR D'INSERTION N'A RIEN, JE SORS" << std::endl;
		return ;
	}
	buf_it = vec_buf.begin();
    buf_it += (pair_ratio) - 1;
    std::cout << "III je sors de tri_dicoto vecteur de base" << std::endl << std::endl;
    print_container(vec);
    std::cout << "avant l'insertion voici vec_buf " << std::endl;
    print_container(vec_buf);
	size_buffer = vec_buf.size();
    while (size_buffer > 0)
    {
		size_t cpt = 0, tmp = 0, bot = 0, ratio = 0, mid = 0;
    	top = vec.size();
		while (ratio < actual_pair)
			ratio += pair_ratio;
		mid = ratio / 2;
		nb = vec[mid];
        std::cout << *buf_it << std::endl;
		std::cout << "voici les parametre a remplir: " << (bot + pair_ratio) << " = " << top << std::endl;
        while (((bot + pair_ratio) != top))
        {
            std::cout << "JE DOIS DONC COMPARER buf: " << *buf_it << " nb " << nb << std::endl;
			std::cout << "voici d'ailleur bot + pair_ratio et top " << std::endl;
			std::cout << bot << " " << pair_ratio << " " << top << std::endl;
            if (*buf_it > nb)
            {
                bot = mid;
                tmp = bot;
                std::cout << "voici mon bot de base " << bot << std::endl;
                while (tmp < top)
                {
                    std::cout << "voici bot " << tmp << " voici top " << top << std::endl;
                    cpt++;
                    tmp += pair_ratio;
                }
				cpt = cpt / 2;
				bot = bot + (cpt * pair_ratio);
				nb = vec[bot];
            }
            else if (*buf_it < nb)
            {
                // trouver comment faire la version inferieur
				top = mid;
                tmp = top;
                std::cout << "voici mon top de base " << top << std::endl;
                while (tmp > bot)
                {
                    std::cout << "voici tmp " << tmp << " voici bot " << bot << std::endl;
                    cpt++;
                    tmp -= pair_ratio;
					if (bot == 0)
						bot++;
                }
				cpt = cpt / 2;
				top = top - (cpt * pair_ratio);
				nb = vec[top];
            }
            // pour le milieu finale il faut prendre son nombre pour augmenter par pair_ratio!!!
            // cpt = cpt / 2;
            // bot = bot + (cpt * pair_ratio);
            // nb = vec[bot];
            std::cout << "voici mon milieu final " << nb << std::endl;
            std::cout << "ma valeur a comparer " << *buf_it << " et ma liste" << std::endl;
            print_container(vec);
			usleep(1000000);
        }
        std::cout << "======= ATTENTION INSERTION D'UNE PAIR =======" << std::endl;
		vec_it = vec.begin();
		while (*vec_it != nb)
			vec_it++;
		vec_it ++;
		buf_it = vec_buf.begin();
        // push dans le vecteur de base avec une boucle for
        for(size_t i = 0; i < pair_ratio; i++)
        {
            std::cout << "valeur de vecteur " << *buf_it << std::endl;
			std::cout << "voici i " << i;
			std::cout << " pair_ratio " << pair_ratio << std::endl;
            // vec.push_back(*buf_it); // regler le problemne avec i et tout au dessus
			vec.insert(vec_it, 1, *buf_it);
			// std::swap(vec[bot + pair_ratio / 2], vec[len]);
            buf_it = vec_buf.erase(buf_it);
        }
		std::cout << "prochaine pair" << std::endl;
		print_container(vec);
		print_container(vec_buf);
		buf_it = vec_buf.begin();
        size_buffer -= pair_ratio;
    }
	std::cout << "voici mon vecteur a la fin de ma fonction: " << std::endl;
    print_container(vec);
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
