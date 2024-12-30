//Author: Kyle Frohlich
//Name: DNencrypt
//Purpose: Decrpyt malware encoded within DNA sequences
//Date: 19Sep2024

#include "keyword.h"
#define KEYWORDLIMIT 100
#define ASCIIsize 127

int getKeywords(Keyword[], ifstream&);
int inputDNA(ifstream&, char[]);
void convertDNA(int[], char[], int);
bool scanDNA(int[], Keyword[], int, int);
void hashKeyLetters(Keyword[], char[], int);
bool keywordScan(int[], int, Keyword);
bool doWarning(int[], int, Keyword);
void fullyDecrypt(int, int[], ofstream&);

//add agrc and argv for custom txt file input for keywords, dna, and code
int main()
{
    ifstream inputKeywordFile("keywords.txt");
    if(!inputKeywordFile.good())
    {
        cout << "Error opening keyword file." << endl;
        return 0;
    }
    Keyword arrayKeywords[KEYWORDLIMIT];
    int numKeywords = getKeywords(arrayKeywords, inputKeywordFile);
    inputKeywordFile.close();
    
    ifstream inputSequenceFile("testsequence.txt");
    if(!inputSequenceFile.good())
    {
        cout << "Error opening DNA sequence file." << endl;
        return 0;
    }
    //implement dynamic resizing array for dna array sometime
    char nucleotideSequence[100000];
    int length = inputDNA(inputSequenceFile, nucleotideSequence);
    inputSequenceFile.close();
    int binaryLength = length * 2;
    int binarySequence[binaryLength];

    convertDNA(binarySequence, nucleotideSequence, length);

    cout << "Starting DNA Scan" << endl;
    bool didWrite = scanDNA(binarySequence, arrayKeywords, binaryLength, numKeywords);

    if(didWrite == true)
    {
        cout << endl << "Code written to text file" << endl;
    }
    cout << endl << endl << "Exiting program" << endl;

    return 0;
}



int getKeywords(Keyword arrayKeywords[], ifstream& keywordFile)
{
    int numKeywords = 0;
    string tempKeyword;
    //char tempChar1, tempChar2;
    //Keyword keywordArray[KEYWORDLIMIT];

    while(keywordFile.good())
    {
        getline(keywordFile, tempKeyword, '\n');
        arrayKeywords[numKeywords].setKeyword(tempKeyword);
        arrayKeywords[numKeywords].assignValues();
        cout << "Keyword " << numKeywords + 1 << ": " << arrayKeywords[numKeywords].getKeyword() << endl;
        numKeywords++;
    }

    cout << numKeywords << " Keywords Stored" << endl;
    return numKeywords;
}

int inputDNA(ifstream& dnaFile, char dnaSequence[])
{
    int length = 0;
    while(dnaFile.good())
    {
        dnaSequence[length] = dnaFile.get();
        // cout << dnaSequence[length];
        length++;
    }
    cout << "DNA sequence read" << endl;
    return length - 1;
}

void convertDNA(int binarySequence[], char nucleotideSequence[], int length)
{
    //for the purposes of this project we are assuming the following nucleotide substitution key
    //A = 00, T = 01, C = 10, G = 11

    //int binLength = length * 2;
    int index2 = 0;

    //for loop to go through n nucleotides
    for(int index = 0; index < length; index++)
    {
        switch(nucleotideSequence[index])
        {
            case 'A':
                //A is 00
                binarySequence[index2] = 0;
                binarySequence[index2 + 1] = 0;
                break;
            case 'T':
                //T is 01
                binarySequence[index2] = 0;
                binarySequence[index2 + 1] = 1;
                break;
            case 'C':
                //C is 10
                binarySequence[index2] = 1;
                binarySequence[index2 + 1] = 0;
                break;
            case 'G':
                //G is 11
                binarySequence[index2] = 1;
                binarySequence[index2 + 1] = 1;
                break;
        }
        // cout << "Nucleotide: " << nucleotideSequence[index];
        // cout << " " << binarySequence[index2] << " " << binarySequence[index2 + 1] << " " << endl;
        index2+=2;
    }

    cout << "DNA converted to binary" << endl << endl;
}

