#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
string token;
int dfa = 0;
int count;
int column = 2;
vector<pair<string, string>> tokensArray;
void addToTokensArray(string token, string type)
{
    tokensArray.push_back(make_pair(token, type));
}

bool isKeyword(string c)
{
    if (c == "auto" || c == "double" || c == "int" || c == "struct" || c == "break" || c == "else" || c == "long" || c == "switch" || c == "case" || c == "enum" || c == "register" || c == "typedef" || c == "char" || c == "extern" ||
        c == "return" || c == "union" || c == "const" || c == "float" || c == "short" || c == "unsigned" || c == "continue" || c == "signed" || c == "for" || c == "void" || c == "default" || c == "goto" || c == "sizeof" || c == "volatile" || c == "do" ||
        c == "if" || c == "static" || c == "while" || c == "asm" || c == "bool" || c == "catch" || c == "class" || c == "const_cast" || c == "delete" || c == "dynamic_cast" || c == "explicit" || c == "export" || c == "false" || c == "friend" ||
        c == "inline" || c == "mutable" || c == "namespace" || c == "new" || c == "operator" || c == "private" || c == "protected" || c == "public" || c == "reinterpret_cast" || c == "static_cast" || c == "template" || c == "this" || c == "throw" || c == "true" || c == "try" || c == "typeid" || c == "typename" || c == "using" || c == "virtual" || c == "wchar")
        return true;
    else
        return false;
}

int iswhitespace(char c)
{
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f');
}
void state0(char c)
{
    if (iswhitespace(c))
    {
        dfa = 0;
    }
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
    {
        token = token + c;
        dfa = 1;
    }

    else if (c >= '0' && c <= '9')
    {
        token = token + c;
        dfa = 3;
    }
    else if (c == '/')
    {
        token = token + c;
        dfa = 8;
    }
    else if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ';' || c == ':' || c == '#')
    {
        token = token + c;
        dfa = 13;
    }
    else if (c == ' ')
    {
        token = token + c;
        dfa = 14;
    }
    else if (c == '"')
    {
        token = token + c;
        dfa = 15;
    }
    else if (c == '|')
    {
        token = token + c;
        dfa = 19;
    }
    else if (c == '&')
    {
        token = token + c;
        dfa = 17;
    }
    else if (c == '^')
    {
        token = token + c;
        dfa = 21;
    }
    else if (c == '!' || c == '=' || c == '*' || c == '%')
    {
        token = token + c;
        dfa = 23;
    }
    else if (c == '>')
    {
        token = token + c;
        dfa = 25;
    }
    else if (c == '<')
    {
        token = token + c;
        dfa = 26;
    }
    else if (c == '+')
    {
        token = token + c;
        dfa = 30;
    }
    else if (c == '-')
    {
        token = token + c;
        dfa = 32;
    }
    else if (c == '?')
    {
        token = token + c;
        dfa = 33;
    }
    else
        dfa = -1;
}
void state1(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        token = token + c;
        dfa = 1;
    }
    else if (c >= 'A' && c <= 'Z')
    {
        token = token + c;
        dfa = 1;
    }
    else if (c == '_')
    {
        token = token + c;
        dfa = 1;
    }
    else if (c >= '0' && c <= '9')
    {
        token = token + c;
        dfa = 1;
    }
    else
    {
        if (isKeyword(token))
        {
            ::count++;
            cout << "Token " << token << " is Keyword" << endl;
            tokensArray.push_back(make_pair(token, "Keyword"));

            token.clear();
            state0(c);
        }
        else
        {
            ::count++;
            cout << "Token " << token << " is Identifier" << endl;
            token.clear();
            state0(c);
        }
    }
}

void state2(char c)
{
    ::count++;
    cout << "Token  " << token << " is Identifier";
    dfa = 0;
    token.clear();
}

void state3(char c)
{
    if (c >= '0' && c <= '9')
    {
        token = token + c;
        dfa = 3;
    }

    else if (c == '.')
    {
        token = token + c;
        dfa = 4;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Constant" << endl;
        token.clear();
        state0(c);
    }
}

void state4(char c)
{
    if (c >= '0' && c <= '9')
    {
        token = token + c;
        dfa = 4;
    }
    else
    {
        ::count++;
        cout << "Token  " << token << " is Constant" << endl;
        token.clear();
        state0(c);
    }
}

void state5(char c)
{
    ::count++;
    cout << "Token  " << token << " is Constant" << endl;
    token.clear();
    state0(c);
}

void state7(char c)
{
    ::count++;
    cout << "Token  " << token << " is Operator" << endl;
    token.clear();
    state0(c);
}

