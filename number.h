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
    Number *ptr1, *ptr2;
    bool assignFlag = false;
    string s1, s2;

public:
    Number (int num):_value(std::to_string(num)), _symbol(std::to_string(num)), sFlag(false), vFlag(true) {}
    Number (string name):_symbol(name), _value(name), sFlag(true), vFlag(false) {}
    string symbol() { return _symbol; }
    string value() { return _value; }

    bool match(Atom *A);
    bool match(Variable *V);
    bool match(Number *N);
    bool match(Atom A);
    bool match(Variable V);
    bool match(Number N);

    /*bool match(int compareN){
        _com = std::to_string(compareN);
        if (_value.compare(_com)==0) { return true; }
        else return false;
    }
    bool match(string _comS){
        if (_symbol.compare(_comS)==0) { return true; }
        else return false;
    }
    bool match(Variable V){
        if(_symbol.compare("")==0){
            if (V.match(_value)) { return true; }
            else return false;
        }
        else{
            if (V.match(_symbol)) { return true; }
            else return false;
        }
    }*/



};

#endif
