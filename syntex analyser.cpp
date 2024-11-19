#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

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

    // Print the parsing table
    for (const auto &entry : parsingTable)
    {
        std::cout << entry.first << " -> ";
        for (const auto &item : entry.second)
        {
            std::cout << item.first << " [";
            for (const auto &action : item.second)
            {
                std::cout << action << " ";
            }
            std::cout << "] ";
        }
        std::cout << std::endl;
    }

    return 0;
}
