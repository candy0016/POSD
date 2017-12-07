#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include <vector>

/*
using namespace std;

class Number: public Term {
private:
    string _symbol, _value;
    bool _assignable = false;
    string s1, s2;

public:
    Number (double num){
        stringstream ss;
        ss<<num;
        _symbol = ss.str();
        _value = _symbol;
    }
    string symbol() const{
        return _symbol;
    }
    string value() {
        return _value;
    }

    bool match(Term & term) {
      if(term.getTerm()==1 || term.getTerm()==2) { return symbol() == term.symbol(); }
      else if(term.getTerm()==3){
        term.match(*this);
      }
      else if(term.getTerm()==4){ return false; }
      else if(term.getTerm()==5){ return false; }
      else return false;
    }

    int getTerm() { return 2; }
    bool get_assign() { return _assignable; }
    void setValue(string s) { this->_symbol = s; }
    void setTemp(Term *t) {}
    vector<Term *> *getTemp() {}
    vector<Term *> *get_args() {}
    int arity(){}
    void set_assign() {}
};*/

#endif
