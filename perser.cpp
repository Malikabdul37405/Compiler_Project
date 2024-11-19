#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class ParsingTableEntry
{
public:
    string non_terminal;
    string terminal;
    string production_rule;
    ParsingTableEntry *next;

    ParsingTableEntry(const string &nt, const string &t, const string &pr)
        : non_terminal(nt), terminal(t), production_rule(pr), next(nullptr) {}
};

class ParsingTable
{
private:
    static const int SIZE = 10;
    ParsingTableEntry *table[SIZE];

    size_t customHash(const string &nt, const string &t)
    {
        return hash<string>{}(nt + t) % SIZE;
    }

public:
    ParsingTable()
    {
        for (int i = 0; i < SIZE; ++i)
        {
            table[i] = nullptr;
        }
    }

    void insert(const string &non_terminal, const string &terminal, const string &production_rule)
    {
        size_t index = customHash(non_terminal, terminal);
        ParsingTableEntry *new_entry = new ParsingTableEntry(non_terminal, terminal, production_rule);

        if (table[index] == nullptr)
        {
            table[index] = new_entry;
        }
        else
        {
            ParsingTableEntry *current = table[index];
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = new_entry;
        }
    }

    string lookup(const string &non_terminal, const string &terminal)
    {
        size_t index = customHash(non_terminal, terminal);
        ParsingTableEntry *current = table[index];
        while (current != nullptr)
        {
            if (current->non_terminal == non_terminal && current->terminal == terminal)
            {
                return current->production_rule;
            }
            current = current->next;
        }
        return "";
    }
};

bool isKeyword(const string &token)
{
    static unordered_map<string, bool> keywords = {
        {"int", true},
        {"float", true},
        {"if", true},
        {"else", true},
        {"cin", true},
        {"cout", true},
        // Add more keywords as needed
    };

    return keywords.count(token) > 0;
}

bool isIdentifier(const string &token)
{
    if (token.empty() || isdigit(token[0]))
        return false;

    for (char c : token)
    {
        if (!isalnum(c) && c != '_')
            return false;
    }

    return true;
}

bool isConstant(const string &token)
{
    for (char c : token)
    {
        if (!isdigit(c))
            return false;
    }

    return true;
}

int main()
{
    ParsingTable parsing_table;
    parsing_table.insert("S", "cout", "A");
    parsing_table.insert("S", "cin", "B");
    parsing_table.insert("S", "if", "C");
    parsing_table.insert("A", "cout", "cout << M E L");
    parsing_table.insert("B", "cin", "cin >> N U L");
    parsing_table.insert("C", "if", "if P Q R X S K I");
    parsing_table.insert("X", "if", "if P Q R X");
    parsing_table.insert("C", "(", "C");
    parsing_table.insert("E", "'", "'");                   // Updated rule for single quotes
    parsing_table.insert("E", "\"", "\"");                 // Updated rule for double quotes
    parsing_table.insert("E", "identifier", "identifier"); // Updated rule for identifier
    parsing_table.insert("E", "constant", "constant");
    parsing_table.insert("F", "int", "int");
    parsing_table.insert("F", "float", "float");
    parsing_table.insert("G", "ε", "ε");
    parsing_table.insert("G", "T", "O L");
    parsing_table.insert("I", "else", "else X S K I");
    parsing_table.insert("I", "ε", "ε");
    parsing_table.insert("J", "{", "{");
    parsing_table.insert("K", "}", "}");
    parsing_table.insert("L", ";", ";");
    parsing_table.insert("M", "ε", "ε");
    parsing_table.insert("M", "<<", "<<");
    parsing_table.insert("N", "ε", "ε");
    parsing_table.insert("N", ">>", ">>");
    parsing_table.insert("O", "ε", "ε");
    parsing_table.insert("O", "identifier", "Q");
    parsing_table.insert("Q", "constant", "O D O");
    parsing_table.insert("R", ")", ")");
    parsing_table.insert("T", "=", "=");
    parsing_table.insert("U", "identifier", "identifier");

    vector<string> tokens;

    string token;
    cout << "Enter tokens (separated by spaces): ";
    while (cin >> token)
    {
        tokens.push_back(token);

        // Check if the user wants to stop entering tokens
        if (token == "$")
            break;
    }

    for (const string &token : tokens)
    {
        string non_terminal = "S";
        string production_rule;

        if (isKeyword(token))
        {
            production_rule = parsing_table.lookup(non_terminal, token);
            if (!production_rule.empty())
            {
                cout << "Token: " << token << " => Production Rule: " << production_rule << endl;
            }
            else
            {
                cout << "Error: Invalid token - " << token << endl;
            }
        }
        else if (isIdentifier(token))
        {
            production_rule = parsing_table.lookup(non_terminal, "identifier");
            if (!production_rule.empty())
            {
                cout << "Token: " << token << " => Production Rule: " << production_rule << endl;
            }
            else
            {
                cout << "Error: Invalid token - " << token << endl;
            }
        }
        else if (isConstant(token))
        {
            production_rule = parsing_table.lookup(non_terminal, "constant");
            if (!production_rule.empty())
            {
                cout << "Token: " << token << " => Production Rule: " << production_rule << endl;
            }
            else
            {
                cout << "Error: Invalid token - " << token << endl;
            }
        }
        else if (token == "$")
        {
            break;
        }
        else
        {
            cout << "Error: Invalid token - " << token << endl;
        }
    }

    // Adding the cout << a; statement
    string non_terminal = "S";
    string terminal = "cout";
    string production_rule = parsing_table.lookup(non_terminal, terminal);
    if (!production_rule.empty())
    {
        cout << "Token: cout => Production Rule: " << production_rule << endl;
    }

    terminal = "a";
    production_rule = parsing_table.lookup(non_terminal, "identifier");
    if (!production_rule.empty())
    {
        cout << "Token: a => Production Rule: " << production_rule << endl;
    }

    terminal = ";";
    production_rule = parsing_table.lookup(non_terminal, terminal);
    if (!production_rule.empty())
    {
        cout << "Token: " << terminal << " => Production Rule: " << production_rule << endl;
    }
    else
    {
        cout << "Error: Invalid token - " << terminal << endl;
    }

    return 0;
}
