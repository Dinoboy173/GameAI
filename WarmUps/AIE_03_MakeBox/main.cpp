#include <iostream>
#include <string>
// TODO: create the makeBox method
void makeBox(int size)
{
    int lineNum = 0;
    std::string lineContents = "";

    while (lineNum < size)
    {
        for (int i = 0; i < size; i++)
        {
            if (lineNum == 0 || lineNum == size - 1)
            {
                lineContents += '#';
            }
            else
            {
                if (i == 0 || i == size - 1)
                {
                    lineContents += '#';
                }
                else
                {
                    lineContents += ' ';
                }
            }
        }

        std::cout << lineContents << std::endl;
        lineContents = "";
        lineNum++;
    }
}


int main(int argc, char** argv)
{
    // TODO: 
    // read command line args, extract dimensions
    // prompt if no commandline argumenst are specified

    bool printedArg = false;

    while (true)
    {
        std::string boxSize = "";
        if (argc >= 2 && !printedArg)
        {
            boxSize = argv[1];
            printedArg = true;
        }
        else
        {
            std::cout << "Enter a box size: ";
            std::cin >> boxSize;
        }
        int boxDimention = std::stoi(boxSize);
        makeBox(boxDimention);
        std::cout << std::endl;
    }

    // makeBox(5);
    // std::cout << std::endl;
    // makeBox(3);
    // std::cout << std::endl;
    // makeBox(2);
    // std::cout << std::endl;
    // makeBox(1);
    // std::cout << std::endl;

    return 0;
}