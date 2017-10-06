#include "atom.h"
#include "variable.h"
#include "number.h"

#include <string>

#include <iostream>
using namespace std;

bool Variable::match( Atom *atom ){
    if(_assignable){
      _value = atom->_symbol ;
      _assignable = false;
      this->Aptr = atom;
      //cout<<"the value of Aptr first match tom: "<<Aptr<<endl;
      //cout<<"the value of atom first match tom: "<<atom<<endl;
      return true;
    }
    else{
        //cout<<"the value of Aptr second match tom: "<<Aptr<<endl;
        //cout<<"the value of atom second match tom: "<<atom<<endl;
        if(Aptr == atom) return true;
        else return false;
    }
  }

bool Variable::match( Number *N ){
    if(_assignable){
      _value = N->value() ;
      _assignable = false;
      this->Nptr = N;
      return true;
    }
    else{
        if(Nptr == N) return true;
        else return false;
    }
  }



bool Variable::match(Atom A){
    if(this->_assignable){
      this->_value = A._symbol ;
      this->_assignable = false;
      this->setX(_value);
      return true;
    }
    else{
        if(this->getX().compare(A._symbol)==0) return true;
        else return false;
    }
}

bool Variable::match(Number N){
    if(this->_assignable){
      this->_value = N.value() ;
      this->_assignable = false;
      this->setX(_value);
      return true;
    }
    else{
        if(this->getX().compare(N.value())==0) return true;
        else return false;
    }
}
