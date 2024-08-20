#include "PmergeME.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "please put a least 2 elements" << std::endl;
        return 1;
    }
    Algo<int> obj;
    if (obj.check_element_vector(argv, argc) == 1)
        return 1;
}
