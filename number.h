#ifndef NUMBER_H
#define NUMBER_H

#include <string>

using std::string;

class Atom;
class Variable;

class Number {
private:
    string _symbol, _value;
    bool sFlag, vFlag;
    bool assignFlag = false;
    string s1, s2;

public:
    Number (int num):_value(std::to_string(num)), _symbol(std::to_string(num)), sFlag(false), vFlag(true) {}
    Number (string name):_symbol(name), _value(name), sFlag(true), vFlag(false) {}
    string symbol() { return _symbol; }
    string value() { return _value; }

    bool match(Atom &A);
    bool match(Variable &V);
    bool match(Number &N);

};

#endif
