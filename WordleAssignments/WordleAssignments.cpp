#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

enum class ForegroundColor : int {
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int {
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103,
    Grey = 100
};

using namespace std;

int main()
{
    srand(time(NULL));
    string line;
    ifstream wordfile("words.txt");
    vector <string> wordList;
    if (wordfile.is_open())
    {
        while (getline(wordfile, line))
        {
            wordList.emplace_back(line);
        }
        cout << wordList.size() << endl;
        wordfile.close();
    }
    else
    {
        cout << FOREGROUND(ForegroundColor::BrightRed, "Error: Unable to open file!");
    }
    bool notQuit = true;
    while (notQuit)
    {


        cout << "guess word pls" << endl;

        int tries = 6;
        string target = wordList[rand() % wordList.size()];
        cout << target << endl;
        bool playing = true;

        while (playing && tries > 0)
        {
            string input;
            cin >> input;

            while (input.length() != 5)
            {
                cout << "Enter a valid word of 5 letters" << endl;
                cin >> input;

            }

            for (int i = 0; i < input.length(); i++)
            {
                input[i] = toupper(input[i]);
            }

            // Check if word is valid
            if (find(wordList.begin(), wordList.end(), input) != wordList.end())
            {


                // Compare to target string

                for (int i = 0; i < input.length(); i++)
                {
                    if (input[i] == target[i])
                    {
                        cout << BACKGROUND(BackgroundColor::Green, input[i]);
                    }
                    else if (find(target.begin(), target.end(), input[i]) != target.end())
                    {
                        cout << BACKGROUND(BackgroundColor::Yellow, input[i]);
                    }
                    else
                    {
                        cout << BACKGROUND(BackgroundColor::Grey, input[i]);
                    }

                }
                cout << endl;
                for (int i = 0; i < input.length(); i++)
                {
                    if (input[i] == target[i])
                    {
                        playing = false;
                    }
                    else
                    {
                        playing = true;
                        tries--;
                        break;
                    }
                }

                // Output input color coded
                cout << (input[0] == target[0]) << endl;

                // Wait for input
            }
            else
                cout << "valid word plz" << endl;
        }
        cout << "Play again?" << endl;
        cout << "1: Yes.  2: No." << endl;
        string input;
        while (true)
        {
            cin >> input;
            if (input == "1")
            {
                break;
            }
            else if (input == "2") 
            {
                notQuit = false;
                break;
            }
            else
            {
                cout << "valid input plz" << endl;
            }
        }
    }
}