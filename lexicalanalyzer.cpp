#include <bits/stdc++.h>
#include <ctype.h>
#include <iomanip>
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
    char operators[] = "+-*/%=<>";

    //convert string to cstring to check each character 
    int length = line.length();
    char chArray[length+1];
    strcpy(chArray,line.c_str());//this copys the string into char array

    cout <<"...Testing string to char conversion..."<<endl;
    for(int a = 0; a < length;a++)
    {
        cout << chArray[a] << " ";
    }

    //tokenizing the string below
    cout << "...Testing tokenization of the string..."<<endl;
    char buffer[15];//this will be inputed into keyWords function


    /*
        This could be an implementation of Finite State Machine
        Initial State is at the source code input
        Reads each character and catagorize them
        Once done goes to the next state and repeats the process until no more inputs
        Final State will be reached

    */    
    for (int b=0; b < length;b++)
    {

        if(chArray[b]== '+'||chArray[b]== '-'||chArray[b]== '*'||chArray[b]== '/'||
        chArray[b]== '%'||chArray[b]== '='||chArray[b]== '<'||chArray[b]== '>')//check operator
        {
            cout << "operator"<<setw(15)<<chArray[b]<<endl;

        }

        if(chArray[b]== '['||chArray[b]== ']'||chArray[b]== '('||chArray[b]== ')'||
        chArray[b]== '{'||chArray[b]== '}'||chArray[b]== '[')
        {


        }





    }


}
