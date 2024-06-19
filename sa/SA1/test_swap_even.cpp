#define TEST_MODE
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cassert>
#include "ques.cpp"

using namespace std;

int testSwapAtEvenPositionEmptyAndSingle()
{
    srand(time(0));
    DoublyLinkedList<int> list;

    list.swapAtEvenPosition();
    string expectedOutput = "";
    string actualOutput = list.display();
    if (actualOutput != expectedOutput)
    {
        return 0;
    }

    list.append(2);
    list.swapAtEvenPosition();

    string expectedOutput2 = "2";
    string actualOutput2 = list.display();
    if (actualOutput2 != expectedOutput2)
    {
        return 0;
    }

    return 3;
}

int testSwapAtEvenPositionEvenLength()
{
    srand(time(0));
    int numElements;
    DoublyLinkedList<int> list;
    vector<int> v;

    for (int j = 0; j < 2; j++)
    {
        numElements = (rand() % 25 + 10) * 2;
        for (int i = 1; i <= numElements; i++)
        {
            v.push_back(rand() % 40 + 10);
            list.append(v[v.size() - 1]);
        }

        list.swapAtEvenPosition();
        string expectedOutput = "";
        bool isEven = true;
        for (int i = 1; i <= v.size(); i++)
        {
            if (i % 2 == 0)
            {
                expectedOutput += to_string(v[i - 1]) + " <-> ";
                expectedOutput += to_string(v[i - 2]) + " <-> ";
            }
        }

        expectedOutput = expectedOutput.substr(0, expectedOutput.size() - 5);

        string actualOutput = list.display();
        if (expectedOutput != actualOutput)
        {
            return 0;
        }

        for (int i = 1; i <= v.size(); i++)
        {
            if (i % 2 == 0)
            {
                int temp = v[i - 1];
                v[i - 1] = v[i - 2];
                v[i - 2] = temp;
            }
        }
    }

    return 10;
}

int testSwapAtEvenPositionOddLength()
{
    int numElements;
    numElements = (rand() % 25 + 20) * 2 + 1;
    DoublyLinkedList<int> list;
    vector<int> v;

    for (int j = 0; j < 2; j++)
    {
        for (int i = 1; i <= numElements; i++)
        {
            v.push_back(rand() % 40 + 10);
            list.append(v[v.size() - 1]);
        }

        list.swapAtEvenPosition();
        string expectedOutput = "";

        for (int i = 1; i <= v.size() - 1; i++)
        {
            if (i % 2 == 0)
            {
                expectedOutput += to_string(v[i - 1]) + " <-> ";
                expectedOutput += to_string(v[i - 2]) + " <-> ";
            }
        }

        expectedOutput += to_string(v[v.size() - 1]);

        string actualOutput = list.display();
        if (expectedOutput != actualOutput)
        {
            return 0;
        }
        numElements = (rand() % 25 + 5) * 2;

        for (int i = 1; i <= v.size(); i++)
        {
            if (i % 2 == 0)
            {
                int temp = v[i - 1];
                v[i - 1] = v[i - 2];
                v[i - 2] = temp;
            }
        }
    }

    return 10;
}

int main()
{
    int score = 0;
    score += testSwapAtEvenPositionEmptyAndSingle();
    cout << score << endl;
    score += testSwapAtEvenPositionEvenLength();
    cout << score << endl;
    score += testSwapAtEvenPositionOddLength();
    cout << score << endl;

    cout << "Your score is: " << score << " / 23" << endl;
}
