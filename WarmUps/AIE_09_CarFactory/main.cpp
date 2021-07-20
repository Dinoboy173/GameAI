#include <iostream>

// TODO:
// write the GetTotalCarsFromParts method

int GetTotalCarsFromParts(int wheels, int bodies, int figures)
{
    int carsMade = 0;

    while (wheels >= 4 && bodies >= 1 && figures >= 2)
    {
        wheels -= 4;
        bodies -= 1;
        figures -= 2;
        carsMade += 1;
    }
    
    return carsMade;
}

int main(int argc, char** argv)
{
    // (wheels, body, figures)
    //    4      1       2

    std::cout << GetTotalCarsFromParts(2, 48, 76) << std::endl;  // 0
    std::cout << GetTotalCarsFromParts(43, 15, 87) << std::endl; // 10
    std::cout << GetTotalCarsFromParts(88, 37, 27) << std::endl; // 13
    std::cout << GetTotalCarsFromParts(88, 37, 17) << std::endl; // 8

    return 0;
}