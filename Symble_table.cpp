#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

// Tokenize the input code
std::vector<std::string> tokenize(const std::string &code)
{
    std::vector<std::string> tokens;
    std::string currentToken;

    for (char c : code)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
        }
        else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == '=' || c == '<' || c == '>')
        {
            if (!currentToken.empty())
            {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, c));
        }
        else
        {
            currentToken += c;
        }
    }

    if (!currentToken.empty())
    {
        tokens.push_back(currentToken);
    }

    return tokens;
}

bool parseTokens(const std::vector<std::string> &tokens, const std::unordered_map<char, std::unordered_map<std::string, std::vector<std::string>>> &parsingTable)
{
    std::stack<char> stack;
    stack.push('S'); // Push the starting symbol onto the stack

    size_t tokenIndex = 0;

    while (!stack.empty())
    {
        char currentSymbol = stack.top();
        stack.pop();

        if (tokenIndex >= tokens.size())
        {
            // No more tokens to process, but symbols remain on the stack
            return false;
        }

        std::string currentToken = tokens[tokenIndex];

        if (std::string(1, currentSymbol) == currentToken)
        {
            // Symbol matches the token, move to the next token
            tokenIndex++;
        }
        else if (parsingTable.find(currentSymbol) != parsingTable.end())
        {
            // Symbol has an entry in the parsing table
            if (parsingTable.at(currentSymbol).find(currentToken) != parsingTable.at(currentSymbol).end())
            {
                // Token has an entry for the current symbol in the parsing table
                const std::vector<std::string> &production = parsingTable.at(currentSymbol).at(currentToken);

                // Push the production rule onto the stack in reverse order
                for (auto it = production.rbegin(); it != production.rend(); ++it)
                {
                    if (*it != "epsilon")
                    {
                        stack.push((*it)[0]); // Push the symbol onto the stack
                    }
                }
            }
            else
            {
                // Token does not have an entry for the current symbol in the parsing table, indicating a parsing error
                return false;
            }
        }
        else
        {
            // Symbol does not have an entry in the parsing table, indicating a parsing error
            return false;
        }
    }

    // All tokens consumed and stack is empty, indicating successful parsing
    return tokenIndex == tokens.size();
}

int main()
{
    std::unordered_map<char, std::unordered_map<std::string, std::vector<std::string>>> parsingTable;

    // Initialize the parsing table
    parsingTable['S'] = {
        {"cout", std::vector<std::string>{"A"}},
        {"cin", std::vector<std::string>{"B"}},
        {"if", std::vector<std::string>{"C"}},
        {"int", std::vector<std::string>{"F", "identifier", "G", "L"}},
        {"float", std::vector<std::string>{"F", "identifier", "G", "L"}}};

    parsingTable['A'] = {
        {"cout", std::vector<std::string>{"M", "E", "L"}}};

    parsingTable['B'] = {
        {"cin", std::vector<std::string>{"N", "U", "L"}}};

    parsingTable['C'] = {
        {"if", std::vector<std::string>{"P", "Q", "R", "J", "S", "K", "I"}}};

    parsingTable['D'] = {
        {"==", std::vector<std::string>{}},
        {">=", std::vector<std::string>{}},
        {"<=", std::vector<std::string>{}},
        {"!=", std::vector<std::string>{}},
        {">", std::vector<std::string>{}},
        {"<", std::vector<std::string>{}}};

    parsingTable['E'] = {
        {"'", std::vector<std::string>{}},
        {"\"", std::vector<std::string>{}},
        {"identifier", std::vector<std::string>{}},
        {"constant", std::vector<std::string>{}}};

    parsingTable['F'] = {
        {"int", std::vector<std::string>{}},
        {"float", std::vector<std::string>{}}};

    parsingTable['G'] = {
        {"epsilon", std::vector<std::string>{}},
        {"T", std::vector<std::string>{"O", "L"}}};

    parsingTable['I'] = {
        {"else", std::vector<std::string>{"X", "J", "S", "K", "I"}},
        {"epsilon", std::vector<std::string>{}}};

    parsingTable['J'] = {
        {"{", std::vector<std::string>{}}};

    parsingTable['K'] = {
        {"}", std::vector<std::string>{}}};

    parsingTable['L'] = {
        {";", std::vector<std::string>{}}};

    parsingTable['M'] = {
        {"<<", std::vector<std::string>{}}};

    parsingTable['N'] = {
        {">>", std::vector<std::string>{}}};

    parsingTable['O'] = {
        {"identifier", std::vector<std::string>{}},
        {"constant", std::vector<std::string>{}}};

    parsingTable['P'] = {
        {"(", std::vector<std::string>{}}};

    parsingTable['Q'] = {
        {"identifier", std::vector<std::string>{}},
        {"constant", std::vector<std::string>{}}};

    parsingTable['R'] = {
        {")", std::vector<std::string>{}}};

    parsingTable['T'] = {
        {"=", std::vector<std::string>{}}};

    parsingTable['U'] = {
        {"identifier", std::vector<std::string>{}}};

    parsingTable['X'] = {
        {"if", std::vector<std::string>{"P", "Q", "R"}},
        {"epsilon", std::vector<std::string>{}}};

    std::string code;
    std::cout << "Enter the code: ";
    std::getline(std::cin, code);

    std::vector<std::string> tokens = tokenize(code);

    if (parseTokens(tokens, parsingTable))
    {
        std::cout << "Parsing successful!" << std::endl;
    }
    else
    {
        std::cout << "Parsing error occurred." << std::endl;
    }

    return 0;
}
/*  string production = parsingTable[symbol][token]; // Access the parsing table using char and string keys
           if (!production.empty())
           {
               // Apply production by pushing symbols in reverse order
               for (auto it = production.rbegin(); it != production.rend(); ++it)
               {
                   if (*it != '') // Compare with string instead of character constant
                       parseStack.push(string(1, *it));
               }
           }
           else
           {
               cout << "Syntax error" << endl;
               return;
           }
       }
   }

   if (currentIndex == input.length())
   {
       cout << "Parsing successful" << endl;
   }
   else
   {
       cout << "Syntax error" << endl;
   } */
