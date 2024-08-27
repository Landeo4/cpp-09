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
    if (obj.check_element_vector(argv, argc) == 1)
        return 1;
    int pair = 0;
    obj.start_algo(pair);
}
