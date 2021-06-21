#include <iostream>
#include <string>

std::string RepeatLetters(char repeatNum, std::string repeatStr)
{
    std::string resultStr = "";

    // for (int i = 0; i < repeatStr.length(); i++)
    // {
    //     if ()
    // 
    //     //resultStr += repeatStr[i];
    // }

    std::cout << repeatNum << " " << repeatStr << std::endl;

    return repeatStr;
}

std::string stringBuilder(std::string input)
{
    int counter = 0;
    char repeatNum = 0;
    std::string repeatStr = "";
    std::string resultStr = "";
    bool copying = false;

    for (int i = 0; i < input.length(); i++)
    {
        // is number or letter
        // if number are there brackets after
        // if brackets copy everything in them
        // else move on
        // if letter copy till bracket

        if (input[i] == '[')
        {
            counter++;

            if (!copying) repeatNum = input[i - 1];

            copying = true;
        }
        else if (input[i] == ']')
        {
            counter--;
            if (counter == 0)
            {
                copying = false;

                resultStr += RepeatLetters(repeatNum, repeatStr);

                repeatStr = "";
            }
        }

        if (copying)
        {
            if (counter == 1 && input[i] == '[')
            {
            }
            else
                repeatStr += input[i];
        }
    }

    return resultStr;
}

int main(int argc, char** argv)
{
    std::cout << stringBuilder("a2") << std::endl;
    std::cout << stringBuilder("3[a]2[bc]") << std::endl;
    std::cout << stringBuilder("3[a2[c]]") << std::endl;
    std::cout << stringBuilder("2[abc]3[cd]ef") << std::endl;
    return 0;
}