void LL1Parser(const std::string &input)
{
    std::stack<std::string> parseStack;
    parseStack.push("$"); // Push the end-of-input marker
    parseStack.push("S"); // Push the start symbol

    size_t currentIndex = 0;

    while (!parseStack.empty())
    {
        std::string topSymbol = parseStack.top();
        parseStack.pop();

        if (!isTerminal(topSymbol))
        {
            char symbol = topSymbol[0];                   // Get the first character of the top symbol
            string token = input.substr(currentIndex, 1); // Get the next input token
            if (S == parsingTable || S == "$")
            {
                if (A == token)
                {
                    parseStack.pop();
                    token = "";
                }
                else
                    ERROR();
            }
            else if ()
        }
    }
    unordered_map<char, unordered_map<string, string>> parsingTable = {
        {'S', {{"cout", "A"}, {"cin", "B"}, {"if", "C"}}},
        {'A', {{"cout", "coutMEL"}}},
        {'B', {{"cin", "cinNUL"}}},
        {'C', {{"if", "ifPQRJSKI"}}},
        {'D', {{"==", "=="}, {">=", ">="}, {"<=", "<="}, {"!=", "!="}, {">", ">"}, {"<", "<"}}},
        {'E', {{"'", "''"}, {"\"", "\" \""}, {"identifier", "identifier"}, {"constant", "constant"}}},
        {'F', {{"int", "int"}, {"float", "float"}}},
        {'G', {{"identifier", ""}, {"int", "TOL"}}},
        {'I', {{"else", "elseXJSKI"}}},
        {'J', {{"{", "{"}}},
        {'K', {{"}", "}"}}},
        {'L', {{";", ";"}}},
        {'M', {{"<<", "<<"}}},
        {'N', {{">>", ">>"}}},
        {'O', {{"identifier", "identifier"}, {"constant", "constant"}}},
        {'P', {{"(", "("}}},
        {'Q', {{"identifier", "ODO"}, {"constant", "ODO"}}},
        {'R', {{")", ")"}}},
        {'T', {{"=", "="}}},
        {'U', {{"identifier", "identifier"}}},
        {'X', {{"if", "ifPQR"}, {"else", ""}}}};

    bool isTerminal(const string &symbol)
    {
        // Check if the symbol is a terminal
        return symbol == "identifier" || symbol == "constant" ||
               symbol == "'" || symbol == "\"" ||
               symbol == "==" || symbol == ">=" || symbol == "<=" ||
               symbol == "!=" || symbol == ">" || symbol == "<" ||
               symbol == "{" || symbol == "}" || symbol == ";" ||
               symbol == "<<" || symbol == ">>" || symbol == "=" ||
               symbol == "cout" || symbol == "cin" || symbol == "if" ||
               symbol == "else" || symbol == "int" || symbol == "float" ||
               symbol == "(" || symbol == ")";
    }
}