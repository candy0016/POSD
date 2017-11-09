#ifndef LIST_H
#define LIST_H

#include "atom.h"
#include <string>
#include <vector>
#include <exception>
using std::vector;
using std::string;
using std::exception;

class List : public Term {
public:
  string symbol() const;
  string value();
  bool match(Term & term);

public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const;
  List * tail() const;


  int getTerm() { return 5; }
  bool get_assign() {}
  void setValue(string s) {}
  void setTemp(Term *t) {}
  vector<Term *> *getTemp() {}
  vector<Term *> *get_args() { return &_elements; }
  string arity(){}

private:
  vector<Term *> _elements;
  bool matchflag;

};

string List::symbol() const{
    string ret;
    if(_elements.size() == 0) {
        ret = "[]";
        return ret;
    }
    else {
        ret = "[";
        for(int i = 0; i < _elements.size() - 1 ; i++){
            ret += _elements[i]-> symbol() + ", ";
        }
        ret += _elements[_elements.size()-1]-> symbol() + "]";
        return  ret;
    }
}

string List::value(){
    string ret;
    if(_elements.size() == 0) {
        ret = "[]";
        return ret;
    }
    else {
        ret = "[";
        for(int i = 0; i < _elements.size() - 1 ; i++){
            ret += _elements[i]-> value() + ", ";
        }
        ret += _elements[_elements.size()-1]-> value() + "]";
        return  ret;
    }
}

bool List::match(Term & term){
    if(term.getTerm()==5){
        List * ps = dynamic_cast<List *>(&term);
        if (ps){
            if(_elements.size()!= ps->_elements.size())
                return false;
            for(int i=0;i<_elements.size();i++){
                if(! _elements[i]->match(*(ps->_elements[i])))
                    return false;
            }
            return true;
        }
        return false;

    }
    else if(term.getTerm()==3){
        if(term.value().compare(this->value()) ==0) { return true; }
        else if(term.get_assign()) { return true; }
        else { return false; }
    }
    else return false;


}
/*
class myexpception1: public exception{
    virtual const char* what() const throw()
    {
        return "Accessing head in an empty list";
    }
}myex1;

class myexpception2: public exception{
    virtual const char* what() const throw()
    {
        return "Accessing tail in an empty list";
    }
}myex2;*/

Term * List::head() const{
    if(_elements.size()==0){
        throw string("Accessing head in an empty list");
    }
    return this->_elements[0];
}

List * List::tail() const{
    if(_elements.size()==0){
        throw string("Accessing tail in an empty list");
    }
    vector<Term *> args;
    if(_elements.size()>1){
        for(int i=1; i<_elements.size(); i++){
            args.push_back(_elements[i]);
        }
    }
    List *l = new List(args);
    return l;

}




#endif
