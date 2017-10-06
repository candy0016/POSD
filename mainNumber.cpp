#include "atom.h"
#include "variable.h"
#include "number.h"

#include <string>

#include <iostream>
using namespace std;

bool Number::match(Atom *A){
    return false;
}


bool Number::match(Variable *V){
    if(!assignFlag && V->get_assign()){
        assignFlag = true;
        V->setNptr(this);
        V->set_assign_false();
        return true;
    }
    else{
        ptr1 = this;
        ptr2 = V->getNptr();
        if(ptr1 == ptr2) return true;
        else return false;
    }

}

bool Number::match(Number *N){
    if(vFlag){
        if(this->value().compare(N->value()) == 0) return true;
        else return false;
    }
    else return false;
}




bool Number::match(Atom A){
    return false;
}

bool Number::match(Variable &V){
    if(!this->assignFlag && V.get_assign()){
        //this->assignFlag = true;
        V.setX(this->symbol());
        V.set_assign_false();
        return true;
    }
    else{
        s1 = this->symbol();
        s2 = V.getX();
        if(s1.compare(s2)==0) return true;
        else return false;
    }
}

bool Number::match(Number N){
    this->match(&N);
}

