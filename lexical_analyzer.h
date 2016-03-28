#include <iostream>
#include <fstream>
#include "token.h"


using namespace std;


void readFile(ifstream& fstream);

void analyze_for_token(ifstream& fstream, Token& token);

bool isSpace(char c);

bool isSingleQuote(char c);
void startSingleQuotes(ifstream& fstream, Token& token);
void endSingleQuotes(ifstream& fstream, Token& token);

bool isDoubleQuote(char c);
void startDoubleQuotes(ifstream& fstream, Token& token);

bool isOpenComment(char c);
bool isClosedComment(char c);
void startComment(ifstream& fstream, Token& token);

bool isDigit(char c);
void startNumber(ifstream& fstream, Token& token);

bool isLetter(char c);
void startIdentifying(ifstream& fstream, Token& token, char c);
void checkIfKeyword(Token& token);

bool isPeriod(char c);
void checkForPeriod(ifstream& fstream, Token& token);

void checkForGreater(ifstream& fstream, Token& token);
void checkForLess(ifstream& fstream, Token& token);

void checkForSwap(ifstream& fstream, Token& token);

void startLineComment(ifstream& fstream, Token& token);