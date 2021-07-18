#include <iostream>
#include <vector>
#include <string>

// todo:: write the cup swap method

char cupSwap(const std::vector<std::string>& swaps)
{
    char ballPos = 'B'; // ball starts at B
    int size = swaps.size();

    for (int i = 0; i < size; i++)
    {
        if (swaps[i] == "AB" || swaps[i] == "BA")
        {
            if (ballPos == 'A')         ballPos = 'B';
            else if (ballPos == 'B')    ballPos = 'A';
        }
        else if (swaps[i] == "BC" || swaps[i] == "CB")
        {
            if (ballPos == 'B')         ballPos = 'C';
            else if (ballPos == 'C')    ballPos = 'B';
        }
        else if (swaps[i] == "AC" || swaps[i] == "CA")
        {
            if (ballPos == 'A')         ballPos = 'C';
            else if (ballPos == 'C')    ballPos = 'A';
        }
    }

    return ballPos;
}

int main(int argc, char** argv)
{
    std::cout << cupSwap({ "AB", "CA", "AB" }) << std::endl;          // C
    std::cout << cupSwap({ "AB", "CA" }) << std::endl;                // C
    std::cout << cupSwap({ "AC", "CA", "CA", "AC" }) << std::endl;    // B
    std::cout << cupSwap({ "BA", "AC", "CA", "BC" }) << std::endl;    // A

    return 0;
}
