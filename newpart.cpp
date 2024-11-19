#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>

using namespace std;

// variables
string token;
int dfa = 1;
int count;
int column = 2;
typedef pair<string, string> Token;
map<string, string> symbolTable;
vector<pair<string, string>> tokensArray;

void state1(char c);
void state2(char c);
void state3(char c);
void state4(char c);
void state5(char c);
void state6(char c);
void state7(char c);
void state8(char c);
void state9(char c);
void state10(char c);
void state11(char c);
void state12(char c);
void state13(char c);
void state14(char c);
void state15(char c);
void state16(char c);
void state17(char c);
void state18(char c);
void state19(char c);
void state20(char c);
void state21(char c);
void state22(char c);
void state23(char c);
void state24(char c);
void state25(char c);
void isAccepted(ifstream &rfile);
bool isDot(char c);
bool isLetter(char c);
bool isDigit(char c);
bool isOperator(char c);
bool isUnderscore(char c);
bool isSpace(char c);
bool isSpecialCharacter(char c);
bool isKeyword(const string &str);
bool isIdentifier(const std::string &str);
bool isConstant(char c);
void addToTokensArray(string token, string type);
void addToSymbolTable(const string &identifier, map<string, string> &symbolTable);
void ArrayAccessPoint(const vector<Token> &tokensArray);
void symbolTableAccessPoint(const map<string, string> &symbolTable);
unordered_map<char, unordered_map<string, vector<string>>> parsing_table();

void state1(char c)
{
    if (c == '<')
    {
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
    else if (isSpace(c))
    {
        dfa = 1;
    }
    else if (isSpecialCharacter(c))
    {
        token = token + c;
        dfa = 25;
    }
    else
    {
        dfa = -1;
    }
}

void state2(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 3;
    }
    else if (c == '>')
    {
        token = token + c;
        dfa = 12;
    }
    else
    {
        dfa = -1;
    }
}

void state3(char c)
{
    if (c == '>')
    {
        token = token + c;
        dfa = 13;
    }
    else
    {
        dfa = -1;
    }
}

void state4(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 14;
    }
    else
    {
        dfa = -1;
    }
}

void state5(char c)
{
    if (c == '+')
    {
        token = token + c;
        dfa = 15;
    }
    else
    {
        dfa = -1;
    }
}

void state6(char c)
{
    if (c == '-')
    {
        token = token + c;
        dfa = 16;
    }
    else
    {
        dfa = -1;
    }
}

void state7(char c)
{
    if (c == '&')
    {
        token = token + c;
        dfa = 17;
    }
    else
    {
        dfa = -1;
    }
}

void state8(char c)
{
    if (c == '|')
    {
        token = token + c;
        dfa = 18;
    }
    else
    {
        dfa = -1;
    }
}

void state9(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 20;
    }
    else
    {
        dfa = -1;
    }
}

void state10(char c)
{
    if (c == '?')
    {
        token = token + c;
        dfa = 21;
    }
    else
    {
        dfa = -1;
    }
}

void state11(char c)
{
    if (c == '/')
    {
        token = token + c;
        dfa = 22;
    }
    else if (c == '*')
    {
        token = token + c;
        dfa = 24;
    }
    else
    {
        dfa = -1;
    }
}

void state12(char c)
{
    if (c == '>')
    {
        token = token + c;
        dfa = 13;
    }
    else
    {
        dfa = -1;
    }
}

void state13(char c)
{
    dfa = -1;
}

void state14(char c)
{
    dfa = -1;
}

void state15(char c)
{
    dfa = -1;
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
    else
    {
        dfa = -1;
    }
}

void state17(char c)
{
    if (isDigit(c))
    {
        token = token + c;
        dfa = 17;
    }
    else
    {
        dfa = -1;
    }
}

void state18(char c)
{
    dfa = -1;
}

void state19(char c)
{
    if (c == '"')
    {
        token = token + c;
        dfa = 26;
    }
    else
    {
        token = token + c;
        dfa = 19;
    }
}

void state20(char c)
{
    dfa = -1;
}

void state21(char c)
{
    if (c == '\'')
    {
        token = token + c;
        dfa = 27;
    }
    else
    {
        dfa = -1;
    }
}

void state22(char c)
{
    if (c == '\n')
    {
        token = token + c;
        dfa = 28;
    }
    else
    {
        token = token + c;
        dfa = 22;
    }
}

void state23(char c)
{
    if (isLetter(c) || isDigit(c) || isUnderscore(c))
    {
        token = token + c;
        dfa = 23;
    }
    else
    {
        dfa = -1;
    }
}

void state24(char c)
{
    if (c == '*')
    {
        token = token + c;
        dfa = 29;
    }
    else
    {
        token = token + c;
        dfa = 24;
    }
}

