#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "libraries.h"


std::vector <std::vector<std::string>> chageCode
        {
                {"-1", "-1", "-1", "-1", "-1"},
                {"-1", "", "101", "110", "111"},
                {"-1", "11111", "", "11101", "11110"},
                {"-1", "111110", "111111", "", "111101"},
                {"-1", "1111101", "1111110", "1111111", ""} };

std::string firstCode[] = {"-1", "00", "01", "10", "11"};

int codification[5][127] = {{-1}};
constexpr int cost[] = {0, 3, 5, 6, 7};
constexpr int weights[] = {0, 3, 5, 6, 7};


std::vector <std::vector<char>> inverted_chars(5);

#define NUM_COD 4
#define GET_CHAR(x) (x - 32)
#define mayusToMinus(x) (x + ('a' - 'A'))
#define minusToMayus(x) (x + ('A' - 'a'))

namespace preprocessing
{
    const char vocals[] = {'a', 'e', 'i', 'o', 'u'};

    void inialize(){
        for(auto & i : codification)
            for(int j = 0; j < 127;j++)
                i[j]= -1;
    }

    void preprocess1()
    {
        int cod = 1;
        int counter = 0;
        for (auto c : vocals){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
    }
    void preprocess2()
    {
        int cod = 2;
        int counter = 0;
        for (auto c : vocals){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
        for (auto c : vocals){
            codification[cod][minusToMayus(c)] = counter++;
            inverted_chars[cod].push_back(minusToMayus(c));
        }
        for (char c = '0'; c <= '9'; c++){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);

        }
        for (char c = 32; c <= 40; c++){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
    }
    void preprocess3()
    {
        int cod = 3;
        int counter = 0;

        for (char c = 'a'; c <= 'z'; c++){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
        for (char c = 'A'; c <= 'Z'; c++){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
        for (char c = 91; c <= 95; c++){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
        for (char c = 123; c <= 126; c++){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
    }
    void preprocess4()
    {
        int cod = 4;
        int counter = 0;

        for (char c = 32; c <= 126; c++){
            codification[cod][c] = counter++;
            inverted_chars[cod].push_back(c);
        }
    }
}


void preprocess()
{
    using namespace preprocessing;
    inialize();
    preprocess1();
    preprocess2();
    preprocess3();
    preprocess4();
}


#endif