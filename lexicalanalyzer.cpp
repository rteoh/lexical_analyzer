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

#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>


using namespace std;

bool isKeyword(vector<char>buffer);
void lexer(vector<char>chVector, vector<char>buffer); //this checks EACH lexeme 
//void operator(vector<char>buffer);
//void seperator(vector<char>buffer);

int main()
{
	// Open Input file
	ifstream inputFile;
	inputFile.open("test1.txt");

	//file error check
	if (!inputFile.is_open())
	{
		cout << "error in file opening" << endl;
		exit(0);
	}

	// Create Header of Output File
	ofstream outFile;
	outFile.open("output.txt");
	outFile << setw(22) << "Output: " << endl;
	outFile << "TOKENS " << setw(27) << "Lexemes" << endl << endl;
	outFile.close();

	//vector initialization
	vector<char> chVector;	//hold the characters
	vector<char> buffer;	//pushes characters from chVector 

	while (!inputFile.eof())
	{
		string line;
		getline(inputFile, line);
		cout << "...Testing getLine..." << endl;
		cout << line << endl;//here i am inputing a whole string into the function
		
		//converts string and puts each char into a vector
		cout << "...Testing Correct Vector Input..." << endl;
		copy(line.begin(), line.end(), back_inserter(chVector));
		for (int a = 0; a < chVector.size(); a++)
		{
			cout << chVector[a]<< " ";
		}
		cout << endl;
		//passing the vector into the lexer function for tokenization
		lexer(chVector,buffer);	//call the lexer function
		chVector.clear();		//clears for next line
	}

	inputFile.close();
	cout << "...Testing Complete..." << endl;
	cout << "...Terminating Program..." << endl;
	return 0;
}

//////////////////////Function Definitions////////////////////////////////
bool isKeyword(vector<char> buffer)
{
	//convert buffer to string
	string str(buffer.begin(), buffer.end());
	cout <<"Buffer in String Form: " <<str << endl;
	
	string keywords[33] = { "auto","bool","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while" };
	
	//check if the word in the buffer is a keyword
	bool indicator = false; // this is the initial response 
	for (int c = 0; c < 33; c++)
	{
		if (str == keywords[c])
		{
			indicator = true;//set true if found 
			cout << str << " is a keyword" << endl;
		}
		
	}


	return indicator;

}

//void operator(vector<char>buffer)
//{
//	
//}
//void seperator(vector<char> buffer)
//{
//
//
//}
//

void lexer(vector<char>chVector,vector<char>buffer)
{
	//check for operators first 
	char operators[] = "+-*/%=<>";

	//tokenizing the string below AND print out to file.
	ofstream outFile;
	outFile.open("output.txt", ios::app);


	/*
		This could be an implementation of Finite State Machine
		Initial State is at the source code input
		Reads each character and catagorize them
		Once done goes to the next state and repeats the process until no more inputs
		Final State will be reached at output
	*/


	// Check to see if line starts with a valid character
	if (chVector[0] == '!') {
		//if( !isalnum(chArray[0]) || (chArray[0] != '{') || (chArray[0] != '}') || (chArray[0] != '#') || (chArray[0] != '/')  || (chArray[0] != '*')) {

			// If line does not with alpha-numeric or with certain characters, the line will be ignored.
		return;

	}

	string wordInBuffer;
	//This goes through chVector and adds into buffer if needed
	for (int b = 0; b < chVector.size(); b++)
	{
		//checks operator
		if (chVector[b] == '+' || chVector[b] == '-' || chVector[b] == '*' || chVector[b] == '/' ||
			chVector[b] == '%' || chVector[b] == '=' || chVector[b] == '<' || chVector[b] == '>')
		{
			//TOOK OUT wordInBuffer here, not relevant
			outFile << "OPERATOR         =" << setw(10) << chVector[b] << endl;

		}
		else if (chVector[b] == '[' || chVector[b] == ']' || chVector[b] == '(' || chVector[b] == ')' ||
			chVector[b] == '{' || chVector[b] == '}' || chVector[b] == '[' || chVector[b] == ',' || chVector[b] == ';')
		{
			// If previous keyword/identifiers did not get called before operator
			if (!buffer.empty())
			{
				string wordInBuffer(buffer.begin(), buffer.end());
				cout << "Current Word: " << wordInBuffer << endl;
				if (isKeyword(buffer) == true)
					outFile << "KEYWORD          =         " << wordInBuffer << endl;
				else
					outFile << "IDENTIFIER       =         " << wordInBuffer << endl;

				// Resets Buffer
				buffer.clear();
			}
			outFile << "SEPERATOR        =" << setw(10) << chVector[b] << endl;
		}
		else if (isalnum(chVector[b])|| chVector[b] == '$')
		{
			buffer.push_back(chVector[b]);
			cout << "Inside Buffer: ";
			for (int p = 0; p < buffer.size(); p++)
			{
				cout << buffer[p];
			}
			cout << endl;
			
		}
		else if ((chVector[b] == ' ' || chVector[b] == '\n') && (!buffer.empty())) {

			//// Convert char to string
			//bufferSize = sizeof(buffer);
			//word = convertToString(buffer, bufferSize);

			string wordInBuffer(buffer.begin(), buffer.end());
			cout << "Current Word: " << wordInBuffer << endl;

			//once if condition is met, check the things inside buffer and compare
			if (isKeyword(buffer) == true) 
				outFile << "KEYWORD          =         " << wordInBuffer << endl;
			else 
				outFile << "IDENTIFIER       =         " << wordInBuffer << endl;

			// Resets Buffer
			buffer.clear();

		}

	}
	outFile.close();

}
