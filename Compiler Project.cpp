
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Declaring Veriables
string token;
int count;
int dfa = 1;

typedef pair<string, string> Token;
map<string, string> symbolTable;
vector<pair<string, string>> tokensArray;

void 	LA(const vector<Token> &tokensArray);
void	SYA();
void	SEA();

//Global States Functions Declaration
void s1(char c);
void s2(char c);
void s3(char c);
void s4(char c);
void s5(char c);
void s6(char c);
void s7(char c);
void s8(char c);
void s9(char c);
void s10(char c);
void s11(char c);
void s12(char c);
void s13(char c);
void s14(char c);
void s15(char c);
void s16(char c);
void s17(char c);
void s18(char c);
void s19(char c);
void s20(char c);
void s21(char c);
void s22(char c);
void s23(char c);
void s24(char c);
void s25(char c);

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
void isAccepted(ifstream &abdul_file);
void symbolTableAcessPoint(const map<string, string> &symbolTable);

void s1(char c)
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
    else if (c == '\"')
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
// This function is for the second s (q2) of DFA
void s2(char c)
{
    if (c == '=' || c == '<')
    {
        token = token + c;
        cout << token;
        dfa = 3;
    }

    else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c) || isSpecialCharacter(c))
    {
        s3(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}

// This function is for the third s (q3) of DFA
void s3(char c)
{
    ::count++;
    addToTokensArray(token, "Operator"); // Add token to array
    token.clear();
    s1(c);
}

// This function is for the four s (q4)of DFA
void s4(char c)
{

    if (c == '=' || c == '>')
    {
        token = token + c;
        dfa = 3;
    }

    else if (isspace(c) || isConstant(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
    {

        s3(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}
// This function is for the five s (q5)of DFA
void s5(char c)
{
    if (c == '=' || c == '+')
    {
        token = token + c;
        dfa = 3;
    }

    else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
    {

        s3(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}
// This function is for the six s (q6)of DFA
void s6(char c)
{

    if (c == '-' || c == '=')
    {
        token = token + c;
        dfa = 3;
    }
    else if (isspace(c) || isDigit(c) || isUnderscore(c) || isLetter(c) || isOperator(c))
    {

        s3(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}
// This function is for the seven s (q7)of DFA
void s7(char c)
{

    if (c == '&')
    {
        token = token + c;
        dfa = 3;
    }

    else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
    {

        s3(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}

// This function is for the eight s (q8)of DFA
void s8(char c)
{
    if (c == '|')
    {
        token = token + c;
        dfa = 3;
    }
    else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c) || isOperator(c))
    {

        s3(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}
// This function is for the nine s (q9)of DFA final satage
void s9(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 3;
    }
    else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore || isOperator(c))
    {
        s3(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}

void s10(char c)
{
    if (c == ':')
    {
        dfa = 3;
    }
    else
    {

        s10(c);
    }
}

void s11(char c)
{
    if (c == '=')
    {
        token = token + c;
        dfa = 3;
    }
    else if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore(c))
    {
        s3(c);
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
void s12(char c)
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

void s13(char c)
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
void s14(char c)
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
void s15(char c)
{
    token.clear();
    s1(c);
}
void s16(char c)
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
    else if (c != '$' || !isDigit(c))
    {

        s18(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}
void s17(char c)
{
    if (isDigit(c))
    {
        token = token + c;
        dfa = 17;
    }
    else if (c != '$' || !isDigit(c))
    {

        s18(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}
void s18(char c)
{

    ::count++;
    addToTokensArray(token, "Constant"); // Add token to array
    token.clear();
    s1(c);
}
void s19(char c)
{
    if (c == '\"')
    {
        token = token + c;
        dfa = 20;
    }
    else if (c == '\\')  //added code
    {
    	token = token + c;//
    	dfa = 26;//
	}
    else
    {
        token = token + c;
        dfa = 19;
    }
}
void s20(char c)
{
    ::count++;
    addToTokensArray(token, "String"); // Add token to array
    token.clear();
    s1(c);
}
void s21(char c)
{

    if (c == '\'')
    {
        token = token + c;
        s20(c);
    }
    else if (c == '\\')

    {
        token = token + c;
        dfa = 22;
    }
    else
    {
        token = token + c;
        dfa = 21; //change from 22
    }
}
void s22(char c)
{
    if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore || isOperator(c))
    {
        token = token + c;
        dfa = 21; //chage from 20
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}
void s23(char c)
{
    if (isLetter(c) || c == '_' || isDigit(c))
    {
        token = token + c;
        dfa = 23;
    }

    else if (isspace(c) || isSpecialCharacter(c) || isOperator(c))
    {

        s24(c);
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}

void s24(char c)
{

    if (isKeyword(token))
    {
        ::count++;
        addToTokensArray(token, "Keyword"); // Add token to array

        token.clear();
        s1(c);
    }
    else
    {
        ::count++;
        addToTokensArray(token, "Identifier"); // Add token to array
        addToSymbolTable(token, symbolTable);
        token.clear();
        s1(c);
    }
}
void s25(char c)
{
    ::count++;
    addToTokensArray(token, "special character "); // Add token to array
    token.clear();
    s1(c);
}
void s26(char c)
{
	 if (isspace(c) || isDigit(c) || isLetter(c) || isUnderscore || isOperator(c))
    {
        token = token + c;
        dfa = 19; //chage from 20
    }
    else
    {
        cout << "\n\t wrong entry \n"
             << c;
        dfa = 0;
    }
}

void isAccepted(ifstream &abdul_file)
{

    char str;

    while (abdul_file.get(str))
    {
        

        if (dfa == 1)
        {
            s1(str);
        }
        else if (dfa == 2)
        {
            s2(str);
        }
        else if (dfa == 3)
        {
            s3(str);
        }
        else if (dfa == 4)
        {
            s4(str);
        }
        else if (dfa == 5)
        {
            s5(str);
        }
        else if (dfa == 6)
        {
            s6(str);//s 5
        }
        else if (dfa == 7)
        {
            s7(str);
        }
        else if (dfa == 8)
        {
            s8(str);
        }
        else if (dfa == 9)
        {
            s9(str);
        }
        else if (dfa == 10)
        {
            s10(str);
        }
        else if (dfa == 11)
        {
            s11(str);
        }
        else if (dfa == 12)
        {
            s12(str);
        }
        else if (dfa == 13)
        {
            s13(str);
        }
        else if (dfa == 14)
        {
            s14(str);
        }
        else if (dfa == 15)
        {
            s15(str);
        }
        else if (dfa == 16)
        {
            s16(str);
        }
        else if (dfa == 17)
        {
            s17(str);
        }
        else if (dfa == 18)
        {
            s18(str);
        }
        else if (dfa == 19)
        {
            s19(str);
        }
        else if (dfa == 20)
        {
            s20(str);
        }
        else if (dfa == 21)
        {
            s21(str);
        }
        else if (dfa == 22)
        {
            s22(str); //sate 21
        }
        else if (dfa == 23)
        {
            s23(str);
        }
        else if (dfa == 24)
        {
            s24(str);
        }
        else if (dfa == 25)
        {
            s25(str);
        }
        else if (dfa == 26)
        {
            s26(str);
        }

        if (abdul_file.eof())
        {
            // Add a space to the file
           /* ofstream outfile("temp.txt", ios::app);
            outfile << ' ';
            outfile.close();

            // Reopen the file and resume reading
            abdul_file.close();*/
            abdul_file.open("temp.txt");
            abdul_file.clear();

            break;
        }
    }
    
}

bool isOperator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case '<':
        case '>':
        case '&':
        case '|':
        case '!':
        case '^':
            return true;
        default:
            return false;
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

bool isUnderscore(char c)
{
    return c == '_';
}

bool isSpace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

bool isSpecialCharacter(char c) {
    switch (c) {
        case '#':
        case '^':
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ',':
        case '.':
        case ';':
        case ':':
            return true;
        default:
            return false;
    }
}


bool isKeyword(const string &str)
{
    // List of C++ keywords
    unordered_set<string> keywords = {
        "asm", "auto", "bool", "break", "case", "catch", "char", "class", "const", "const_cast",
        "continue", "default", "delete", "do", "double", "dynamic_cast", "else", "enum",
        "explicit", "export", "extern", "false", "float", "for", "friend", "goto", "if", "inline",
        "int", "long", "mutable", "namespace", "new", "operator", "private", "protected", "public",
        "register", "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_cast",
        "struct", "switch", "template", "this", "throw", "true", "try", "typedef", "typeid", "typename",
        "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "cout", "cin",
        "function", "endl", "string"};

    // Check if the string is a C++ keyword
    return keywords.count(str) > 0;
}

bool isIdentifier2(const std::string& str)
{
   if (str=="Identifier")
   return true;
   else return false;
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
    return true || !isKeyword(str);
}

bool isConstant2(const std::string &str)
{
    // Check if the string is empty
    if (str.empty())
    {
        return false;
    }

    // Check each character of the string
    for (char c : str)
    {
        if (!std::isdigit(c) && c != '.')
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

// **************************** Parsing Table  LL(1) *********************************

unordered_map<string, unordered_map<string, vector<string>>> parsingTable = {
    {"S", {{"cout", {"A"}}, {"cin", {"B"}}, {"if", {"C"}}, {"int", {"F", "identifier", "G", "L"}}, {"float", {"F", "identifier", "G", "L"}},{"",{"$"}}}},
    {"A", {{"cout", {"cout", "<<", "E", "L"}}}},
    {"B", {{"cin", {"cin", ">>", "identifier", "L"}}}},
    {"C", {{"if", {"if", "(", "Q", ")", "S", "I"}}}},
    {"D", {{"==", {"=="}}, {">=", {">="}}, {"<=", {"<="}}, {"!=", {"!="}}, {">", {">"}}, {"<", {"<"}}}},
    {"E", {{"''", {"''"}}, {"\"\"", {"\"\""}}, {"identifier", {"identifier"}}, {"constant", {"constant"}}}},
    {"F", {{"int", {"int"}}, {"float", {"float"}}}},
    {"G", {{"=", {"=", "constant"}}, {";", {"epsilon"}}}}, 
    {"I", {{"else", {"else", "I","S","I"}},{"else",{"I"}},{"if", {"if", "(", "Q", ")"}}, {"cout",{"A"}},{"cin", {"B"}}, {"int", {"F", "identifier", "G", "L"}}, {"float", {"F", "identifier", "G", "L"}},{"",{"$"}}}},
    {"L", {{";", {";"}}}},
    {"O", {{"identifier", {"identifier"}}, {"constant", {"constant"}}}},
    {"Q", {{"identifier", {"O", "D", "O"}}, {"constant", {"O", "D", "O"}}}},
};

bool isTerminal(const string &symbol)
{
    // Check if the symbol is a terminal
    return symbol == "constant" || symbol == "''" || symbol == "\"\"" || symbol == "==" ||
    	symbol == "cin" || symbol == "if" || symbol == "else" || symbol == "int" ||
        symbol == ">=" || symbol == "<=" || symbol == "!=" || symbol == ">" ||
        symbol == "<" || symbol == "{" || symbol == "}" || symbol == ";" ||
        symbol == "<<" || symbol == ">>" || symbol == "=" || symbol == "cout" ||
        symbol == "float" || symbol == "identifier" || symbol == "(" || symbol == ")" || symbol == "$";
}

void LL1(const vector<pair<string, string>> &tokens)
{
    stack<string> parseStack;

    parseStack.push("$"); // Push the end-of-input marker
    parseStack.push("S");
    
	int index = 0;
    while (!parseStack.empty())
    {
        string topSymbol = parseStack.top();
    sk:
        parseStack.pop();
        
        cout << "current Symbol :" << topSymbol << endl;

        if (isTerminal(topSymbol))
        {
            if (topSymbol == "$")
            {

                if (index == tokens.size())
                {

                    cout << "Parsing successful" << endl;
                }
                else if (topSymbol == "$")
                {
                    cout << "successful" << endl;
                    parseStack.push("$");
                    parseStack.push("S");
                    topSymbol = parseStack.top();
                    goto sk;
                }
                else
                {
                    cout << "Syntax error: Incomplete input" << endl;
                    return;
                }
            }

            else
            {

                string token = tokens[index].first;
                if (topSymbol == "identifier" && isIdentifier(token))
                {

                    topSymbol = token;
                }
                else if (topSymbol == "constant" && isConstant2(token))
                {
                    topSymbol = token;
                }

                if (topSymbol == token)
                {
                    // Matched terminal symbol
                    index++;
                }
                
                else
                {
                
                    return;
                }
            }
        }
        else if (parsingTable.find(topSymbol) != parsingTable.end())
        {

            string token = tokens[index].first;

            unordered_map<string, vector<string>> production = parsingTable[topSymbol];

            if (production.find(token) != production.end())
            {
                // Apply production by pushing symbols in reverse order
                vector<string> productionSymbols = production[token];

                for (int i = productionSymbols.size() - 1; i >= 0; --i)
                {
                    string symbol = productionSymbols[i];

                    if (symbol != "epsilon")
                    {
                        parseStack.push(symbol);
                    }
                }
            }
            else
            {
                cout << "Syntax error: Unexpected token " << token << endl;
                return;
            }
        }

        else
        {

            cout << "Syntax error: Invalid symbol '" << topSymbol << "'" << endl;
            return;
        }
    }
}

void addToTokensArray(string token, string type)
{
    tokensArray.push_back(make_pair(token, type));
}

void addToSymbolTable(const string &identifier, map<string, string> &symbolTable)
{
    symbolTable[identifier] = "identifier"; // Assuming "identifier" is the type for identifiers
}

void LA(const vector<Token> &tokensArray)
{
    for (int i = 0; i < tokensArray.size(); i++)
    {
        string token = tokensArray[i].first;
        string type = tokensArray[i].second;
        cout << "Token: " << token << " \t Type: " << type << endl;
        cout << "Total tokens are :" << ::count++ << endl;
    }
}

void symbolTableAcessPoint(const map<string, string> &symbolTable)
{
    cout << "Identifiers \t Type " << endl;
    for (const auto &entry : symbolTable)
    {
        cout << entry.first <<"\t "<< entry.second<<"\t "<<endl;
    }
    cout << endl << endl;
    
    
}

void semanticAnalyzer(const vector<pair<string, string>> &tokens)
{
    unordered_set<string> declaredVariables;

    for (const auto &token : tokens)
    {
        string lexeme = token.first;
        string tokenType = token.second;

        if (tokenType == "Keyword")
        {
            // Handle variable declaration
            if (lexeme == "int" || lexeme == "float")
            {
                // Check the next token for an identifier
                size_t nextIndex = &token - &tokens[0] + 1;

                string variableName = tokens[nextIndex].first;
                if (declaredVariables.find(variableName) != declaredVariables.end())
                {
                    cout << "Semantic error: Variable '" << variableName << "' has already been declared" << endl;
                }
                else
                {
                    declaredVariables.insert(variableName);
                }
            }
        }
        else if (isIdentifier2(tokenType)==true)
        {
            // Check if the identifier has been declared
            if (declaredVariables.find(lexeme) == declaredVariables.end())
            {
                cout << "Semantic error: Variable '" << lexeme << "' has not been declared" << endl;
            }
        }
    }
}
void read() {
    ifstream abdul_file;
    abdul_file.open("abdul.txt");
    isAccepted(abdul_file);
    abdul_file.close();
}

void translate() {
	cout << "\n*************************TOKENS LIST************************** \n\n" << endl;
	LA(tokensArray);
	cout<<endl<<endl;
	//SYA();
	//SEA();
}

int main()
{
	read();
    translate();
    
    

    // acessing token and puting in symbol table
    
    
    
    
    cout << "\n*************************SYMBOL TABLE*************************** \n\n" << endl;
    symbolTableAcessPoint(symbolTable);

    cout << "\n*************************SYNTAX ANALYSER*************************** \n\n" << endl;
    
    LL1(tokensArray);
    cout << "\n*************************SEMENTIC ANALYSER*************************** \n\n" << endl;
	semanticAnalyzer(tokensArray);
    return 0;
}