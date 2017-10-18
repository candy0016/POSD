#ifndef STRUCT_H
#define STRUCT_H

#include <vector>
#include <string>
//#include "variable.h"

using namespace std;

class Struct:public Term
{
public:
  Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) {
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom const & name() {
    return _name;
  }
  string symbol() const{
    string ret =_name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]-> symbol() + ", ";
    }
    ret += _args[_args.size()-1]-> symbol() + ")";
    return  ret;
  }

  string value() {
        string ret =_name.symbol() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]-> value() + ", ";
    }
    ret += _args[_args.size()-1]-> value() + ")";
    return  ret;
    }

  bool match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size()!= ps->_args.size())
        return false;
      for(int i=0;i<_args.size();i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;
    }
    return false;
  }


  int getTerm() { return 4; }
  bool get_assign() { return _assignable; }
  void setValue(string s) {}
  void setTemp(Term *t) {}
  vector<Term *> *getTemp() {}
  vector<Term *> *get_args() { return &_args; }



private:
  Atom _name;
  vector<Term *> _args;
  bool _assignable = false;

};

#endif
