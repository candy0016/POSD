#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <vector>

using namespace std;


class Term{

public:
    virtual string symbol() const = 0;
    virtual string value() = 0;

    virtual bool match(Term & term) = 0;
    virtual int getTerm() = 0;
    virtual bool get_assign() = 0;
    virtual void setValue(string s) = 0;
    virtual void setTemp(Term *t) = 0;
    virtual vector<Term *> *getTemp() = 0;
    virtual vector<Term *> *get_args() = 0;
};

class Atom : public Term{

private:
  string _symbol,_value;
  bool _assignable = false;

public:
  Atom (string s):_symbol(s), _value(s) {}

  string symbol() const{
    return _symbol;
  }
  string value() {
    return _value;
  }

  bool match(Term & term) {
      if(term.getTerm()==1 || term.getTerm()==2) { return symbol() == term.symbol(); }
      else if(term.getTerm()==3){
        if(term.get_assign()){
            term.setValue(value());
            return true;
        }
        else{
            return value() == term.value();
        }
      }
      else if(term.getTerm()==4){ return false; }
      else return false;
    }

  int getTerm() { return 1; }
  bool get_assign() { return _assignable; }
  void setValue(string s) { this->_symbol = s; }
  void setTemp(Term *t) {}
  vector<Term *> *getTemp() {}
  vector<Term *> *get_args() {}
};


#endif
