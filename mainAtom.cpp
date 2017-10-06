#include "atom.h"
#include "variable.h"
#include "number.h"

#include <string>

#include <iostream>
using namespace std;

bool Atom::match(Number &N){
    return false;
}


bool Atom::match(Variable &V){
    if(V.get_assign()){
        assignFlag = true;
        V.set_assign_false();
        return true;
    }
    else{
        s1 = this->_symbol;
        s2 = V.value();
        if(s1 == s2) return true;
        else return false;
    }

}

bool Atom::match(Atom &A){
    if(this->value().compare(A.value()) == 0) return true;
    else return false;

}
