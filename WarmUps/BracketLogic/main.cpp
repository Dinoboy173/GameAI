#include <iostream>
#include <string>
// TODO: create the bracketLogic method

bool IsOpenBracket(char bracket)
{
    return bracket == '(' || bracket == '[' || bracket == '{' || bracket == '<';
}

char OppositeBracket(char bracket)
{
    switch (bracket)
    {
    case '(': return ')';
    case ')': return '(';

    case '[': return ']';
    case ']': return '[';

    case '{': return '}';
    case '}': return '{';

    case '<': return '>';
    case '>': return '<';

    default: return '!';
    }
}

bool bracketLogic(std::string input)
{
    std::string brackets = "";
    std::string bracketStack = "";
    int bracketsSize = 0;
    int size = input.size();

    for (int i = 0; i < size; i++)
    {
        if (input[i] == '(' || input[i] == ')' || input[i] == '[' || input[i] == ']' || input[i] == '{' || input[i] == '}' || input[i] == '<' || input[i] == '>')
        {
            brackets += input[i];
        }
    }

    bracketsSize = brackets.size();
    
    for (int i = 0; i < bracketsSize; i++)
    {
        if (IsOpenBracket(brackets[i]))
        {
            bracketStack += brackets[i];
        }
        else
        {
            if (OppositeBracket(brackets[i]) == bracketStack.back())
            {
                bracketStack.pop_back();
            }
        }
    }

    return bracketStack.empty();
}

int main(int argc, char** argv)
{
    std::cout << std::boolalpha;
    std::cout << "Expected: true\t\t got: " << bracketLogic("[<>()]") << std::endl; // [<>()]
    std::cout << "Expected: false\t\t got: " << bracketLogic("[<(>)]") << std::endl; // [<(>)]
    std::cout << "Expected: false\t\t got: " << bracketLogic("[(a*b+<7-c>+9]") << std::endl; // [(<>]
    std::cout << "Expected: false\t\t got: " << bracketLogic("[{(h*i+3)-12]/4*x+2}") << std::endl; // [{()]}
    std::cout << "Expected: true\t\t got: " << bracketLogic("[ab(c/d<e-f+(7*6)>)+2]") << std::endl; // [(())]
    return 0;
}