void hashKeyLetters(Keyword allKeywords[], char secondLetters[], int numKeywords)
{
    //this takes the value of the first character to be used as the hash index
    //the hash index is then filled with the second character
    //this allows us to implicitly get the first character and explicitly get the second character

    int tempASCIIdec;

    for(int index = 0; index < numKeywords; index++)
    {
        tempASCIIdec = static_cast<int>(allKeywords[index].getFirstChar());
        secondLetters[tempASCIIdec] = allKeywords[index].getSecondChar();

        cout << "First Letter: " << allKeywords[index].getFirstChar();
        cout << " - Index hash location: " << tempASCIIdec;
        cout << " - 2nd letter at index: " << secondLetters[tempASCIIdec];
        cout << " - 2nd letter value: " << static_cast<int>(allKeywords[index].getSecondChar()) << endl;
        //cout << allKeywords[index].getFirstChar() << allKeywords[index].getSecondChar() << endl;
    }
}

bool scanDNA(int binarySequence[], Keyword arrayKeywords[], int binLength, int numKeywords)
{
    bool finishScan = false;
    string tempByte;
    int tempASCII;
    char tempChar;
    int index, index2, index3, index4;
    bool foundKeyword = false;

    //make an array of 2nd letter keywords
    //we hash the 2nd letter to the position of the first letter
    //this allows us to get the first letter by implicit and second letter explicit

    //bool firstLetters[sizeof(arrayKeywords)]
    
    char secondLetters[ASCIIsize];
    for(int index = 0; index < ASCIIsize; index++)
    {
        secondLetters[index] = '\0';
    }
    hashKeyLetters(arrayKeywords, secondLetters, numKeywords);

    //goes through binary sequence in chunks of 8 (a while byte)
    for(index = 0; index < binLength / 8; index++)
    {
        tempByte = "";
        //goes through the byte for conversion
        for(index2 = (index * 8); index2 < (index * 8) + 8; index2++)
        {
            tempByte += to_string(binarySequence[index2]);
        }
        index2 = 0;
        //cout << tempByte << endl;
        tempASCII = stoi(tempByte, nullptr, 2);
        tempChar = static_cast<char>(tempASCII);
        //cout << "The char: " << tempChar << " The ASCII: " << static_cast<int>(tempASCII) << endl;
        //check if 1st character matches
        if(secondLetters[tempASCII] != '\0')
        {
            // cout << "first letter detected" << endl;
            // check if 2nd character matches only if first hash index is found
            // cout << secondLetters[tempASCII] << endl;

            tempByte = "";
            for(index3 = (index * 8) + 8; index3 < (index * 8) + 16; index3++)
            {
                tempByte += to_string(binarySequence[index3]);
            }
            index3 = 0;
            int otherASCII = tempASCII;
            tempASCII = stoi(tempByte, nullptr, 2);
            tempChar = static_cast<char>(tempASCII);
            // cout << tempChar << endl;

            if(secondLetters[otherASCII] == tempChar)
            {
                //cout << "second letter detected" << endl;
                cout << "Attempting Full Keyword Scan" << endl;

                //needs binary sequence, index startpoint, keyword
                for(index4 = 0; index4 < numKeywords; index4++)
                {
                    if(arrayKeywords[index4].getFirstChar() == otherASCII && arrayKeywords[index4].getSecondChar() == tempASCII)
                    {
                        cout << "Keyword Possibly Detected: " << arrayKeywords[index4].getKeyword() << endl;
                        //cout << "first char: " << otherASCII << " second char: " << tempASCII << endl;
                        foundKeyword = keywordScan(binarySequence, index * 8, arrayKeywords[index4]);
                    }
                }
                index4 = 0;

                if(foundKeyword == true)
                {
                    finishScan = doWarning(binarySequence, binLength, arrayKeywords[index4]);
                }
            }
        }
        if(finishScan == true)
        {
            break;
        }
    }
    return finishScan;
}

