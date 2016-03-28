#include <iostream>
#include <fstream>
#include "lexical_analyzer.h"


using namespace std;

bool printAST;

int main(int argc, char * argv[])
{
	char * filename;
	if (argc < 2 || argc > 3)
	{
		cout<< "\nERROR: incorrect amount of arguments\n" <<endl;
		return 1;
	}
	if (argc == 3)
	{
		if (string(argv[1]) == "-ast")
		{
			cout<< "Read File" <<endl;
			cout<< "Print Abstract Syntax Tree" <<endl;
			printAST = true;
			filename = argv[2];
 		}
		else 
		{
			cout<< "\nERROR: unrecognizable argument(s)\n" <<endl;
			return 1;
		}
	}
	else
	{
		cout<< "Read File" <<endl;
		filename = argv[1];
	}

	ifstream inputfile (filename);

	if (!inputfile.is_open())
	{
		cout<< "\nERROR: unrecognizable file name(s)\n" <<endl;
		return 1;
	}
	if (printAST)
	{
		/* print Abstract Syntax Tree */
	}
	
	try 
	{
		readFile(inputfile);
	}
	catch(int n) { }
	
	cout<< "made it to end" <<endl;
	return 0;
}