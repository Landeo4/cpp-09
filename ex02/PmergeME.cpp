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
    // print_container_pair_size(vec, pair_ratio);
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

// code du 17 septembre
/*
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
	std::cout << std::endl << std::endl;
    std::cout << "!!!debut de recherche du milieu: !!!" << std::endl << std::endl;
    print_container(vec);
    std::cout << "avant l'insertion voici vec_buf " << std::endl;
    print_container(vec_buf);
	size_buffer = vec_buf.size();
    while (size_buffer > 0)
    {
		size_t cpt = 0, tmp = 0, bot = 0, ratio = 0, mid = 0;
    	top = vec.size();
		while (ratio < actual_pair)
		{
			ratio += pair_ratio;
			tmp++;
		}
		mid = (tmp / 2);
		nb = vec[mid];
		std::cout << " AVANT DEBUT DE RECHERCHE VOICI DES INFOS IMPORTANTE: nb " << nb << " mid " << mid << std::endl; 
        std::cout << "voici ma size " << vec.size() << std::endl;
		std::cout << "voici mon ratio " << ratio << " et / 2 " << ratio / 2 << std::endl;
		std::cout << *buf_it << std::endl;
		std::cout << "voici les parametre a remplir: " << (bot + pair_ratio) << " = " << top << std::endl;
        std::cout << std::endl;
		std::cout << "=== voici la recherche de milieu" << std::endl;
		while (((bot + pair_ratio) != top))
        {
			std::cout << "[[[ Debut recherche milieu:" << std::endl << std::endl;
            std::cout << "--- JE DOIS DONC COMPARER buf: " << *buf_it << " nb " << nb << std::endl;
			std::cout << "voici d'ailleur bot + pair_ratio et top " << std::endl;
			std::cout << "voici aussi mon mid " << mid << std::endl;
			std::cout << bot << " " << pair_ratio << " " << top << std::endl;
            if (*buf_it > nb)
            {
				std::cout << "mid en entrant dans if = " << mid << std::endl;
                bot = mid;
                tmp = bot;
                std::cout << "voici mon bot de base " << bot << std::endl;
                while (tmp < top)
                {
                    std::cout << "voici temporaire " << tmp << " voici top " << top << std::endl;
                    cpt++;
                    tmp += pair_ratio;
                }
				cpt = cpt / 2;
				mid = bot + (cpt * pair_ratio);
				std::cout << "voici mid dans le if " << bot << std::endl;
				std::cout << "voic bot " << bot << std::endl;
				nb = vec[mid];
            }
            else if (*buf_it < nb)
            {
				std::cout << "mid en entrant dans if = " << mid << std::endl;
				top = mid;
                tmp = top;
                std::cout << "voici mon top de base " << top << std::endl;
                while (tmp > bot)
                {
                    std::cout << "voici temporaire " << tmp << " voici bot " << bot << std::endl;
                    cpt++;
                    tmp -= pair_ratio;
					if (bot == 0)
						bot++;
                }
				cpt = cpt / 2;
				mid = top - (cpt * pair_ratio);
				std::cout << "voici mid dans le if " << bot << std::endl;
				std::cout << "voic top " << top << std::endl;
				nb = vec[mid];
            }
            // pour le milieu finale il faut prendre son nombre pour augmenter par pair_ratio!!!
            // cpt = cpt / 2;
            // bot = bot + (cpt * pair_ratio);
            // nb = vec[bot];
			std::cout << "=== fin de ma recherche de milieu" << std::endl;
            std::cout << "--- voici mon milieu final " << nb << std::endl;
            std::cout << "ma valeur a comparer " << *buf_it << " et ma liste" << std::endl;
            print_container(vec);
			std::cout << "voici mes conditions de sortie de mon while " << bot + pair_ratio;
			std::cout << " top " << top << std::endl;
			usleep(1000000);
			std::cout << "fin recherche milieu]]]" << std::endl << std::endl;
        }
		std::cout << std::endl;
        std::cout << "======= ATTENTION INSERTION D'UNE PAIR =======" << std::endl;
		vec_it = vec.begin();
		std::cout << "VOICI LE NB TROUVER PAR MA COMPARAISON " << nb << std::endl;
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
			vec.insert(vec_it + i, 1, *buf_it);
			// std::swap(vec[bot + pair_ratio / 2], vec[len]);
            buf_it = vec_buf.erase(buf_it);
        }
		std::cout << "prochaine pair" << std::endl;
		print_container(vec);
		print_container(vec_buf);
		buf_it = vec_buf.begin() + pair_ratio;
        size_buffer -= pair_ratio;
    }
	std::cout << "voici mon vecteur a la fin de ma fonction: " << std::endl;
    print_container(vec);
}
*/

