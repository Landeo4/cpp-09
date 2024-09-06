#include "PmergeME.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "please put a least 2 elements" << std::endl;
        return 1;
    }
    Algo obj;
    std::cout << "liste de base: ";
    for(int i = 1; argv[i]; i++)
        std::cout << argv[i] << " ";
    std::cout << std::endl << std::endl;
    std::vector<double> vec;
    if (obj.check_element_vector(argv, argc, vec) == 1)
        return 1;
    for (int i = 1; i < argc; i++)
    {
        double nb = atof(argv[i]);
        // std::cout << "voici push " << nb << std::endl;
        vec.push_back(nb);
    }
    int pair = 1;
    obj.start_algo(pair, vec);
}
