#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <map>
using namespace std;

string token;
int dfa = 1;
int count;
int column = 2;
typedef pair<string, string> Token;
map<string, string> symbolTable;

// Function to add an identifier token to the symbol table

vector<pair<string, string>> tokensArray;
void addToTokensArray(string token, string type)
{
	tokensArray.push_back(make_pair(token, type));
}

void addToSymbolTable(const string &identifier, map<string, string> &symbolTable)
{
	symbolTable[identifier] = "identifier"; // Assuming "identifier" is the type for identifiers
}

bool isOperator(char c)
{
	std::string operators = "+-*/%=<>&|!^~";

	return (operators.find(c) != std::string::npos);
}

bool isSign(char c)
{
	return c == '+' || c == '-';
}

bool isDot(char c)
{
	return c == '.';
}

bool isExponent(char c)
{
	return c == 'e' || c == 'E';
}

bool isLetter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool isUnderscore(char c)
{
	return c == '_';
}

bool isSpace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

bool isSpecialCharacter(char c)
{
	// Define a string of special characters
	std::string specialCharacters = "#^(){}[]<>,.;:";

	// Check if the character exists in the specialCharacters string
	return (specialCharacters.find(c) != std::string::npos);
}

bool isKeyword(const string &str)
{
	// List of C++ keywords
	unordered_set<string> keywords = {
		"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit",
		"atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch",
		"char", "char8_t", "char16_t", "char32_t", "class", "compl", "concept", "const",
		"consteval", "constexpr", "const_cast", "continue", "co_await", "co_return",
		"co_yield", "decltype", "default", "delete", "do", "double", "dynamic_cast",
		"else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend",
		"goto", "if", "import", "inline", "int", "long", "module", "mutable", "namespace",
		"new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
		"protected", "public", "reflexpr", "register", "reinterpret_cast", "requires",
		"return", "short", "signed", "sizeof", "static", "static_assert", "static_cast",
		"struct", "switch", "synchronized", "template", "this", "thread_local", "throw",
		"true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
		"virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq", "string"};

	// Check if the string is a C++ keyword
	return keywords.count(str) > 0;
}
bool isIdentifier(const std::string &str)
{
	// Check if the string is empty or starts with a digit
	if (str.empty() || isDigit(str[0]))
	{
		return false;
	}
	// Check each character of the string
	for (char c : str)
	{
		if (!isLetter(c) && c != '_')
		{

			return false;
		}
	}

	// All characters are valid
	return true;
}

bool isConstant(char c)
{
	return (isDigit(c) || c == '.');
}

// This function is for the starting or initial state (q1)of DFA
void state1(char c)
{

	if (c == '<')
	{
		cout << 1;
		token = token + c;
		dfa = 2;
	}
	else if (c == '>')
	{
		token = token + c;
		dfa = 4;
	}
	else if (c == '+')
	{
		token = token + c;
		dfa = 5;
	}
	else if (c == '-')
	{
		token = token + c;
		dfa = 6;
	}
	else if (c == '&')
	{
		token = token + c;
		dfa = 7;
	}
	else if (c == '|')
	{
		token = token + c;
		dfa = 8;
	}
	else if (c == '!' || c == '=' || c == '*' || c == '%')
	{
		token = token + c;
		dfa = 9;
	}
	else if (c == '?')
	{
		token = token + c;
		dfa = 10;
	}
	else if (c == '/')
	{
		token = token + c;
		dfa = 11;
	}
	else if (isDigit(c))
	{
		token = token + c;
		dfa = 16;
	}
	else if (c == '"')
	{
		token = token + c;
		dfa = 19;
	}
	else if (c == '\'')
	{
		token = token + c;
		dfa = 21;
	}
	else if (isLetter(c) || isUnderscore(c))
	{
		token = token + c;
		dfa = 23;
	}
	else if (isSpecialCharacter(c))
	{
		token = token + c;
		dfa = 25;
	}
	else if (isSpace(c))
		dfa = 1;
	else
	{
		cout << "\n\t start  \n"
			 << c;
		dfa = 1;
	}
}
// This function is for the second state (q2) of DFA
void state2(char c)
{
	if (c == '=' || c == '<')
	{
		token = token + c;
		cout << token;
		dfa = 3;
	}

	else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c) || isSpecialCharacter(c))
	{
		dfa = 3;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}

