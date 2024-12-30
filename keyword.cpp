//Author: Kyle Frohlich
//Name: DNencrypt
//Purpose: Decrpyt malware encoded within DNA sequences
//Date: 19Sep2024

#include "keyword.h"

Keyword::Keyword()
{
    firstChar = '-';
    secondChar = '-';
    fullKeyword = "-";
    keywordLength = 0;
    // - signifies that there is nothing and will be used to error check if something hasn't been set
}

Keyword::Keyword(char newFirst, char newSecond, string newKeyword, int newKeywordLength)
{
    firstChar = newFirst;
    secondChar = newSecond;
    fullKeyword = newKeyword;
    keywordLength = newKeywordLength;
}


void Keyword::setFirstChar(char newFirst)
{
    firstChar = newFirst;
}

void Keyword::setSecondChar(char newSecond)
{
    secondChar = newSecond;
}

void Keyword::setKeyword(string newKeyword)
{
    fullKeyword = newKeyword;
}

void Keyword::setKeywordLength(int newKeywordLength)
{
    keywordLength = newKeywordLength;
}



char Keyword::getFirstChar()
{
    return firstChar;
}

char Keyword::getSecondChar()
{
    return secondChar;
}

string Keyword::getKeyword()
{
    return fullKeyword;
}

int Keyword::getKeywordLength()
{
    return keywordLength;
}



void Keyword::assignValues()
{
    if(fullKeyword != "-")
    {
        if(fullKeyword.length() >= 2)
        {
            firstChar = fullKeyword[0];
            secondChar = fullKeyword[1];

            keywordLength = sizeof(fullKeyword);
        }
        else
        {
            cout << "Keyword: " << fullKeyword << " must be at least 2 characters long" << endl;
            cout << "Please revise the keyword to be longer or change it for another" << endl;
        }
    }
    else
    {
        cout << "No keyword saved" << endl;
    }
}