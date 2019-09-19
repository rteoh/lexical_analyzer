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
string convertToString(char ch[], int size);
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
        cout << line << endl;//here i am inputing a whole string into the function
        lexer(line);//call the lexer function
    
    }
    cout <<endl;
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
//converting character array to string for printing
string convertToString(char*ch, int size)
{
    string str = "";
    for(int d = 0; d < size; d++)
    {
        str = str + ch[d];
    }
    return str;
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
    cout <<setw(10)<<"Output: "<<endl;
    cout <<"token "<<setw(20)<<"lexeme"<<endl;

    char buffer[15];//this will be inputed into keyWords function
    int position = 0;//this is the position in the buffer char array
    int bufferSize;
    string word;

    /*
        This could be an implementation of Finite State Machine
        Initial State is at the source code input
        Reads each character and catagorize them
        Once done goes to the next state and repeats the process until no more inputs
        Final State will be reached at output

    */    
    for (int b=0; b < length;b++)
    {
        //checks operator
        if(chArray[b]== '+'||chArray[b]== '-'||chArray[b]== '*'||chArray[b]== '/'||
        chArray[b]== '%'||chArray[b]== '='||chArray[b]== '<'||chArray[b]== '>')
        {
            cout << "operator"<<setw(15)<<chArray[b]<<endl;

        }

        //checks seperator
        if(chArray[b]== '['||chArray[b]== ']'||chArray[b]== '('||chArray[b]== ')'||
        chArray[b]== '{'||chArray[b]== '}'||chArray[b]== '[')
        {
            cout <<"seperator"<<setw(15)<< chArray[b]<<endl;

        }

        //keywords and identifier
        if(isalnum(chArray[b])) // this checks if char is alphanumeric
        {
            buffer[position++];
        }
        else if((chArray[b] == ' '||chArray[b]=='\n')&&(position !=0))
        {//I took this from the internet to help break this apart
            //buffer[position]= '\0';
            //position = 0; 
            //both of these will reset the buffer and positon to zero
            //that way the program can continue to run the checking states.

            bufferSize = sizeof(buffer);
            word = convertToString(buffer,bufferSize);
            //once if condition is met, check the things inside buffer and compare
            if(isKeyword(buffer))
            {//if true
                
                cout << "keyword"<<setw(15)<<word<<endl;;
                
            }
            else
            {
                cout <<"identifier"<<setw(15)<<word<<endl;;
            }
            

        }

//*/



    }


}
