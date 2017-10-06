#include "atom.h"
#include "variable.h"
#include "number.h"

#include <string>

#include <iostream>
using namespace std;

bool Variable::match( Atom &atom ){
    if(_assignable){
      _value = atom._symbol ;
      _assignable = false;
      return true;
    }
    else{
        if(_value == atom._symbol) return true;
        else return false;
    }
  }

bool Variable::match( Number &N ){
    if(_assignable){
      _value = N.value() ;
      _assignable = false;
      return true;
    }
    else{
        if(_value == N.value()) return true;
        else return false;
    }
  }

bool Variable::match(Variable &V){
    if(this->value().compare(V.value()) == 0) return true;
    else return false;

}
