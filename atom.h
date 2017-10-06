#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;

class Variable;
class Number;

class Atom {
public:
  Atom (string s):_symbol(s), _value(s) {}
  bool operator ==(Atom a) {return _symbol == a._symbol;}
  string _symbol, _value;

  bool match(Variable *V);
  bool match(Number *N);
  bool match(Variable V);
  bool match(Number N);

private:
    Atom *ptr1, *ptr2;
    bool assignFlag = false;

};

#endif
