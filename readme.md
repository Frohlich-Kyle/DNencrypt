Title: EncodeDNA
Author: Kyle Frohlich

EncodeDNA is an auxiliary program meant to supplement and test the functionality of
DNencrypt

Steps
1.) In terminal run the "make" command to compile and generate the executable,
2.) Your code that you want to translate should be entered into "input.txt".
3.) Run "./encode".
4.) Your code in "input.txt" will be translated into DNA in "output.txt".



Title: DNencrypt
Author: Kyle Frohlich

Steps
1.) In terminal run the "make" command to compile and generate the executable.
2.) Add a DNA sequence into "testsequence.txt". Do not add any extra spaces or endlines.
3.) Add in your desired keywords in the format;
    keyword 1
    keyword 2
    keyword 3

    Each keyword should be followed with a single endline except the last one.
    An extra endline here will cause problems because the program will try to
    enter it as a keyword of length 1 which is not allowed.
4.) Run "./dna" to begin the scan.
5.) Follow the in program instructions as needed. Breakdown below in Full Decryption.



Full Decryption (Part of DNencrypt)

1.) You will be asked if you want to decrypt or not. Choosing no aborts the program.
2.) If yes, you will be asked to choose a filename (in the form of yourfilename.txt)
3.) While writing to your .txt file you will be asked if you want to see the output in your screen.