#include "lexical_analyzer.h"

void readFile(ifstream& fstream) 
{
	while(fstream.good()) 
	{
		// cout<< c <<endl;

		Token token;
		analyze_for_token(fstream, token);
		cout<< "Token Type: " << token.type << "  Token Value: " << token.value <<endl;

	}
}

void analyze_for_token(ifstream& fstream, Token& token) 
{
	char c = fstream.get();
	if (fstream.eof())
	{
		token.type = END_FILE;
		token.value.append("EOF");
		return;
	}
	if (isSpace(c))
	{
		analyze_for_token(fstream, token);
		return;
	}
	if (isSingleQuote(c))
	{
		startSingleQuotes(fstream, token);
		return;
	}
	if (isDoubleQuote(c))
	{
		startDoubleQuotes(fstream, token);
		return;
	}
	if (isOpenComment(c))
	{
		startComment(fstream, token);
		return;
	}
	if (isDigit(c))
	{
		token.value.append(1, c);
		token.type = INTEGER;
		startNumber(fstream, token);
		return;
	}
	if (isLetter(c))
	{
		startIdentifying(fstream, token, c);
		return;
	}
	if (c == '+')
	{
		token.value = "+";
		token.type = T_PLUS;
		return;
	}
	if (c == '-')
	{
		token.value = "-";
		token.type = T_MINUS;
		return;
	}
	if (c == '*')
	{
		token.value = "*";
		token.type = T_MULTIPLY;
		return;
	}
	if (c == '/')
	{
		token.value = "/";
		token.type = T_DIVIDE;
		return;
	}
	if (c == ',')
	{
		token.value = ",";
		token.type = T_COMMA;
		return;
	}
	if (c == ';')
	{
		token.value = ";";
		token.type = T_SEMI_COLON;
		return;
	}
	if (c == ')')
	{
		token.value = ")";
		token.type = T_CLOSE_PARENTHESIS;
		return;
	}
	if (c == '(')
	{
		token.value = "(";
		token.type = T_OPEN_PARENTHESIS;
		return;
	}
	if (c == '=')
	{
		token.value = "=";
		token.type = T_EQUALS;
		return;
	}
	if (isPeriod(c))
	{
		checkForPeriod(fstream, token);
		return;
	}
	if (c == '>')
	{
		checkForGreater(fstream, token);
		return;
	}
	if (c == '<')
	{
		checkForLess(fstream, token);
		return;
	}
	if (c == ':')
	{
		checkForSwap(fstream, token);
		return;
	}
	if (c == '#')
	{
		startLineComment(fstream, token);
		return;
	}
	cout<< "\nERROR: unknown character\n" <<endl;
	throw 0;
}