void state25(char c)
{
    dfa = -1;
}

void state26(char c)
{
    dfa = -1;
}

void state27(char c)
{
    dfa = -1;
}

void state28(char c)
{
    dfa = -1;
}

void state29(char c)
{
    if (c == '/')
    {
        token = token + c;
        dfa = 30;
    }
    else
    {
        token = token + c;
        dfa = 24;
    }
}

void state30(char c)
{
    dfa = -1;
}

void isAccepted(ifstream &rfile)
{
    int nextDFA;
    char c;
    while (rfile.get(c))
    {
        switch (dfa)
        {
        case 1:
            state1(c);
            break;
        case 2:
            state2(c);
            break;
        case 3:
            state3(c);
            break;
        case 4:
            state4(c);
            break;
        case 5:
            state5(c);
            break;
        case 6:
            state6(c);
            break;
        case 7:
            state7(c);
            break;
        case 8:
            state8(c);
            break;
        case 9:
            state9(c);
            break;
        case 10:
            state10(c);
            break;
        case 11:
            state11(c);
            break;
        case 12:
            state12(c);
            break;
        case 13:
            state13(c);
            break;
        case 14:
            state14(c);
            break;
        case 15:
            state15(c);
            break;
        case 16:
            state16(c);
            break;
        case 17:
            state17(c);
            break;
        case 18:
            state18(c);
            break;
        case 19:
            state19(c);
            break;
        case 20:
            state20(c);
            break;
        case 21:
            state21(c);
            break;
        case 22:
            state22(c);
            break;
        case 23:
            state23(c);
            break;
        case 24:
            state24(c);
            break;
        case 25:
            state25(c);
            break;
        case 26:
            state26(c);
            break;
        case 27:
            state27(c);
            break;
        case 28:
            state28(c);
            break;
        case 29:
            state29(c);
            break;
        case 30:
            state30(c);
            break;
        default:
            cout << "Invalid DFA state!" << endl;
            break;
        }

        if (dfa == -1)
        {
            if (token != "")
            {
                if (isKeyword(token))
                {
                    addToTokensArray(token, "KEYWORD");
                }
                else if (isIdentifier(token))
                {
                    addToTokensArray(token, "IDENTIFIER");
                    addToSymbolTable(token, symbolTable);
                }
                else if (isConstant(token[0]))
                {
                    addToTokensArray(token, "CONSTANT");
                }
                else
                {
                    addToTokensArray(token, "UNKNOWN");
                }
            }
            token = "";
            dfa = 1;
        }
    }
}

bool isDot(char c)
{
    return c == '.';
}

bool isLetter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || c == '&' || c == '|' || c == '!' || c == '>' || c == '<' || c == '?';
}

bool isUnderscore(char c)
{
    return c == '_';
}

bool isSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

bool isSpecialCharacter(char c)
{
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ';' || c == ':';
}

bool isKeyword(const string &str)
{
    unordered_set<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
    return keywords.find(str) != keywords.end();
}

bool isIdentifier(const std::string &str)
{
    if (!isLetter(str[0]) && !isUnderscore(str[0]))
        return false;

    for (size_t i = 1; i < str.length(); ++i)
    {
        if (!isLetter(str[i]) && !isDigit(str[i]) && !isUnderscore(str[i]))
            return false;
    }

    return true;
}

bool isConstant(char c)
{
    return c == '"' || c == '\'' || isDigit(c);
}

void addToTokensArray(string token, string type)
{
    tokensArray.push_back(make_pair(token, type));
}

void addToSymbolTable(const string &identifier, map<string, string> &symbolTable)
{
    if (symbolTable.find(identifier) == symbolTable.end())
    {
        symbolTable[identifier] = "IDENTIFIER";
    }
}

void ArrayAccessPoint(const vector<Token> &tokensArray)
{
    cout << "\n ******************* Array tokens****************     " << endl;
    for (int i = 0; i < tokensArray.size(); i++)
    {
        string token = tokensArray[i].first;
        string type = tokensArray[i].second;
        cout << "Token: " << token << " \t Type: " << type << endl;
    }
}

void symbolTableAccessPoint(const map<string, string> &symbolTable)
{
    // Code for symbol table access point
}

unordered_map<char, unordered_map<string, vector<string>>> parsing_table()
{
    // Code for parsing table
}

int main()
{
    ifstream rfile("sk.txt");
    if (rfile.fail())
    {
        cout << "Error opening input file." << endl;
        return 0;
    }

    isAccepted(rfile);
    rfile.close();

    ArrayAccessPoint(tokensArray);
    symbolTableAccessPoint(symbolTable);

    return 0;
}
