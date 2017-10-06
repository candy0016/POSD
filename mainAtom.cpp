#include "atom.h"
#include "variable.h"
#include "number.h"

#include <string>

#include <iostream>
using namespace std;

bool Atom::match(Number *N){
    return false;
}


bool Atom::match(Variable *V){
    if(!assignFlag && V->get_assign()){
        assignFlag = true;
        V->setAptr(this);
        V->set_assign_false();
        return true;
    }
    else{
        ptr1 = this;
        ptr2 = V->getAptr();
        //cout<<ptr1<<"----------";
        //cout<<ptr2<<"----------";
        if(ptr1 == ptr2) return true;
        else return false;
    }

}


bool Atom::match(Number N){
    return false;
}

bool Atom::match(Variable V){
    this->match(&V);
}
