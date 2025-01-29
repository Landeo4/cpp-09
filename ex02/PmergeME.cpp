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

//10 15 22 13 6 16 1 4 8 12 14 19 5 18 17 11 2 20 7 3 23 9 21

void Algo::start_algo(size_t pair_ratio, std::vector<double> &vec)
{
    size_t actual_pair = pair_ratio - 1;
    std::cout << vec.size() << std::endl;
    // std::cout << "NOUVELLE BOUCLE ";
    // std::cout  << "pair__ratio " << pair_ratio << std::endl << std::endl;
    // print_container_pair_size(vec, pair_ratio);
    while (actual_pair + pair_ratio < vec.size())
    {
        // std::cout << std::endl << "actual pair " << actual_pair << " " << actual_pair + pair_ratio << std::endl;
        // std::cout << vec[actual_pair] << " " << vec[actual_pair + pair_ratio]<< std::endl;
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
    unsort_list_creation(pair_ratio, vec);
    // tri_dicoto(pair_ratio, actual_pair, vec);
}

// faire la liste non trier avant 

void Algo::unsort_list_creation(size_t pair_ratio, std::vector<double> &vec)
{
    std::vector<double> vec_buf;
    size_t total;
    total = vec.size() / pair_ratio;
    size_t reach = 0; // la valeur a atteindre
    std::vector<double>::iterator vec_it = vec.begin();
    std::vector<double>::iterator buf_it;
    size_t pl_check = 2;

    while (reach < total)
    {
        if (reach == pl_check)
        {
            // std::cout << "reach et pl_check " << reach << " " << pl_check << std::endl;
            for(size_t i = 0; i < pair_ratio; i++)
            {
                // std::cout << "valeur de vecteur " << *vec_it << std::endl;
                vec_buf.push_back(*vec_it);
                vec_it = vec.erase(vec_it);
            }
            reach++;
            pl_check += 2;
        }
        vec_it += pair_ratio;
        reach++;
    }
    std::cout << "========== mes deux containers " << std::endl;
    print_container(vec);
    print_container(vec_buf);
    std::cout << "============= fin des deux containers " << std::endl;
    Jacobstal(pair_ratio, vec, vec_buf);
}

// cree une variable qui commence a trois avec un index sur Jacob
// faire boucler avec un - 1 au debut pour trier sur la variable donc 2 1 etc
// une fois que tu atteint 0 ou le nombre d'avant (par exemple 3) tu passe au prochain
// donc par exemple tu passe de 3 a 5

void Algo::Jacobstal(size_t pair_ratio, std::vector<double> &vec, std::vector<double> vec_buf)
{
    int jacob[] = {3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525};
    // unsigned int num = vec.size();
    int i = 0;
    int cur = jacob[i];
    int prec;
    int size = vec.size();
    std::cout << std::endl << "tour de Jacobstal : " << std::endl << std::endl;
    print_container(vec);
    print_container(vec_buf);
    // tri_dicoto(pair_ratio, vec, vec_buf);

    // creation liste trier et non trier, en dessous creation de Jacobstal
    // pour ca je dois trouver un moyen de savoir combien il me reste de nombre
    // a trier dans ma liste donc faire un index qui descend via la Jacobstal

    while (size > jacob[i])
    {
        while (cur > 0)
        {
            if (vec_buf.size() == 0)
                break;
            int nb_tri = vec_buf[cur]; // il faut juste que je trouve ou effacer ma 2 liste
            tri_dicoto(pair_ratio, vec, vec_buf, nb_tri);
            cur--;
        }
        i++;
        cur = jacob[i];
        prec = jacob[i - 1];
    }

}

// OU sinon j'isole le nombre qui doit trouver son endroit puis je le supprime ou
// le laisse dans la liste et je cherche son milieu, a l'issue de ca, je le deplace
// JE PENSE QUE C'EST CA
// ELi a confirmer la theorie

void Algo::tri_dicoto(size_t pair_ratio, std::vector<double> &vec, std::vector<double> vec_buf, int nb_tri)
{
    (void)nb_tri;
    // std::vector<double>::iterator vec_it = vec.begin();
    // std::vector<double>::iterator buf_it;

    // std::cout << "I === debut de tri_dicoto ===" << std::endl; 
    // std::cout << "container au debut de tri_dicoto" << std::endl;
    // print_container(vec);
    // std::cout << "II et voici le pair_ratio " << pair_ratio << std::endl;
    // std::cout << "voici size " << vec.size() << std::endl;
	// if (pair_ratio == 0)
		// std::cout << std::endl << " ===================== ATTENTION PAIR RATIO 1 ===================== " << std::endl;
    // std::cout << " Quel paire je dois allez " << total << std::endl;
    std::cout << "print de mes container debut ==== " << std::endl;
    // print_container(vec);
    // print_container(vec_buf);
    std::cout << std::endl << "fin du print de mes container ==== " << std::endl;
    // std::cout << "voici index " << index << " pl_check " << pl_check << std::endl;
	std::cout << "toutout " << vec_buf.size() << std::endl;
    if (vec_buf.size() < 1)
	{
		std::cout << " MON VECTEUR D'INSERTION N'A RIEN, JE SORS" << std::endl;
		return ;
	}
    std::cout << "ca continue" << std::endl;
    std::vector<double>::iterator vec_it = vec.begin();
    size_t nb = vec_buf[pair_ratio - 1];
    std::vector<double>::iterator mid;
    std::vector<double>::iterator top = vec.end();
    std::vector<double>::iterator bot = vec.begin();
    int pair_size = vec_buf.size();
    std::vector<double>::iterator buf_it = vec_buf.begin();
    nb = vec_buf[pair_ratio - 1];
    top = vec.end();
    while (is_pair_ratio(*top, pair_ratio, vec) == 0)
        top--;
    size_t i = 0;
    while (i < vec.size())
        i++;
    bot = vec.begin();
    while (*bot != nb_tri)
        bot++;
    std::cout << "voici nb " << nb_tri << " " << "bot = " << *bot << std::endl;
    while (42) // utilliser nb_tri
    {
        std::cout << std::endl << "=== DEBUT WHILE " << std::endl;
        print_container(vec);
        print_container(vec_buf);
        if (bot + pair_ratio > vec.end())
        {
            mid = top;
            break;
        }
        mid = find_middle(vec, top, pair_ratio, bot);
        std::cout << "voici bot " << *bot << " mid " << *mid << " tp " << *top << " nb " << nb << std::endl;
        if (std::distance(bot, top) <= (int)pair_ratio || top == bot)
            break;
        else if (*mid < nb)
            bot = mid;
        else if (*mid > nb)
        {
            if (mid - pair_ratio < vec.begin())
                top = mid;
            else
                top = mid - pair_ratio;
        }
        // std::cout << "quand meme pas ici ???" << std::endl;
        usleep(50000);
    }
    vec_it = vec.begin();
    if (nb > *mid)
    {
        std::cout << "je suis dans le if" << std::endl;
        if (mid < top)
        {
            while (vec_it < mid)
                vec_it++;
        }
        else
        {
            while (vec_it < top)
                vec_it++;
        }
        if (nb > *top)
        {
            while (vec_it < top)
                vec_it++;
        }
        // std::cout << "je passe par nb > *mid" << std::endl;
        if (*vec_it > nb)
            insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 0);
        else
            insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 1);
    }
    else
    {
        std::cout << "je suis dans le else" << std::endl;
        if ((bot == vec.begin() && nb < *(bot + pair_ratio - 1)) || (bot + pair_ratio == mid && nb > *bot && pair_ratio > 1))
        {
            while (vec_it < bot)
                vec_it++;
        }
        else if (nb > *bot && nb < *mid)
        {
            while (vec_it < mid)
                vec_it++;
        }
        if (*vec_it > nb || (bot == vec.begin() && nb < *(bot + pair_ratio - 1)))
            insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 0);
        else
            insert_list(pair_ratio, buf_it, vec_buf, vec, vec_it, 1);
    }
    std::cout << "ici" << std::endl;
    pair_size -= pair_ratio;
    if (pair_size > 0)
    {
        buf_it += pair_ratio;
        nb = *(buf_it + pair_ratio - 1);
    }
}