bool keywordScan(int binarySequence[], int startIndex, Keyword possibleKeyword)
{
    bool keywordFound = false;
    string compareKeyword;
    int keywordLength = possibleKeyword.getKeyword().length();

    //index = 0; index < binLength / 8; index++
    for(int index = startIndex; index < startIndex + (keywordLength * 8); index += 8)
    {
        string tempByte = "";
        // Convert each segment of 8 bits into a character 
        for(int bitIndex = index; bitIndex < index + 8; bitIndex++)
        {
            tempByte += to_string(binarySequence[bitIndex]);
        } 
        char tempChar = static_cast<char>(stoi(tempByte, nullptr, 2));
        compareKeyword += tempChar;
    }
    cout << "Keyword translated: " << compareKeyword << endl;
    cout << "Keyword sent: " << possibleKeyword.getKeyword() << endl;

    if(compareKeyword == possibleKeyword.getKeyword())
    {
        keywordFound = true;
        cout << endl;
        cout << "!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "!!!Keyword Match!!!" << endl;
        cout << "!!!!!!!!!!!!!!!!!!!" << endl << endl;
    }
    return keywordFound;
}

bool doWarning(int binarySequence[], int binLength, Keyword detectedKeyword)
{
    char uInput, writeCheck;
    string txtFileName;
    int selectCheck = 0;
    ofstream outputDetected;
    bool finishScan = true;

    // cout << "A possible keyword has been detected" << endl;
    cout << "Keyword detected: " << detectedKeyword.getKeyword() << endl << endl;
    
    while(selectCheck != 2)
    {
        cout << "Would you like to fully decrypt? Y/N: ";
        cin >> uInput;

        switch(uInput)
        {
            case 'Y':
            case 'y':
                cout << "Please name the txt file where the code will be written" << endl;
                cout << "Format is your filename.txt" << endl;
                do
                {
                    cout << "Enter desired file name: ";
                    cin >> txtFileName;
                    cout << endl << "Is " << txtFileName << " correct? Y/N: ";
                    cin >> writeCheck;
                    switch(writeCheck)
                    {
                        case 'Y':
                        case 'y':
                            //writeCheck has already been changed so it is not modified as double Y has been selected anyways
                            //write to txt file
                            outputDetected.open(txtFileName);
                            if(!outputDetected.good())
                            {
                                cout << "Error opening keyword file." << endl;
                                return 0;
                            }
                            fullyDecrypt(binLength, binarySequence, outputDetected);
                            break;
                        case 'N':
                        case 'n':
                            //implicit assuming that when you press N or n, it loops back to "Enter desired file name"
                            break;
                        default:
                            cout << "Please choose Y, y, N, or n" << endl;
                            writeCheck = 2;
                            break;
                    };

                }while(writeCheck != 'Y' && writeCheck != 'y');
                selectCheck = 2;
                break;

            case 'N':
            case 'n':
                cout << "Aborting program" << endl << endl;
                selectCheck = 2;
                break;

            default:
                cout << "Please choose Y, y, N, or n" << endl;
                selectCheck = 0;
                break;
        };
    }
    return finishScan;
}

void fullyDecrypt(int binLength, int binarySequence[], ofstream& writeFile)
{
    string tempByte;
    int tempASCII;
    char tempChar;
    char uInput;
    bool printTerminal = false;

    cout << "Would you like to view the code decryption process in terminal? (Y/N): ";
    cin >> uInput;
    switch(uInput)
    {
        do
        {
            case 'Y':
            case 'y':
                printTerminal = true;
                break;
            case 'N':
            case 'n':
                break;
            default:
                cout << "Please enter Y, y, N, or n" << endl;
                break;
        }while(uInput != 'Y' && uInput != 'y');
    }

    if(printTerminal == true)
    {
        cout << "-----------------------------------------------" << endl;
    }

    for(int index = 0; index < binLength / 8; index++)
    {
        tempByte = "";
        //goes through the byte for conversion
        for(int index2 = (index * 8); index2 < (index * 8) + 8; index2++)
        {
            tempByte += to_string(binarySequence[index2]);
        }
        //cout << tempByte << endl;
        tempASCII = stoi(tempByte, nullptr, 2);
        tempChar = static_cast<char>(tempASCII);

        writeFile << tempChar;
        if(printTerminal == true)
        {
            cout << tempChar;
        }
    }
    if(printTerminal == true)
    {
        cout << endl << "-----------------------------------------------" << endl;
    }
}