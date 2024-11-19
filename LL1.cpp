#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>
#include <sstream>

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parsingTable;

void initializeParsingTable()
{
    parsingTable["S"] = {{"cout", "coutStatement"}, {"cin", "cinStatement"}, {"if", "ifStatement"}, {"int", "variableDeclaration"}};
    parsingTable["coutStatement"] = {{"<<", "coutExpression"}};
    parsingTable["coutExpression"] = {{"\"", "literal"}, {"id", "variable"}};
    parsingTable["cinStatement"] = {{">>", "cinExpression"}};
    parsingTable["cinExpression"] = {{"id", "variable"}};
    parsingTable["ifStatement"] = {{"if", "condition", "then", "S", "else", "S"}};
    parsingTable["condition"] = {{"id", "variable"}, {"lit", "literal"}};
    parsingTable["variableDeclaration"] = {{"id", "idList"}};
    parsingTable["idList"] = {{"id", "idList"}, {",", "idList"}, {";", ""}};
}

bool isTerminal(const std::string &symbol)
{
    return parsingTable.find(symbol) == parsingTable.end();
}

bool parseLL1(const std::vector<std::string> &tokens)
{
    std::stack<std::string> stack;
    stack.push("$");
    stack.push("S");

    size_t index = 0;
    std::string currentToken = tokens[index];

    while (!stack.empty())
    {
        std::string top = stack.top();
        stack.pop();

        if (isTerminal(top))
        {
            if (top == currentToken)
            {
                index++;
                if (index < tokens.size())
                {
                    currentToken = tokens[index];
                }
                else
                {
                    currentToken = "$";
                }
            }
            else
            {
                std::cout << "Error: Expected '" << top << "', found '" << currentToken << "'." << std::endl;
                return false;
            }
        }
        else
        {
            if (parsingTable.find(top) != parsingTable.end() && parsingTable[top].find(currentToken) != parsingTable[top].end())
            {
                std::string production = parsingTable[top][currentToken];
                if (production != "")
                {
                    std::vector<std::string> productionTokens;
                    std::istringstream iss(production);
                    std::string token;
                    while (iss >> token)
                    {
                        productionTokens.push_back(token);
                    }
                    for (auto it = productionTokens.rbegin(); it != productionTokens.rend(); ++it)
                    {
                        stack.push(*it);
                    }
                }
            }
            else
            {
                std::cout << "Error: No production rule found for non-terminal '" << top << "' and input token '" << currentToken << "'." << std::endl;
                return false;
            }
        }
    }

    if (currentToken == "$")
    {
        std::cout << "Input successfully parsed." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Error: Input could not be fully parsed." << std::endl;
        return false;
    }
}

int main()
{
    initializeParsingTable();

    std::vector<std::string> tokens = {"cout", "<<", "\"Hello, world!\"", ";"};

    bool success = parseLL1(tokens);

    if (success)
    {
        // Further processing if parsing is successful
    }
    else
    {
        // Handle parsing errors
    }

    return 0;
}