/*
void Algo::tri_dicoto(size_t pair_ratio, size_t actual_pair, std::vector<double> &vec)
{
    std::vector<double> vec_buf;
    std::vector<double>::iterator vec_it = vec.begin();
    std::vector<double>::iterator buf_it;
    int pl_check = 2;
    int index = 0;
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
                std::cout << "nouvel pair" << std::endl;
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
	size_t top = vec.size();
	size_t cpt = 0;
	size_t tmp = 0;
	while (tmp < top)
	{
		cpt++;
		tmp += pair_ratio;
	}
	size_buffer = cpt;
	size_t bot;
	size_t mid;
	size_t nb_pos;
    if (pair_ratio == 1)
    {
        std::cout << std::endl << "---------------- JE PASSE A LA DERNIERE PARTIS DE L'INSERTION, LES PAIRS INDIVIDUEL ----------------" << std::endl << std::endl; 
    }
	std::cout << std::endl << "DEBUT DE MON INSERTION" << std::endl;
    for (int i = 0; vec[i] != vec.back(); i++)
    {
        std::cout << "[";
        size_t j = 0;
        while (j < pair_ratio)
        {
            if (vec[i] == vec.back())
                break;
            usleep(10000);
            std::cout << " " << vec[i];
            j++;
            i++;
        }
        std::cout << "] ";
    }
    print_container(vec_buf);
	while (size_buffer > 0)
	{
		top = vec.size();
		top--;
        tmp = 0;
        cpt = 0;
        while (tmp < top)
        {
            cpt++;
            tmp += pair_ratio;
        }
        if (cpt == top)
            cpt /= 2;
        std::cout << "bon les putains de cpt et tmp ont ca comme valeur " << tmp << " " << cpt << std::endl;
        // cree une maniere de recup la milieu parfait 
        if (cpt % 2 == 0)
			mid = cpt - 1;
		else
			mid = cpt;
		bot = 0;
        if (pair_ratio == 1)
            nb_pos = 0;
        else
        {
            nb_pos = pair_ratio;
            nb_pos--;
        }
		// attention pour le mid, il faut que ca sois en pair_ratio
		while ((bot + pair_ratio) < top)
		{
            // if (vec_buf.size() > 0)
		        // print_container(vec_buf);
            // print_container(vec);
			std::cout << "[ DEBUT DE BOUCLE: ma condition est egale a " << (bot + pair_ratio) << std::endl;
			std::cout << "A l'entre du while voici mon top " << top << " bot " << bot << " mid " << mid << std::endl;
			std::cout << "nb_pos " << nb_pos << std::endl;
            std::cout << " et mon nb " << vec_buf[nb_pos] << std::endl;
            // std::cout << "Maintenant avec l<e contexte ca donne " << vec[top] << " bot " << vec[bot] << " mid " << vec[mid] << std::endl;
			std::cout << "top " << vec[top] << " size " << vec.size() <<  std::endl;
            tmp = 0;
			cpt = 0;
            std::cout << "voici les comparaison du if " << vec_buf[nb_pos] << " " << vec[mid] << std::endl;
			if (vec_buf[nb_pos] > vec[mid])
				bot = mid;
			else if (vec_buf[nb_pos] < vec[mid])
				top = mid;
            tmp = bot;
            while (tmp < top)
            {
                cpt += pair_ratio;
                tmp += pair_ratio;
            }
            cpt = cpt / 2;
            std::cout << "mid = bot " << bot << " + cpt " << cpt << " et cpt % 2 = " << cpt % 2 << std::endl;
            if (cpt % 2 == 0)
                mid = bot + cpt;
            else
                mid = bot + cpt + 1;
            if (mid % 2 == 0 && pair_ratio != 1)
                mid++;
            if (mid == top)
                mid = bot + pair_ratio;
			std::cout << "fin de boucle voici donc mid " << mid << " ]" << std::endl;
			usleep(100000);
		}
        // if (bot == mid)
            // bot -= pair_ratio;
        // pour cette condition faire attention a ce qu'elle ne pose pas probleme plus tard
        std::cout << std::endl << "!!! debut insertion des pairs" << std::endl << std::endl;
		std::cout << "FIN DE BOUCLE: ma condition est egale a " << (bot + pair_ratio) << std::endl;
		std::cout << "A la sortie du while voici mon top " << top << " bot " << bot << " mid " << mid << std::endl;
		std::cout << "Maintenant avec le contexte ca donne " << vec[top] << " bot " << vec[bot] << " mid " << vec[mid] << std::endl;
		vec_it = vec.begin();
        if (vec_buf.size() > 0)
		    print_container(vec_buf);
		if (vec_buf[nb_pos] < vec[mid] && mid == top)
            mid -= pair_ratio;
        for(int sac = mid; sac >= 0; sac--)
			vec_it++;
        std::cout << "voici vec_buf[pair_ratio] " << vec_buf[pair_ratio - 1] << " voici bot " << vec[bot] << std::endl;
        if (pair_ratio == 1)
            tmp = 0;
        else
            tmp = pair_ratio - 1;
        std::cout << " pos bot " << bot << " " << "valeur bot " << vec[bot];
        std::cout << " pos mid " << mid << " " << "valeur mid " << vec[mid];
        std::cout << " pos top " << top << " " << "valeur top " << vec[top];
        std::cout << " valeur nb_pos " << vec_buf[nb_pos] << std::endl;
        if (*vec_it < vec_buf[nb_pos] && vec_buf[nb_pos] > vec[top])
        {
            std::cout << "VEC_IT AUGMENTEEEE de 1" << std::endl;
            vec_it++;
        }
        if (*vec_it == vec[vec.size()])
            vec_it--;
        buf_it = vec_buf.begin();
		for(size_t i = 0; i < pair_ratio; i++)
        {
            std::cout << "valeur de vecteur " << *buf_it << std::endl;
			std::cout << "voici les differentes composante de l'insertion:" << std::endl;
			std::cout << *vec_it + i<< " 1 " << *buf_it << std::endl;
            // vec.push_back(*buf_it); // regler le problemne avec i et tout au dessus
			vec.insert(vec_it + i, 1, *buf_it);
			// std::swap(vec[bot + pair_ratio / 2], vec[len]);
            buf_it = vec_buf.erase(buf_it);
        }
        if (vec_buf.size() > 0)
		    print_container(vec_buf);
        std::cout << "et voici ma principale" << std::endl;
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
            if (vec[i] == vec.back())
                break;
            i++;
            std::cout << "] ";
        }
        std::cout << "] " << std::endl;
        size_buffer = vec_buf.size();
		// size_buffer -= pair_ratio;
        print_container(vec);
        std::cout << "voici size_buffer " << size_buffer << " et voici pair_ratio " << pair_ratio << std::endl;
		std::cout << "insertion finis" << std::endl << std::endl;
	}
	std::cout << "voici mon vecteur a la fin de ma fonction: " << std::endl;
    print_container(vec);
}

*/