// This function is for the third state (q3) of DFA
void state3(char c)
{
	::count++;
	cout << "Token  " << token << " is Operator" << endl;
	addToTokensArray(token, "Operator"); // Add token to array
	token.clear();
	state1(c);
}

// This function is for the four state (q4)of DFA
void state4(char c)
{

	if (c == '=' || c == '>')
	{
		token = token + c;
		dfa = 3;
	}

	else if (isspace(c) || isConstant(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
	{

		dfa = 3;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
// This function is for the five state (q5)of DFA
void state5(char c)
{
	if (c == '=' || c == '+')
	{
		token = token + c;
		dfa = 3;
	}

	else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
	{

		dfa = 3;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
// This function is for the six state (q6)of DFA
void state6(char c)
{

	if (c == '-' || c == '=')
	{
		token = token + c;
		dfa = 3;
	}
	else if (isspace(c) || isDigit(c) || isUnderscore(c) || isLetter(c) || isOperator(c))
	{

		dfa = 3;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
// This function is for the seven state (q7)of DFA
void state7(char c)
{

	if (c == '&')
	{
		token = token + c;
		dfa = 3;
	}

	else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
	{

		dfa = 3;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}

// This function is for the eight state (q8)of DFA
void state8(char c)
{
	if (c == '|')
	{
		token = token + c;
		dfa = 3;
	}
	else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
	{

		dfa = 3;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
// This function is for the nine state (q9)of DFA final satage
void state9(char c)
{
	if (c == '=')
	{
		token = token + c;
		dfa = 3;
	}
	else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore || isOperator(c))
	{
		dfa = 3;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}

void state10(char c)
{
	if (c == ':')
	{
		dfa = 3;
	}
	else
	{

		dfa = 10;
	}
}

void state11(char c)
{
	if (c == '=')
	{
		token = token + c;
		dfa = 3;
	}
	else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
	{
		dfa = 3;
	}
	else if (c == '/')
	{
		token.clear();
		dfa = 12;
	}
	else if (c == '*')
	{
		token.clear();
		dfa = 13;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
void state12(char c)
{
	if (c == '\n')
	{
		dfa = 15;
	}
	else
	{
		dfa = 12;
	}
}

void state13(char c)
{
	if (c == '*')
	{
		dfa = 14;
	}
	else
	{
		dfa = 13;
	}
}
void state14(char c)
{
	if (c == '*')
	{
		dfa = 14;
	}
	else if (c == '/')
	{
		dfa = 15;
	}

	else
	{
		dfa = 13;
	}
}
void state15(char c)
{
	token.clear();
	state1(0);
}
void state16(char c)
{
	if (isDigit(c))
	{
		token = token + c;
		dfa = 16;
	}
	else if (isDot(c))
	{
		token = token + c;
		dfa = 17;
	}
	else if (isOperator(c) || isSpace(c) || isSpecialCharacter(c) || isLetter(c) || isUnderscore(c))
	{

		dfa = 18;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
void state17(char c)
{
	if (isDigit(c))
	{
		token = token + c;
		dfa = 17;
	}
	else if (isOperator(c) || isSpace(c) || isSpecialCharacter(c) || isLetter(c) || isUnderscore(c))
	{

		dfa = 18;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
void state18(char c)
{
	::count++;
	cout << "Token  " << token << " is Constant" << endl;
	addToTokensArray(token, "Constant"); // Add token to array
	token.clear();
	state1(c);
}
void state19(char c)
{
	if (c == '"')
	{
		token = token + c;
		dfa = 20;
	}
	else
	{
		token = token + c;
		dfa = 19;
	}
}
void state20(char c)
{
	::count++;
	cout << "Token  " << token << " is String " << endl;
	addToTokensArray(token, "String"); // Add token to array
	token.clear();
	state1(c);
}
void state21(char c)
{

	if (c == '\'')
	{
		token = token + c;
		dfa = 20;
	}
	else
	{
		token = token + c;
		dfa = 22;
	}
}
void state22(char c)
{
	if (c == '\'')
	{
		token = token + c;
		dfa = 20;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}
void state23(char c)
{
	if (isLetter(c) || c == '_' || isDigit(c))
	{
		token = token + c;
		dfa = 23;
	}

	else if (isspace(c) || isSpecialCharacter(c) || isOperator(c))
	{

		dfa = 24;
	}
	else
	{
		cout << "\n\t wrong entry \n"
			 << c;
		dfa = 0;
	}
}

void state24(char c)
{

	if (isKeyword(token))
	{
		::count++;
		cout << "Token:  " << token << "    is Keyword" << endl;
		addToTokensArray(token, "Keyword"); // Add token to array

		token.clear();
		state1(c);
	}
	else
	{
		::count++;
		cout << "Token " << token << " is Identifier" << endl;
		addToTokensArray(token, "Identifier "); // Add token to array
		token.clear();
		state1(c);
	}
}
void state25(char c)
{
	::count++;
	cout << "Token  " << token << " is Special Character" << endl;
	addToTokensArray(token, "special character "); // Add token to array
	token.clear();
	state1(c);
}

void isAccepted(ifstream &rfile)
{

	char str;

	while (true)
	{
		if (dfa == 1)
		{
			state1(str);
		}
		else if (dfa == 2)
		{
			state2(str);
		}
		else if (dfa == 3)
		{
			state3(str);
		}
		else if (dfa == 4)
		{
			state4(str);
		}
		else if (dfa == 5)
		{
			state5(str);
		}
		else if (dfa == 6)
		{
			state5(str);
		}
		else if (dfa == 7)
		{
			state7(str);
		}
		else if (dfa == 8)
		{
			state8(str);
		}
		else if (dfa == 9)
		{
			state9(str);
		}
		else if (dfa == 10)
		{
			state10(str);
		}
		else if (dfa == 11)
		{
			state11(str);
		}
		else if (dfa == 12)
		{
			state12(str);
		}
		else if (dfa == 13)
		{
			state13(str);
		}
		else if (dfa == 14)
		{
			state14(str);
		}
		else if (dfa == 15)
		{
			state15(str);
		}
		else if (dfa == 16)
		{
			state16(str);
		}
		else if (dfa == 17)
		{
			state17(str);
		}
		else if (dfa == 18)
		{
			state18(str);
		}
		else if (dfa == 19)
		{
			state19(str);
		}
		else if (dfa == 20)
		{
			state20(str);
		}
		else if (dfa == 21)
		{
			state21(str);
		}
		else if (dfa == 22)
		{
			state21(str);
		}
		else if (dfa == 23)
		{
			state23(str);
		}
		else if (dfa == 24)
		{
			state24(str);
		}
		else if (dfa == 25)
		{
			state25(str);
		}

		if (rfile.eof())
		{
			// Add a space to the file
			ofstream outfile("temp.txt", ios::app);
			outfile << ' ';
			outfile.close();

			// Reopen the file and resume reading
			rfile.close();
			rfile.open("temp.txt");

			// Clear the end-of-file flag
			rfile.clear();

			// Reset the DFA state if needed
			// ...
			break;

			// Resume the while loop
		}

		// Read the next character from the file
		rfile.get(str);
	}
	cout << "Total tokens are :" << ::count++ << endl;
}

void ArrayAcessPoint(const vector<Token> &tokensArray, map<string, string> &symbolTable)
{
	cout << "\n \n \t array tokens" << endl;
	for (int i = 0; i < tokensArray.size(); i++)
	{
		string token = tokensArray[i].first;
		string type = tokensArray[i].second;
		cout << "Token: " << token << ", Type: " << type << endl;
	}
}

void symbolTableAcessPoint(const map<string, string> &symbolTable)
{
	cout << "\n \n \t symbol table " << endl;
	for (const auto &entry : symbolTable)
	{
		cout << "Identifier: " << entry.first << endl;
	}
}

int main()
{

	ifstream rfile;
	rfile.open("sk.txt");
	isAccepted(rfile);
	rfile.close();

	// acessing token and puting in symbol table
	ArrayAcessPoint(tokensArray, symbolTable);

	symbolTableAcessPoint(symbolTable);

	return 0;
}
