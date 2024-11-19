unordered_map<string, unordered_map<string, vector<string>>> parsingTable = {
    {"S", {{"cout", {"A"}}, {"cin", {"B"}}, {"if", {"C"}}, {"int", {"F", "identifier", "G", "L"}}, {"float", {"F", "identifier", "G", "L"}}}},
    {"A", {{"cout", {"cout", "M", "E", "L"}}}},
    {"B", {{"cin", {"cin", "NUL"}}}},
    {"C", {{"if", {"if", "P", "Q", "R", "J", "S", "K", "I"}}}},
    {"D", {{"==", {"=="}}, {">=", {">="}}, {"<=", {"<="}}, {"!=", {"!="}}, {">", {">"}}, {"<", {"<"}}}},
    {"E", {{"'", {"''"}}, {"\"", {"\" \""}}, {"identifier", {"U"}}, {"constant", {"constant"}}}},
    {"F", {{"int", {"int"}}, {"float", {"float"}}}},
    {"G", {{"identifier", {"epsilon"}}, {"int", {"T", "O", "L"}}}},
    {"I", {{"else", {"else", "X", "J", "S", "K", "I"}}}},
    {"J", {{"{", {"{"}}}},
    {"K", {{"}", {"}"}}}},
    {"L", {{";", {";"}}}},
    {"M", {{"<<", {"<<"}}}},
    {"N", {{">>", {">>"}}}},
    {"O", {{"identifier", {"U"}}, {"constant", {"constant"}}}},
    {"P", {{"(", {"("}}}},
    {"Q", {{"identifier", {"O", "D", "O"}}, {"constant", {"O", "D", "O"}}}},
    {"R", {{")", {")"}}}},
    {"T", {{"=", {"="}}}},
    {"U", {{"identifier", {"identifier"}}}},
    {"X", {{"if", {"if", "P", "Q", "R"}}, {"else", {""}}}}};
    bool isTerminal(const string &symbol)
{
    // Check if the symbol is a terminal
    return symbol == "constant" || symbol == "'" || symbol == "\"" || symbol == "==" ||
           symbol == ">=" || symbol == "<=" || symbol == "!=" || symbol == ">" ||
           symbol == "<" || symbol == "{" || symbol == "}" || symbol == ";" ||
           symbol == "<<" || symbol == ">>" || symbol == "=" || symbol == "cout" ||
           symbol == "cin" || symbol == "if" || symbol == "else" || symbol == "int" ||
           symbol == "float" || symbol == "identifier" || symbol == "(" || symbol == ")";
}

void LL1Parser(const string &input)
{
    stack<string> parseStack;
    parseStack.push("$"); // Push the end-of-input marker
    parseStack.push("S"); // Push the start symbol

    size_t currentIndex = 0;

    while (!parseStack.empty())
    {
        string topSymbol = parseStack.top();
        parseStack.pop();

        if (isTerminal(topSymbol))
        {
            if (topSymbol == "$")
            {
                // Reached the end of input
                if (currentIndex == input.length())
                {
                    cout << "Parsing successful" << endl;
                }
                else
                {
                    cout << "Syntax error: Incomplete input" << endl;
                    return;
                }
            }
            else
            {
                // Skip consecutive spaces
                while (currentIndex < input.length() && input[currentIndex] == ' ')
                {
                    currentIndex++;
                }

                // Extract the token until the next space character
                size_t nextSpace = input.find(' ', currentIndex);
                if (nextSpace == string::npos)
                {
                    nextSpace = input.length(); // Reached the end of the input
                }

                string token = input.substr(currentIndex, nextSpace - currentIndex);

                if (topSymbol == token)
                {
                    // Matched terminal symbol
                    currentIndex = nextSpace; // Move to the next space character
                }
                else
                {
                    cout << "Syntax error: Unexpected terminal symbol '" << token << "'" << endl;
                    return;
                }
            }
        }
        else if (parsingTable.find(topSymbol) != parsingTable.end())
        {
            // Skip consecutive spaces
            while (currentIndex < input.length() && input[currentIndex] == ' ')
            {
                currentIndex++;
            }

            // Find the production for the next token
            size_t nextSpace = input.find(' ', currentIndex);
            if (nextSpace == string::npos)
            {
                nextSpace = input.length(); // Reached the end of the input
            }

            string token = input.substr(currentIndex, nextSpace - currentIndex);

            unordered_map<string, vector<string>> production = parsingTable[topSymbol];
            if (production.find(token) != production.end())
            {
                // Apply production by pushing symbols in reverse order
                vector<string> productionSymbols = production[token];
                for (int i = productionSymbols.size() - 1; i >= 0; --i)
                {
                    string symbol = productionSymbols[i];
                    parseStack.push(symbol);
                }
                currentIndex = nextSpace; // Move to the next space character
            }
            else
            {
                cout << "Syntax error: Unexpected token '" << token << "'" << endl;
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