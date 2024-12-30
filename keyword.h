//Author: Kyle Frohlich
//Name: DNencrypt
//Purpose: Decrpyt malware encoded within DNA sequences
//Date: 19Sep2024

#ifndef KEYWORD_H
#define KEYWORD_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Keyword
{
    private: 
        char firstChar;
        char secondChar;
        string fullKeyword;
        int keywordLength;

    public:
        Keyword();
        Keyword(char, char, string, int);

        void setFirstChar(char);
        void setSecondChar(char);
        void setKeyword(string);
        void setKeywordLength(int);

        char getFirstChar();
        char getSecondChar();
        string getKeyword();
        int getKeywordLength();

        void assignValues();
};

#endif