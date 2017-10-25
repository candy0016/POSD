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
        if(this->get_args()->size()!=0 && term.get_args()->size()!=0){
            if(this->get_args()->size() == term.get_args()->size()){
                for(int i=0; i<this->get_args()->size(); i++){
                    if((*this->get_args())[i]->getTerm()==1 || (*this->get_args())[i]->getTerm()==2){
                        if((*term.get_args())[i]->getTerm()==1 || (*term.get_args())[i]->getTerm()==2) {
                            if(((*this->get_args())[i]->value().compare((*term.get_args())[i]->value())) != 0) { return false; }
                        }
                        else if((*term.get_args())[i]->getTerm()==3){
                            if((*term.get_args())[i]->get_assign()) { (*term.get_args())[i]->setValue((*this->get_args())[i]->value()); }
                            else{
                                if( (*this->get_args())[i]->value().compare((*term.get_args())[i]->value()) != 0) { return false; }
                            }
                        }
                    }
                    else if((*this->get_args())[i]->getTerm()==3){
                        if((*term.get_args())[i]->getTerm()==1 || (*term.get_args())[i]->getTerm()==2) {
                            if((*term.get_args())[i]->get_assign()){
                                (*this->get_args())[i]->setValue((*term.get_args())[i]->value());
                            }
                            else{
                                if( (*this->get_args())[i]->value().compare((*term.get_args())[i]->value()) != 0) { return false; }
                            }
                        }
                    }

                }
                return true;
            }
            else return false;
        }
        else return false;
    }
    else if(term.getTerm()==3){
        if(term.value().compare(this->value()) ==0) { return true; }
        else { return false; }
    }


}

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
}myex2;

Term * List::head() const{
    if(_elements.size()==0){
        throw myex1;
    }
    return this->_elements[0];
}

List * List::tail() const{
    if(_elements.size()==0){
        throw myex2;
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