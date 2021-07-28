#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>

class Dictionary
{
public:

    std::fstream dictionary;

    std::vector<std::string> words;

    Dictionary(const char* filename)
    {
        dictionary.open(filename, std::ios_base::in | std::ios_base::binary);

        if (dictionary.is_open())
        {
            char byte = 0;

            std::string wordFromFile = "";

            while (dictionary.get(byte))
            {
                if (byte == '\n')
                {
                    words.push_back(wordFromFile);
                    wordFromFile = "";
                }
                else
                {
                    wordFromFile += byte;
                }
            }

            words.push_back(wordFromFile);
        }
    }

    ~Dictionary()
    {
        dictionary.close();
    }

    bool Contains(const char* word)
    {
        if (dictionary.is_open())
        {
            static int wordsCount = 178690;

            std::string upperWord = "";

            
            upperWord += std::toupper(word);

            int s = upperWord.size();

            for (int i = 0; i < wordsCount; i++)
            {
                int strCompare = upperWord.compare(words[i]);

                if (strCompare == 1)
                {
                    return true;
                }
            }
        }

        return false;
    }

protected:
private:
};

int main(int argc, char** argv)
{
    {
        Dictionary dictionary("dictionary.txt");

        std::cout << std::boolalpha;
        std::cout << dictionary.Contains("AA") << std::endl;
        std::cout << dictionary.Contains("hello") << std::endl;
        std::cout << dictionary.Contains("pilgrimaged") << std::endl;
        std::cout << dictionary.Contains("ejector") << std::endl;
        std::cout << dictionary.Contains("thisworddoesntexist") << std::endl;
        std::cout << dictionary.Contains("z") << std::endl;
    }
    return 0;
}
