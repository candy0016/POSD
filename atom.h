#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <sstream>
using std::string;

template <typename T> class Iterator;
class Term{
public:
  virtual string symbol() const {return _symbol;}
  virtual string value() const {return symbol();}
  virtual bool isAssignable() { return false; }

  virtual bool match(Term &term)
  {
    if (term.isAssignable())
      return term.match(*this);
    else
      return symbol() == term.value();
  }

  virtual Term *findBySymbol(string symbol)
  {
    if (symbol == this->symbol())
      return this;
    else
      return nullptr;
  }

  virtual Iterator<Term*> * createIterator();
protected:
  Term ():_symbol(""){}
  Term (string s):_symbol(s) {}
  Term(double db){
    std::ostringstream strs;
    strs << db;
    _symbol = strs.str();
  }
  string _symbol;
};

class Atom : public Term{
public:
  Atom(string s):Term(s) {}
};

class Number : public Term{
public:
  Number(double db):Term(db) {}
};

#endif