void Algo::tri_dicoto(size_t pair_ratio, size_t actual_pair, std::vector<double> &vec)
{
    std::vector<double> vec_buf;
    std::vector<double>::iterator vec_it = vec.begin();
    std::vector<double>::iterator buf_it;
    size_t pl_check = 2;
    int index = 0;
    (void)actual_pair;

    std::cout << "I === debut de tri_dicoto ===" << std::endl; 
    std::cout << "container au debut de tri_dicoto" << std::endl;
    print_container(vec);
    std::cout << "II et voici le pair_ratio " << pair_ratio << std::endl;
    std::cout << "voici size " << vec.size() << std::endl;
    size_t total;
    total = vec.size() / pair_ratio;
    std::cout << "voici total " << total << std::endl;
    size_t calcul = total * pair_ratio;
    std::cout << "calcul " << calcul << std::endl;
    size_t reach = 0; // la valeur a atteindre
    if (vec.size() % 2 == 1)// impair
    {
        std::cout << "dans cherche pair je rentre dans impair " << std::endl;
        if (calcul + 1 >= vec.size())
        {
            while (reach < total)
            {
                if (reach == pl_check)
                {
                    for(size_t i = 0; i < pair_ratio; i++)
                    {
                        std::cout << "valeur de vecteur " << *vec_it << std::endl;
                        vec_buf.push_back(*vec_it);
                        vec_it = vec.erase(vec_it);
                    }
                    reach++;
                    pl_check += 2;
                }
                vec_it += pair_ratio;
                reach++;
            }
        }
    }
    else
    {
        std::cout << "dans cherche pair je rentre dans pair " << std::endl;
        if (calcul >= vec.size())
        {
            while (reach < total) // tant que je suis dans la chaine
            {
                // std::cout << "voici mes donnees de base: calcul " << calcul << " vec.size() " << vec.size();
                // std::cout << " reach: " << reach << " total " << total << " et pl_check " << pl_check <<std::endl;
                // std::cout << "je suis ici dans vec_it " << *vec_it << std::endl;
                if (reach == pl_check) // quand je suis sur un == alors je recup les valeurs
                {
                    for(size_t i = 0; i < pair_ratio; i++)
                    {
                        std::cout << "valeur de vecteur " << *vec_it << std::endl;
                        vec_buf.push_back(*vec_it);
                        vec_it = vec.erase(vec_it);
                    }
                    reach++;
                    pl_check += 2; // je passe a deux pair_size pour obtenir la prochaine valeur
                }
                vec_it += pair_ratio;
                reach++;
            }
        }
    }
    // usleep(500000);
    /*
    while (vec_it < vec.end())
    {
        if (index == pl_check)
        {
			if (vec_it + pair_ratio < vec.end())
			{
                std::cout << "nouvel pair" << std::endl;
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
    }// ici je repere et je stock ou sont les nb a replacer
    */
    // il me faut le dernier (5eme)
    std::cout << "voici index " << index << " pl_check " << pl_check << std::endl;
    print_container(vec);
    print_container(vec_buf);
    // std::cout << "la len " << vec.size() << std::endl;
	if (vec_buf.size() < 1)
	{
		std::cout << " MON VECTEUR D'INSERTION N'A RIEN, JE SORS" << std::endl;
		return ;
	}
    std::cout << std::endl << std::endl;
    if (pair_ratio == 1)
        std::cout << "===== MAINTENANT PAIR_RATIO == 1 =====" << std::endl << std::endl;
    // print_container(vec);
    // print_container(vec_buf);
    vec_it = vec.begin();
    size_t nb = vec_buf[pair_ratio - 1];
    std::cout << "voici nb " << nb << std::endl;
    std::vector<double>::iterator mid;
    std::vector<double>::iterator top = vec.end();
    std::vector<double>::iterator bot = vec.begin();
    int pair_size = vec_buf.size();
    while (pair_size > 0)
    {
        top = vec.end();
        top--;
        bot = vec.begin();
        buf_it = vec_buf.begin() + pair_ratio;
        nb = vec_buf[pair_ratio - 1];
        while (42)
        {
            usleep(10000);
            std::cout << std::endl;
            std::cout<< "=== DEBUT WHILE " << std::endl;
            // print_container(vec);
            // if (*buf_it)
                // print_container(vec_buf);
            mid = find_middle(top, pair_ratio, bot);
            std::cout << "voici bot " << *bot << " mid " << *mid << " top " << *top << std::endl;
            std::cout << "pair_ratio " << pair_ratio;
            std::cout << " donc ma comparaison est: mid " << *mid << " et nb " << nb << std::endl;
            if ((bot + pair_ratio + 1) > top)
            {
                std::cout << "=== FIN DE WHILE" << std::endl;
                std::cout << "voici bot " << *bot << " mid " << *mid << " top " << *top << std::endl;
                break;
            }
            else if (*mid < nb)
                bot = mid;
            else if (*mid > nb)
            {
                top = mid - pair_ratio;
                std::cout << "je passe par une reduction de top: " << *top << std::endl;
            }
        }
        std::cout << std::endl << " !!!DEBUT INSERTION" << std::endl;
/*
        while()
                {
                    iterator mid = ft_findmiddle(start, end, list);
                    if (condition d'arret)
                        break;
                    else if(mid > listnontrier)
                        start = mid;
                    else if(mid < listnontrier)
                        end = mid - taille element;                
                }
                if (mid < listnontrier)
                    insert (apres mid);
                else if (mid > listnontrier)
                    insert (avant mid);
*/

        vec_it = vec.begin();
        buf_it = vec_buf.begin();
        // size_t nb = *buf_it;
        // for(size_t i = 0; i < buf_it; i++)
            // buf_it++;
        std::cout << "comparaison pour insertion: buf_it = " << nb << " mid " << *mid << std::endl;
        // if (*mid > *top && nb > *top)
        // {
        //     std::cout << "je passe par le premier if bizarre " << std::endl;
        //     while (vec_it < top)
        //         vec_it++;
        //     vec_it++;
        // }
        std::cout << std::endl << "MOMENT IMPORTANT !!! " << std::endl;
        if (nb > *mid)
        {
        /*
            if (is_pair_ratio(top, pair_ratio, vec) == 0)
                top++;
            std::cout << "debut de if mon nb est " << nb << " et top de base " << *top;
            std::cout << " top + pair_ratio " << *(top + pair_ratio) << std::endl;
            if (nb > *(top + pair_ratio))
            {
                std::cout << "je prend le ++" << std::endl;
                top++;
            }
            else if (nb < *top)
                top -= pair_ratio;
            while (vec_it < top)
                vec_it++;
            std::cout << "mon vec_it " << *vec_it << " et nb " << nb << std::endl;
            if (*vec_it < nb && is_pair_ratio(vec_it, pair_ratio, vec) == 1) // == 0: pas pair_ratio
                vec_it++;
*/
            while (vec_it < top)
                vec_it++;
            std::cout << "vec_it dans insertion " << *vec_it << std::endl;
            if (is_pair_ratio(top, pair_ratio, vec) == 1 && pair_ratio != 1)
                vec_it++;
            else if (pair_ratio == 1 && nb > *vec_it)
                *vec_it++;
            std::cout << "vec_it dans insertion " << *vec_it << std::endl;
        }
        else if (nb <= *mid)
        {
            std::vector<double>::iterator bot_verif = vec.begin() + pair_ratio - 1;
            std::cout << "bot dans insertion " << *bot << std::endl;
            if (*bot_verif > nb)
            {
                std::cout << "je passe par *bot_verif > nb" << std::endl;
                vec_it = vec.begin();
            }
            else if (nb > *bot && *(bot + pair_ratio) < nb)
            {
                std::cout << "je passe par nb > *bot" << std::endl;
                std::cout << "voici les composantes du if " << *(bot + pair_ratio) << std::endl;
                while (vec_it < mid)
                    vec_it++;
            }
            else
            {
                std::cout << "je passe par le reste" << std::endl;
                if (*bot == *top)
                {
                    while (vec_it < bot)
                        vec_it++;
                    if (nb > *vec_it)
                        vec_it++;
                }
                else
                {
                    while (vec_it < bot)
                        vec_it++;
                    vec_it++;
                }
            }
        }
        for(size_t i = 0; i < pair_ratio; i++)
        {
            std::cout << "valeur de vecteur " << *buf_it << std::endl;
            std::cout << "voici les differentes composante de l'insertion: (vec_it et buf_it)" << std::endl;
            std::cout << *vec_it + i << " 1 " << *buf_it << std::endl;
            vec.insert(vec_it + i, 1, *buf_it);
            buf_it = vec_buf.erase(buf_it);
        }
        std::cout << "!!! FIN INSERTION" << std::endl;
        print_container(vec);
        if (*buf_it)
            print_container(vec_buf);
        pair_size -= pair_ratio;
    }
    std::cout << std::endl << "SORTIE DE TRI DICOTO " << std::endl;
    print_container(vec);
}