void state8(char c)
{
    if (c == '/')
    {
        token.clear();
        dfa = 9;
    }
    else if (c == '*')
    {
        token.clear();
        dfa = 11;
    }
    else if (c == '=')
    {
        token = token + c;
        dfa = 7;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}

void state9(char c)
{
    if (c == '\n' || c == '\r')
    {
        state0(c);
    }
    else
        dfa = 9;
}

void state10(char c)
{
    token.clear();
    state0(0);
}

void state11(char c)
{
    if (c == '*')
    {
        dfa = 12;
    }
    else
        dfa = 11;
}

void state12(char c)
{
    if (c == '/')
    {
        dfa = 0;
    }
    else
        dfa = -1;
}

void state13(char c)
{
    ::count++;
    cout << "Token  " << token << " is Special Character" << endl;
    token.clear();
    state0(c);
}

void state14(char c)
{
    if (c == ' ')
    {
        token = token + c;
        dfa = 16;
    }
    else
    {
        token = token + c;
        dfa = 14;
    }
}
void state15(char c)
{
    if (c == '"')
    {
        token = token + c;
        dfa = 16;
    }
    else
    {
        token = token + c;
        dfa = 15;
    }
}
void state16(char c)
{
    ::count++;
    cout << "Token  " << token << " is String" << endl;
    token.clear();
    state0(c);
}
void state17(char c)
{
    if (c == '&')
    {
        token = token + c;
        dfa = 18;
    }
    else
    {
        ::count++;
        cout << "Token  " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}

void state18(char c)
{
    ::count++;
    cout << "Token  " << token << " is Operator" << endl;
    token.clear();
    state0(c);
}
void state19(char c)
{
    if (c == '|')
    {
        ::count++;
        token = token + c;
        cout << "Token  " << token << " is Operator" << endl;
        token.clear();
        dfa = 20;
    }
    else
    {
        ::count++;
        cout << "Token  " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state20(char c)
{
    state0(c);
}
void state21(char c)
{
    ::count++;
    cout << "Token  " << token << " is Operator" << endl;
    token.clear();
    state0(c);
}
void state23(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 24;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state24(char c)
{
    ::count++;
    cout << "Token " << token << " is Operator" << endl;
    token.clear();
    state0(c);
}
void state25(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 24;
    }

    else if (c == '>')
    {
        token = token + c;
        dfa = 27;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state26(char c)
{
    if (c == '<')
    {
        token = token + c;
        dfa = 28;
    }

    else if (c == '=')
    {
        token = token + c;
        dfa = 29;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state27(char c)
{
    if (c == '>')
    {
        token = token + c;
        dfa = 29;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state28(char c)
{
    if (c == '<')
    {
        token = token + c;
        dfa = 29;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state29(char c)
{
    ::count++;
    cout << "Token " << token << " is Operator" << endl;
    token.clear();
    state0(c);
}
void state30(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 21;
    }

    else if (c == '+')
    {
        token = token + c;
        dfa = 31;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state31(char c)
{
    ::count++;
    cout << "Token " << token << " is Operator" << endl;
    token.clear();
    state0(c);
}
void state32(char c)
{
    if (c == '=')
    {
        dfa = 21;
    }

    else if (c == '-')
    {
        dfa = 34;
    }
    else
    {
        ::count++;
        cout << "Token " << token << " is Operator" << endl;
        token.clear();
        state0(c);
    }
}
void state33(char c)
{
    if (c == ':')
    {
        dfa = 35;
    }
    else
        dfa = 33;
}
void state34(char c)
{
    if (c == 'd')
    {
        dfa = 1;
    }

    else if (c == 'e')
    {
        dfa = 1;
    }
    else if (c == 'f')
    {
        dfa = 1;
    }
    else
        dfa = -1;
}
void state35(char c)
{
    ::count++;
    cout << "Token " << token << " is Operator" << endl;
    token.clear();
    state0(c);
}

void lexicalAnalyzer(ifstream &file)
{
    char str;
    while (file.get(str))
    {
        if (dfa == 0)
        {
            state0(str);
        }
        else if (dfa == 1)
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
        else if (dfa == 26)
        {
            state26(str);
        }
        else if (dfa == 27)
        {
            state27(str);
        }
        else if (dfa == 28)
        {
            state28(str);
        }
        else if (dfa == 29)
        {
            state29(str);
        }
        else if (dfa == 30)
        {
            state30(str);
        }
        else if (dfa == 31)
        {
            state31(str);
        }
        else if (dfa == 32)
        {
            state32(str);
        }
        else if (dfa == 33)
        {
            state33(str);
        }
        else if (dfa == 34)
        {
            state34(str);
        }
        else if (dfa == 35)
        {
            state35(str);
        }
    }

    cout << "Total tokens are :" << ::count++ << endl;
}

int main()
{
    ifstream file("sk.txt");
    lexicalAnalyzer(file);
    file.close();

    return 0;
}
