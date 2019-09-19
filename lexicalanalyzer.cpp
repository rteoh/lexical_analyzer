#include <bits/stdc++.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>


using namespace std;

bool isKeyword(char buffer[]);
void lexer(string line); //this checks EACH lexeme and returns a token

int main()
{

    ifstream inputFile;
    inputFile.open("test1.txt");
    
    //file error check
    if(!inputFile.is_open())
    {
        cout << "error in file opening" <<endl;
        exit(0);
    }

    while(!inputFile.eof())
    {
        
        //vector<string> lineVector;
        string line;
        getline(inputFile,line);
        cout << "...Testing getLine..."<<endl;
        cout << line << endl;

        lexer(line);

        /*
        stringstream test1(line);
        string intermediate;

        while(getline(test1, intermediate, ' '))
        {
            lineVector.push_back(intermediate);
        }
        

        //print out vector results
        cout <<"...Testing whitespace seperation..."<<endl;
        for (int i = 0; i < lineVector.size();i++)
        {
            cout << lineVector[i]<<endl;
        }
        cout << endl;
        lineVector.clear();//refreshes the vector for the next line


        */
    }

   

    inputFile.close();

    return 0;
}

//////////////////////Function Definitions////////////////////////////////
/*
    isKeyword function will return true or false if the input buffer is a keyword
*/
bool isKeyword(char buffer[])
{//took this from the internet to compare the characters
    char keywords[32][10]= {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};

    //creating a variable to initcate if buffer is a keyword
    bool indicator = false; // this is the initial response 
    for (int b = 0; b < 32; b++)
    {
        if(strcmp(keywords[b],buffer))
        {
            indicator = true; // if keyword and buffer are the same, then true
            break; //exits the loop
        }
    }

    return indicator;

}
void lexer(string line)
{
    //this will do all the testing and tokening
    
    //check for operators first 
    char operators[] = "+-*/%=";

    //convert string to cstring to check each character 
    int length = line.length();
    char chArray[length+1];
    strcpy(chArray,line.c_str());//this copys the string into char array

    cout <<"...Testing string to char conversion..."<<endl;
    for(int a = 0; a < length;a++)
    {
        cout << chArray[a] << " ";
    }



}
