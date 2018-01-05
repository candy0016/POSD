#include "parser.h"
#include "scanner.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    string content, keyIn = "";
    Parser *parser;
    while (true)
    {
        do
        {
            if (keyIn == "")
                cout << "?- ";
            else
                cout << "|   ";
            getline(cin, content);
            if (content != "")
                while (content[0] == ' ')
                    content = content.substr(1, content.size() - 1);
            keyIn += content;
        } while (content == "" || keyIn.back() != '.');
        if (keyIn == "halt.")
            break;
        parser = new Parser(Scanner(keyIn));
        try
        {
            cout << parser->buildExpression()->getResult() << endl;
        }
        catch (string &msg)
        {
            cout << msg << endl;
        }
        keyIn = "";
    }
}