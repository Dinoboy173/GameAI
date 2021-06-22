#include <iostream>
#include <string>

bool IsNum(char character)
{
    if (character > '0' && character <= '9')
        return true;

    return false;
}

std::string BuildSubString(int repeatNum, std::string repeatStr)
{
    std::string resultStr = "";

    for (int i = 0; i < repeatStr.length(); i++)
    {
        if (IsNum(repeatStr[i]))
        {
            // maybe check if substring within first then process them differently to there being none

            // need header folder to access stringBuilder
            // feed substring into stringBuilder
        }
        else
        {
            for (int j = 0; j < repeatNum; j++)
            {
                resultStr += repeatStr[i];
            }
        }
    }

    //std::cout << repeatNum << " " << repeatStr << std::endl;

    return resultStr;
}

std::string stringBuilder(std::string input)
{
    int counter = 0;
    int repeatNum = 0;
    std::string repeatStr = "";
    std::string resultStr = "";
    bool copying = false;
    bool isNum = false;

    for (int i = 0; i < input.length(); i++)
    {
        // is number or letter
        // if number are there brackets after
        // if brackets copy everything in them
        // else move on
        // if letter copy till bracket

        if (!copying)
        {
            if (IsNum(input[i]))
            {
                repeatNum = input[i] - '0';
                isNum = true;
            }
        }

        if (isNum)
        {
            if (input[i] == '[')
            {
                counter++;

                copying = true;
            }
            else if (input[i] == ']')
            {
                counter--;
                if (counter == 0)
                {
                    copying = false;

                    resultStr += BuildSubString(repeatNum, repeatStr);

                    repeatStr = "";

                    isNum = false;
                }
            }
        }
        else
        {
            resultStr += input[i];
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