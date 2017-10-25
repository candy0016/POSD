#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <string>
#include "atom.h"
#include "number.h"
#include "struct.h"

#include<iostream>

using namespace std;

class Variable: public Term{
public:
  Variable(string s):_symbol(s), _value(s){}
  string const _symbol;

  string value(){
      if(ptr!=nullptr){
            _value = ptr->value();
            return _value;
      }
      else if(lptr!=nullptr){
            _value = lptr->value();
            return _value;
      }
      else return _value;
}
  string symbol() const{
    return _symbol;
  }
  bool get_assign() { return this->_assignable; }
  int getTerm() { return 3; }
  void setValue(string s) { this->_value = s; }
  void setTemp(Term *t) { this->temp = t; }
  vector<Term *> *getTemp() { return &tVec; }
  vector<Term *> *get_args() {}


  bool match( Term & term ){
        if(term.getTerm()==1 || term.getTerm()==2){
            if(_assignable){
                _value = term.symbol() ;
                _assignable = false;

                if(!tVec.empty()){
                    for(int i=0; i<tVec.size(); i++){
                        tVec[i]->setValue(term.symbol());
                    }
                }
                return true;
            }
            else{
                if(_value == term.symbol()) return true;
                else return false;
            }


        }
        else if(term.getTerm()==3){
            if((this->value().compare(term.value()) == 0) && !term.get_assign() && !this->get_assign() ) return true;
            else if(   ((!term.get_assign()) && this->get_assign()) || ((term.get_assign()) && !this->get_assign()) || ((term.get_assign()) && this->get_assign())){
                if( term.get_assign() && this->get_assign() ){
                    this->setValue(term.value());
                }

                if(!term.get_assign()){
                    this->setValue(term.value());
                    for(int a=0; a<tVec.size(); a++){
                        tVec[a]->setValue(term.value());
                    }
                }
                this->tVec.push_back(&term);
                term.getTemp()->push_back(this);
                for(int i=0; i<tVec.size(); i++){
                    if(&term!=tVec[i]){
                        tVec[i]->getTemp()->push_back(&term);
                    }
                }
                for(int j=0; j<term.getTemp()->size(); j++){
                    if(this!=(*term.getTemp())[j]){
                        (*term.getTemp())[j]->getTemp()->push_back(this);
                    }
                }
                for(int k=0; k<tVec.size(); k++){
                    if(tVec[k] != &term){
                        term.getTemp()->push_back(tVec[k]);
                    }
                }
                for(int l=0; l<term.getTemp()->size(); l++){
                    if((*term.getTemp())[l] != this){
                        tVec.push_back( (*term.getTemp())[l] );
                    }
                }
                return true;
            }
            else return false;
        }
        else if(term.getTerm()==4){
            ptr = &term;
            return true;
        }
        else if(term.getTerm()==5){
            if(this->get_assign()) {
                for(int i=0; i<term.get_args()->size(); i++){
                    if(this == (*term.get_args())[i]) return false;
                }
                lptr = &term;
                return true;
            }
            else return false;
        }

        else return false;

  }


private:
  string _value;
  bool _assignable = true;
  Term *temp, *ptr = nullptr, *lptr = nullptr;
    vector<Term *> tVec;  //X is same with which variable
};

#endif
