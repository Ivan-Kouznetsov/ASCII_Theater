// ASCII_Theater.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread> 
#include "clear_screen.h"

using namespace std;

void display_frame(vector<string> lines)
{
    clear_screen();
    for (size_t i = 0; i < lines.size(); i++)
    {
        cout << lines[i] << '\n';
    }
}

void print_lines(string filename)
{
    fstream read;
    read.open(filename, fstream::in);

    vector<string> lines;
    string current_line;
    const regex frame_start("\\d+(?=ms)"); // Ex: 600ms
    smatch current_match;
    unsigned int current_duration;

    if (read)
    {
        try {
            while (getline(read, current_line))
            {

                if (regex_search(current_line, current_match, frame_start))
                {
                    // the start of a new frame means we should print the current one, if there is one
                    if (lines.size() > 0)
                    {
                        display_frame(lines);
                        lines.clear();

                        // wait after printing
                        this_thread::sleep_for(chrono::milliseconds(current_duration));
                    }
                    current_duration = stoi(current_match[0].str());
                }
                else
                {
                    lines.push_back(current_line);
                }
            }

            // print last frame
            display_frame(lines);
        }
        catch (exception e)
        {
            cout << e.what();
            read.close();
        }
    }

    read.close();
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        print_lines(argv[1]);
    }
    else
    {
        cout << "Usage ASCII_Theater example.txt";
    }
}
