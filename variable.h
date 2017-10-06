#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using std::string;

class Atom;
class Number;

class Variable{
private:
  string _value, s1, s2;
  bool _assignable = true;

public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }
  string symbol(){ return _symbol; }

  void set_assign_false() { this->_assignable = false; }
  bool get_assign() { return this->_assignable; }
  void setValue(string s) { this->_value = s; }



  bool match(Atom &A);
  bool match(Number &N);


};

#endif