//3 5 24 10 14 17 18 19 7 2 20 13 9 1 22 21 4 25 23 8 15 6 16 11 12

std::vector<double>::iterator Algo::find_middle(std::vector<double> vec, std::vector<double>::iterator top, int pair_ratio, std::vector<double>::iterator bot)
{
    std::vector<double>::iterator mid;
    std::vector<double>::iterator tmp = vec.begin();
    if (top == bot)
        return top;
    size_t dist = std::distance(bot, top);
    tmp = bot + (dist / 2);
    // std::cout << "voici mon tmp " << *tmp << std::endl;
    while (is_pair_ratio(*tmp, pair_ratio, vec) == 0 && tmp > vec.begin())
        tmp++;
    // std::cout << "bot juste avant is_pair_ratio" << std::endl;
    // std::cout << "debut find_middle " << *bot << " ";
    if (is_pair_ratio(*bot, pair_ratio, vec) == 0)
        while (is_pair_ratio(*bot, pair_ratio, vec) == 0)
            bot++;
    // std::cout << "bot " << *bot << " ";
    while (bot < tmp)
        bot += pair_ratio;
    mid = bot;
    return mid;
}

void Algo::insert_list(size_t pair_ratio, std::vector<double>::iterator buf_it, std::vector<double> vec_buf, std::vector<double> &vec, std::vector<double>::iterator vec_it, int plus)
{
    (void)vec_buf;
	for(size_t i = 0; i < pair_ratio; i++)
	{
        // std::cout << *(vec_it + plus + i) << " 1 " << *buf_it << std::endl;
		vec.insert(vec_it + plus + i, 1, *buf_it);
        // std::cout << *(vec_it + plus + i) << " 1 " << *buf_it << std::endl;
        buf_it++;
	}
}

