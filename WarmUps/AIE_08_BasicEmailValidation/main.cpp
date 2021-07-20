#include <iostream>
#include <string>
// TODO:
// write the validate Email method

bool validateEmail(const std::string& email)
{
    int size = email.size();

    bool hasAt = false;
    bool hasDot = false;

    if (email[0] == '@' || email[0] == '.') return false;

    for (int i = 0; i < size; i++)
    {
        if (email[i] == '@')
        {
            if (hasAt) return false;

            else if (hasDot) return false;

            hasAt = true;
        }

        if (email[i] == '.')
        {
            if (!hasAt) return false;

            else if (email[i - 1] == '.') return false;

            hasDot = true;
        }

        if (email[i] == ' ') return false;
    }

    if (hasAt && hasDot) return true;

    else return false;
}

int main(int argc, char** argv)
{
    std::cout << validateEmail("@gmail.com") << std::endl;          //false
    std::cout << validateEmail("hello.gmail@com") << std::endl;     //false
    std::cout << validateEmail("gmail") << std::endl;               //false
    std::cout << validateEmail("hello@gmail") << std::endl;         //false
    std::cout << validateEmail("hello @gmail") << std::endl;        //false
    std::cout << validateEmail("test@domain..com") << std::endl;    //false  (double dot after @) - not aloud
    std::cout << validateEmail("test@sub.domain.com") << std::endl; //true - sub domain aloud
    std::cout << validateEmail("hello@edabit.com") << std::endl;    //true
    return 0;
}