std::vector<double>::iterator Algo::find_middle(std::vector<double>::iterator top, int pair_ratio, std::vector<double>::iterator bot)
{
    // garder sa taille de contenaire
    // comparer milieu est plus petit ou plus grand que le nb
    std::vector<double>::iterator mid;
    size_t dist = std::distance(bot, top);
    std::vector<double>::iterator tmp = bot + (dist / 2);
    // std::cout << " en entrant voici mon top " << *top << " et bot " << *bot << std::endl;
    // std::cout << "voici ma distance " << dist << std::endl;
    // std::cout << "voici nb de tmp " << *tmp << std::endl;
    // std::cout << "--- find mid" << std::endl;
    std::vector<double>::iterator tmp2 = bot;
    while (bot < tmp)
    {
        if (tmp2 > tmp)
            break;
        tmp2 += pair_ratio;
    }
    mid = tmp2;
    std::cout << "--- fin de find mid" << std::endl;
    // if (bot + pair_ratio - 1 == top)
        // return 
    // std::cout << " mid en sortant de find mid " << *mid + << std::endl;
    return mid + pair_ratio - 1;
    // trouver comment faire un bon mid
    // -> je pourrais parcourir ma liste a par pair_size, diviser le top par 2
    // puis regarder quel valeur de pair_size est la plus proche de top / 2

    // faire une boucle pour trouver les nombres en pair_size
    // int tmp = 0;
    // int cpt = 0;
    // size_t mid;
    // while (bot < top / 2)
    // {
    //     cpt++;
    //     bot += pair_ratio;
    // }
    // tmp = bot / 2;
    // if (odd == 0)
    //     mid = pair_ratio * cpt + 1;
    // else
    //     mid = pair_ratio * cpt;
    // return mid;
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

bool Algo::is_pair_ratio(std::vector<double>::iterator it, int pair_ratio, std::vector<double> vec)
{
    size_t i;
    if (pair_ratio > 1)
        i = pair_ratio - 1;
    else
        i = pair_ratio;
    while ((i + pair_ratio) <= vec.size())
    {
        // std::cout << "dans is_pair_ratio it = " << *it << " vec[i] " << vec[i];
        // std::cout << " et la valeur de i " << i << std::endl;
        if (*it == vec[i])
        {
            std::cout << "la valeur == pair_ratio" << std::endl;
            return 1;
        }
        i += pair_ratio;
    }
    std::cout << "la valeur n'est pas pair_ratio" << std::endl;
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

// template<typename T>
// void print_container(T vec, size_t pair_ratio)
// {
//     size_t i = 0;
//     (void)pair_ratio;
//     size_t j = -1;
//     if (pair_ratio == j)
//     {
//         std::cout << "voici print cointainer: ";
//         while (vec[i] != vec.back())
//         {
//             if (vec[i] == vec.back())
//                 break;
//             std::cout << vec[i] << " ";
//             i++;
//         }
//         std::cout << vec[i] << std::endl;
//     }
//     else
//     {
//         std::cout << "voici print cointainer: ";
//         while (vec[i] != vec.back())
//         {
//             std::cout << "[";
//             j = 0;
//             std::cout << " i " << i << " " << vec.back();
//             while (j < pair_ratio)
//             {
//                 if (vec[i] == vec.back())
//                     break;
//                 usleep(10000);
//                 std::cout << " " << vec[i];
//                 j++;
//                 i++;
//             }
//             std::cout << "] ";
//             i++;
//         }
//         std::cout << vec[i] << "]" << std::endl;
//     }
// }


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
