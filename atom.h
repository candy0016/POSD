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
  string symbol() { return _symbol; }
  string value() { return _value; }

  bool match(Variable &V);
  bool match(Number &N);
  bool match(Atom &A);

private:
    bool assignFlag = false;
    string s1, s2;

};

#endif
