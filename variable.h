#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

using std::string;

class Atom;
class Number;

class Variable{
private:
  string _value;
  bool _assignable = true;
  Atom *Aptr = nullptr;
  Number *Nptr = nullptr;

public:
  Variable(string s):_symbol(s){}
  string const _symbol;
  string value(){ return _value; }
  string symbol(){ return _symbol; }
  void setAptr(Atom *A) { this->Aptr = A; }
  void setNptr(Number *N) { this->Nptr = N; }
  Atom *getAptr() { return this->Aptr; }
  Number *getNptr() { return this->Nptr; }
  void set_assign_false() { this->_assignable = false; }
  bool get_assign() { return this->_assignable; }

  bool match(Atom *A);
  bool match(Number *N);

  /*bool match( Atom atom ){
    bool ret = _assignable;
    if(_assignable){
      _value = atom._symbol ;
      _assignable = false;
      atom._var = _symbol;
    }
    return ret;
  }*/


};

#endif
