#include "atom.h"
#include "variable.h"
#include "number.h"

#include <string>

#include <iostream>
using namespace std;

bool Number::match(Atom &A){
    return false;
}


bool Number::match(Variable &V){
    if(!assignFlag && V.get_assign()){
        assignFlag = true;
        V.setValue(this->value());
        V.set_assign_false();
        return true;
    }
    else{
        s1 = this->value();
        s2 = V.value();
        if(s1 == s2) return true;
        else return false;
    }

}

bool Number::match(Number &N){
    if(vFlag){
        if(this->value().compare(N.value()) == 0) return true;
        else return false;
    }
    else return false;
}


