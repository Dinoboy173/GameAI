#include <iostream>
#include <utility>
#include <vector>
#include <chrono>
#include <functional>
// TODO:
// Write the function

namespace Aaron
{
    bool overTwentyOne(const std::vector<char>& cards)
    {
        int total = 0;
        for (const char& card : cards)
        {
            if (card == 'A')
                total += 1;
            else if (card == 'J' || card == 'Q' || card == 'K')
                total += 10;
            else
                total += card - '0';
        }
        return total > 21;
    }
}

namespace Solution
{
    bool OverTwentyOne(const std::vector<char>& arr)
    {
        bool hasAce = false;
        int sum = 0;

        for (auto card : arr)
        {
            if (card >= '2' && card <= '9')
                sum += card - '0';
            else if (card == 'J' || card == 'Q' || card == 'K')
                sum += 10;
        }

        if (hasAce)
        {
            if (sum <= 10)
                sum += 11;
            else
                sum += 1;
        }

        return sum > 21;
    }
}

namespace JWLong
{
    bool OverTwentyOne(const std::vector<char>& arr)
    {
        bool hasAce = false;
        int sum = 0;

        for (auto card : arr)
        {
            if (card == 'A')
                hasAce = true;
            else if (isdigit(card))
                sum += card - '0';
            else if (isalpha(card) && card != 'A')
                sum += 10;

            if (sum > 21)
                return true;
        }

        if (hasAce)
        {
            if (sum <= 10)
                sum += 11;
            else
                sum += 1;
        }

        if (sum > 21)
            return true;
        else return false;
    }
}

namespace JWShort
{
    bool OverTwentyOne(const std::vector<char>& arr)
    {
        bool hasAce = false;
        int sum = 0;
        for (auto card : arr)
        {
            if (card == 'A')
                hasAce = true;
            else if (card - '0' >= 2 && card - '0' <= 10)
                sum += card - '0';
            else if (card == 'J' || card == 'Q' || card == 'K')
                sum += 10;
            if (sum > 21)
                return true;
        }
        if (hasAce)
        {
            if (sum <= 10)
                sum += 11;
            else
                sum += 1;
        }
        if (sum > 21)
            return true;
        else return false;
    }
}

void RunSolution(
    const char* name, std::function< bool(const std::vector<char> & cards)> solutionFn)
{
    int totalTime = 0;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    bool r1, r2, r3, r4, r5, r6;
    std::vector<char> cards1 = { '2', '8', 'J' }; // false
    std::vector<char> cards2 = { 'A', 'J', 'K' }; // false
    std::vector<char> cards3 = { '5', '5', '3', '9' }; // true
    std::vector<char> cards4 = { '2', '6', '4', '4', '5' }; // false
    std::vector<char> cards5 = { 'J', 'Q', 'K' }; // true
    std::vector<char> cards6 = { 'J', '3', 'A' }; // false
    for (int i = 0; i < 5; i++)
    {
        auto t1 = high_resolution_clock::now();
        for (int i = 0; i < 100000; i++)
        {
            r1 = solutionFn(cards1);
            r2 = solutionFn(cards2);
            r3 = solutionFn(cards3);
            r4 = solutionFn(cards4);
            r5 = solutionFn(cards5);
            r6 = solutionFn(cards6);
        }
        auto t2 = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        totalTime += ms_int.count();
    }

    std::cout << name << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::boolalpha;
    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;
    std::cout << r3 << std::endl;
    std::cout << r4 << std::endl;
    std::cout << r5 << std::endl;
    std::cout << r6 << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Average Time: " << totalTime / 5.0f << std::endl << std::endl;
}

int main(int argc, char** argv)
{
    // Test your code

    RunSolution("Ignore", JWLong::OverTwentyOne);

    RunSolution("Jordan", Solution::OverTwentyOne);
    RunSolution("Jordan", Solution::OverTwentyOne);
    RunSolution("Jordan", Solution::OverTwentyOne);
    RunSolution("Jordan", Solution::OverTwentyOne);
    RunSolution("Jordan", Solution::OverTwentyOne);

    // RunSolution("JWLong", JWLong::OverTwentyOne);
    // RunSolution("JWLong", JWLong::OverTwentyOne);
    // RunSolution("JWLong", JWLong::OverTwentyOne);
    // RunSolution("JWLong", JWLong::OverTwentyOne);
    // RunSolution("JWLong", JWLong::OverTwentyOne);
    // 
    // RunSolution("JWShort", JWShort::OverTwentyOne);
    // RunSolution("JWShort", JWShort::OverTwentyOne);
    // RunSolution("JWShort", JWShort::OverTwentyOne);
    // RunSolution("JWShort", JWShort::OverTwentyOne);
    // RunSolution("JWShort", JWShort::OverTwentyOne);

    RunSolution("Aaron", Aaron::overTwentyOne);
    RunSolution("Aaron", Aaron::overTwentyOne);
    RunSolution("Aaron", Aaron::overTwentyOne);
    RunSolution("Aaron", Aaron::overTwentyOne);
    RunSolution("Aaron", Aaron::overTwentyOne);

    return 0;
}