bool isSpace(char c) 
{
	if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool isSingleQuote(char c) 
{
	if (c == '\'')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void startSingleQuotes(ifstream& fstream, Token& token) 
{
	char c = fstream.get();
	if (isSingleQuote(c))
	{
		cout<< "\nERROR: Empty char\n" <<endl;
		throw 0;
	}
	token.value.append(1, c);
	endSingleQuotes(fstream, token);
}

void endSingleQuotes(ifstream& fstream, Token& token)
{
	char c = fstream.get();
	if (!isSingleQuote(c))
	{
		cout<< "\nERROR: Invalid char\n" <<endl;
		throw 0;
	}
	token.type = CHAR;
}

bool isDoubleQuote(char c) 
{
	if (c == '\"')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void startDoubleQuotes(ifstream& fstream, Token& token) 
{
	if (fstream.eof())
	{
		cout<< "\nERROR: Incomplete string\n";
		throw 0;
	}
	char c = fstream.get();
	if (!isDoubleQuote(c))
	{
		token.value.append(1, c);
		startDoubleQuotes(fstream, token);
		return;
	}
	token.type = STRING;
}

bool isOpenComment(char c) 
{
	if (c == '{')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isClosedComment(char c) 
{
	if (c == '}')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void startComment(ifstream& fstream, Token& token) 
{
	if (fstream.eof())
	{
		cout<< "\nERROR: Incomplete comment\n";
		throw 0;
	}
	char c = fstream.get();
	if (!isClosedComment(c))
	{
		token.value.append(1, c);
		startComment(fstream, token);
		return;
	}
	token.type = COMMENT;
}

bool isDigit(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void startNumber(ifstream& fstream, Token& token)
{
	if (fstream.eof())
	{
		token.type = INTEGER;
		return;
	}
	char c = fstream.get();
	if (isDigit(c))
	{
		token.value.append(1, c);
		startNumber(fstream, token);
		return;
	}
	if (isLetter(c))
	{
		cout<< "\nERROR: alphanumerical disorder\n";
		throw 0;
	}
	fstream.unget();
}

bool isLetter(char c)
{
	if ( (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_' )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void startIdentifying(ifstream& fstream, Token& token, char c_prev)
{
	token.value.append(1, c_prev);
	if (fstream.eof())
	{
		checkIfKeyword(token);
		return;
	}
	char c = fstream.get();
	if (isDigit(c) || isLetter(c))
	{
		startIdentifying(fstream, token, c);
		return;
	}
	fstream.unget();
	checkIfKeyword(token);
}

void checkIfKeyword(Token& token)
{
	if (token.value == "program")
	{
		token.type = PROGRAM;
	}
	else if (token.value == "var")
	{
		token.type = VAR;
	}
	else if (token.value == "const")
	{
		token.type = CONST;
	}
	else if (token.value == "type")
	{
		token.type = TYPE;
	}
	else if (token.value == "function")
	{
		token.type = FUNCTION;
	}
	else if (token.value == "return")
	{
		token.type = RETURN;
	}
	else if (token.value == "begin")
	{
		token.type = BEGIN;
	}
	else if (token.value == "end")
	{
		token.type = END;
	}
	else if (token.value == "output")
	{
		token.type = OUTPUT;
	}
	else if (token.value == "if")
	{
		token.type = IF;
	}
	else if (token.value == "else")
	{
		token.type = ELSE;
	}
	else if (token.value == "then")
	{
		token.type = THEN;
	}
	else if (token.value == "while")
	{
		token.type = WHILE;
	}
	else if (token.value == "do")
	{
		token.type = DO;
	}
	else if (token.value == "case")
	{
		token.type = CASE;
	}
	else if (token.value == "of")
	{
		token.type = OF;
	}
	else if (token.value == "otherwise")
	{
		token.type = OTHERWISE;
	}
	else if (token.value == "repeat")
	{
		token.type = REPEAT;
	}
	else if (token.value == "for")
	{
		token.type = FOR;
	}
	else if (token.value == "until")
	{
		token.type = UNTIL;
	}
	else if (token.value == "loop")
	{
		token.type = LOOP;
	}
	else if (token.value == "pool")
	{
		token.type = POOL;
	}
	else if (token.value == "exit")
	{
		token.type = EXIT;
	}
	else if (token.value == "mod")
	{
		token.type = MOD;
	}
	else if (token.value == "and")
	{
		token.type = AND;
	}
	else if (token.value == "or")
	{
		token.type = OR;
	}
	else if (token.value == "not")
	{
		token.type = NOT;
	}
	else if (token.value == "read")
	{
		token.type = READ;
	}
	else if (token.value == "succ")
	{
		token.type = SUCC;
	}
	else if (token.value == "pred")
	{
		token.type = PRED;
	}
	else if (token.value == "chr")
	{
		token.type = CHR;
	}
	else if (token.value == "eof")
	{
		token.type = _EOF_;
	}
	else 
	{
		token.type = IDENTIFIER;
	}
}

bool isPeriod(char c) {
	if (c == '.')
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void checkForPeriod(ifstream& fstream, Token& token)
{
	token.value.append(1, '.');
	if (fstream.eof())
	{
		token.type = T_PERIOD;
		return;
	}
	char c = fstream.get();
	if (isPeriod(c))
	{
		token.value.append(1, c);
		token.type = T_DOT_CASE;
		return;
	}
	fstream.unget();
	token.type = T_PERIOD;
}

void checkForGreater(ifstream& fstream, Token& token)
{
	token.value.append(1, '>');
	if (fstream.eof())
	{
		token.type = T_GREATER;
		return;
	}
	char c = fstream.get();
	if (c == '=')
	{
		token.value.append(1, c);
		token.type = T_GREATER_EQUAL;
		return;
	}
	fstream.unget();
	token.type = T_GREATER;
}

void checkForLess(ifstream& fstream, Token& token) 
{
	token.value.append(1, '<');
	if (fstream.eof())
	{
		token.type = T_LESS;
		return;
	}
	char c = fstream.get();
	if (c == '=')
	{
		token.value.append(1, c);
		token.type = T_LESS_EQUAL;
		return;
	}
	if (c == '>')
	{
		token.value.append(1, c);
		token.type = T_NOT_EQUAL;
		return;
	}
	fstream.unget();
	token.type = T_GREATER;
}

void checkForSwap(ifstream& fstream, Token& token) 
{
	token.value.append(1, ':');
	if (fstream.eof())
	{
		token.type = T_COLON;
		return;
	}
	char c = fstream.get();
	if (c == '=')
	{
		token.value.append(1, c);
		char c_next = fstream.get();
		if (fstream.eof())
		{
			token.type = T_COLON;
			return;
		}
		if (c_next == ':')
		{
			token.value.append(1, c_next);
			token.type = T_SWAP;
			return;
		}
		fstream.unget();
		token.type = T_ASSIGNMENT;
		return;
	}
	fstream.unget();
	token.type = T_COLON;
}

void startLineComment(ifstream& fstream, Token& token)
{
	if (fstream.eof())
	{
		token.type = LINE_COMMENT;
		return;
	}
	char c = fstream.get();
	if (c != '\n' &&  c != '\r' )
	{
		token.value.append(1, c);
		startLineComment(fstream, token);
		return;
	}
	token.type = LINE_COMMENT;
}






