/*
Jimmy Phong
Ryan Teoh
Assignment 1 Lexical Analyzer 
*/


//////////////////////////
//         TODO:        //
//////////////////////////

/*
1. USE STATE VARIABLE
2. Create 2 DIM ARRAY
(Use LOOP from CHP 2 PG.13 powerpoint for referance)
3. Implement DFSM into project
4. Fix identifier
(see if the 'word' variable matches any of the know keywords, if it does not, it is an identifier)
5. Show dollar signs in identifier
(remove isalnum and use else statement for both identifier and keywords)
(achieve this by listing out all keywords in c++ by using if-else statement)
*/


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

    // Open Input file
    ifstream inputFile;
    inputFile.open("test1.txt");

    
    //file error check
    if(!inputFile.is_open())
    {
        cout << "error in file opening" <<endl;
        exit(0);
    }


    // Create Header of Output File
    ofstream outFile;
    outFile.open("output.txt");
    outFile <<setw(22)<<"Output: "<<endl;
    outFile <<"TOKENS "<<setw(27)<<"Lexemes"<<endl << endl;
    outFile.close();


    while(!inputFile.eof())
    {  
        vector<string> lineVector;
        string line;
        getline(inputFile,line);
        cout << "...Testing getLine..."<<endl;
        cout << line << endl;//here i am inputing a whole string into the function
        lexer(line);//call the lexer function
    }
    


    inputFile.close();
    cout << "...Testing Complete..." <<endl;
    cout<<"...Terminating Program..."<<endl;
    return 0;
}

//////////////////////Function Definitions////////////////////////////////
/*
    isKeyword function will return true or false if the input buffer is a keyword
*/
bool isKeyword(char buffer[])
{
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
string convertToString(char ch[], int size)
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



    //tokenizing the string below AND print out to file.
    ofstream outFile;
    outFile.open("output.txt", ios::app);

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


    // Check to see if line starts with a valid character
    if(chArray[0] == '!') {
    //if( !isalnum(chArray[0]) || (chArray[0] != '{') || (chArray[0] != '}') || (chArray[0] != '#') || (chArray[0] != '/')  || (chArray[0] != '*')) {

        // If line does not with alpha-numeric or with certain characters, the line will be ignored.
        return;

    } 
    

    for (int b=0; b < length;b++)
    {
        //checks operator
        if(chArray[b]== '+'||chArray[b]== '-'||chArray[b]== '*'||chArray[b]== '/'||
        chArray[b]== '%'||chArray[b]== '='||chArray[b]== '<'||chArray[b]== '>')
        {

            // If previous keyword/identifiers did not get called before operator
            if(position != 0) {

                // Convert char to string
                bufferSize = sizeof(buffer);
                word = convertToString(buffer,bufferSize);

                outFile << "KEYWORD          =         " << word <<endl;  

                // Resets Buffer
                while(position != 0) {
                    buffer[position]= '\0';
                    position--;
                }

            }

            outFile << "OPERATOR         =" << setw(10) << chArray[b]<<endl;


        }
        else if(chArray[b]== '['||chArray[b]== ']'||chArray[b]== '('||chArray[b]== ')'||
        chArray[b]== '{'||chArray[b]== '}'||chArray[b]== '['||chArray[b]== ','||chArray[b]== ';')
        {

            // If previous keyword/identifiers did not get called before operator
            if(position != 0) {

                // Convert char to string
                bufferSize = sizeof(buffer);
                word = convertToString(buffer,bufferSize);

                outFile << "KEYWORD          =         " << word <<endl;  

                // Resets Buffer
                while(position != 0) {
                    buffer[position]= '\0';
                    position--;
                }

            }

            outFile <<"SEPERATOR        =" << setw(10) << chArray[b]<<endl;


        // If char is not space or new line, add char to buffer
        } else if(isalnum(chArray[b])) {

            buffer[position++]=chArray[b];

        } else if((chArray[b] == ' '||chArray[b]=='\n') && (position !=0)) { 

            // Convert char to string
            bufferSize = sizeof(buffer);
            word = convertToString(buffer,bufferSize);



            //once if condition is met, check the things inside buffer and compare
            if(isKeyword(buffer) == true) {

                outFile << "KEYWORD          =         " << word <<endl;  

            } else {

                outFile << "IDENTIFIERS      =         " << word <<endl;

            }

            // Resets Buffer
            while(position != 0) {
                buffer[position]= '\0';
                position--;
            }

        }

    }
    outFile.close();

}