// modif la method pour trouver les pair_ratio

bool Algo::is_pair_ratio(size_t nb_it, int pair_ratio, std::vector<double> vec)
{
    size_t i;
    if (pair_ratio > 1)
        i = pair_ratio - 1;
    else
        i = pair_ratio;
    while ((i + pair_ratio) < vec.size())
    {
        // std::cout << "nb_it " << nb_it << " " ;
        if (nb_it == vec[i])
            return 1;
        // if (pair_ratio == 8)
            // std::cout << "voici mon vec[i] " << vec[i] << " ";
        i += pair_ratio;
    }
    if (nb_it == vec[i])
        return 1;
    // std::vector<double>::iterator tmp = vec.begin();
    // while (tmp + pair_ratio < vec.end())
    //     tmp += pair_ratio;
    // if (nb_it == *tmp)
    // {
    //     std::cout << "nb == pair ratio " << nb_it << " ";
    //     return 1;
    // }
    return 0;
}

template<typename T>
void print_container(T vec)
{
    size_t i = 0;
    std::cout << "voici print cointainer: ";
    if (vec.size() < 1)
    {
        std::cout << "il n'y a rien dans ce vecteur" << std::endl;
        return ;
    }
    while (vec[i] != vec.back())
    {
        if (vec[i] == vec.back())
            break;
        std::cout << vec[i] << " ";
        i++;
    }
    std::cout << vec[i] << std::endl;
}

template<typename T>
void print_container_pair_size(T vec, size_t pair_ratio)
{
    int i = 0;
    while (vec[i] != vec.back())
    {
        std::cout << "[";
        size_t j = 0;
        while (j < pair_ratio && vec[i] != vec.back())
        {
            if (vec[i] == vec.back())
                break;
            std::cout << " " << vec[i];
            j++;
            i++;
        }
        std::cout << " " << vec[i];
        if (vec[i] == vec.back())
            break;
        i++;
        std::cout << "] ";
    }
    std::cout << "] " << std::endl;
}
