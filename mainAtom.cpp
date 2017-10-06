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
    if(!this->assignFlag /*&& V.get_assign()*/){
        this->assignFlag = true;
        V.setX(this->_symbol);
        V.set_assign_false();
        return true;
    }
    else{
        s1 = this->_symbol;
        s2 = V.getX();
        if(s1.compare(s2)==0) return true;
        else return false;
    }
}