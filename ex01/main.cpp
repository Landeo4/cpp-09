#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc > 3)
    {
        std::cout << "too many arguments" << std::endl;
        return 1;
    }
    else if (argc < 2)
    {
        std::cout << "please put 2 arguments" << std::endl;
        return 1;
    }
    RPN obj;
    if (obj.check_args(argv) == 1)
        return 1;
}

// votre programme doit prendre une expression mathematique polonaise inversee en argument

// les nombres utilises dans cette operation et passe en argument seront toujous moins de 10
//le calcul en lui meme mais aussi le resultat ne compte pas dans la regle

// votre programme doit faire le calcul et l'afficher dans la sortie standard

// si une erreur adviens pendant l'execution du programme, un message d'erreur doit etre
// renvoye dans la sorite standard

// votre programme doit gerer les operation avec ses operateur: "+ - / *"

//si 3 nombre mais plus d'operation, mettre une erreur