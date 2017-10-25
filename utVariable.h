#ifndef UTVARIABLE_H
#define UTVARIABLE_H
#include "variable.h"
#include "struct.h"
#include<iostream>
#include<vector>

using namespace std;

TEST(Variable, constructor){
  Variable X("X");
  ASSERT_EQ("X", X._symbol);
}

TEST(Variable , matching){
  Atom tom("tom");
  Variable X("X");
  X.match(tom);
  ASSERT_EQ( "tom", X.value());
}
TEST (Variable , haveValue){
  Atom tom ("tom");
  Atom jerry ("jerry");
  Variable X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(jerry));
}

// ?- X=2.7182.
// X=2.7182
TEST(Variable , numE_to_varX){
    Variable X("X");
    Number E(2.7182);
    X.match(E);
    ASSERT_EQ( "2.7182", X.value());
}

// ?- X=Y, X=1.
// Y=1
TEST (Variable, varY_to_varX_and_num1_to_varX) {
    Variable X("X");
    Variable Y("Y");
    Number E(1);
    X.match(Y);
    X.match(E);
    //ASSERT_EQ( "1", X.value());
    ASSERT_EQ( "1", Y.value());

}

// ?- X=Y, Y=1.
// X=1
TEST (Variable, varY_to_varX_and_num1_to_varY) {
    Variable X("X");
    Variable Y("Y");
    Number E(1);
    X.match(Y);
    Y.match(E);
    ASSERT_EQ( "1", X.value());
}

// ?- X=X, X=1.
// X=1
TEST (Variable, varX_match_varX_and_num1_to_varX) {
    Variable X("X");
    Number E(1);
    X.match(X);
    X.match(E);
    ASSERT_EQ( "1", X.value());
}

// ?- Y=1, X=Y.
// X=1
TEST (Variable, num1_to_varY_and_varX_match_varY) {
    Variable X("X");
    Variable Y("Y");
    Number E(1);
    Y.match(E);
    X.match(Y);
    ASSERT_EQ( "1", X.value());
}

// ?- X=Y, Y=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varY_to_varX) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Number E(1);
    X.match(Y);
    /*cout<<"X.tVec.size 1----------"<<X.getTemp()->size()<<endl;
    cout<<"Y.tVec.size 1----------"<<Y.getTemp()->size()<<endl;
    cout<<"Z.tVec.size 1----------"<<Z.getTemp()->size()<<endl<<endl;*/
    Y.match(Z);
    /*cout<<"X.tVec.size 2----------"<<X.getTemp()->size()<<endl;
    cout<<"Y.tVec.size 2----------"<<Y.getTemp()->size()<<endl;
    cout<<"Z.tVec.size 2----------"<<Z.getTemp()->size()<<endl<<endl;*/
    Z.match(E);
    /*cout<<"X.tVec.size 3----------"<<X.getTemp()->size()<<endl;
    cout<<"Y.tVec.size 3----------"<<Y.getTemp()->size()<<endl;
    cout<<"Z.tVec.size 3----------"<<Z.getTemp()->size()<<endl<<endl;*/
    ASSERT_EQ( "1", X.value());
    ASSERT_EQ( "1", Y.value());
    ASSERT_EQ( "1", Z.value());
}

// ?- X=Y, X=Z, Z=1
// X=1, Y=1, Z=1
TEST (Variable, num1_to_varZ_to_varX_and_varY_to_varX) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Number E(1);
    X.match(Y);
    X.match(Z);
    Z.match(E);
    ASSERT_EQ( "1", X.value());
    ASSERT_EQ( "1", Y.value());
    ASSERT_EQ( "1", Z.value());
}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(X)"
TEST (Variable, Struct1) {
    Variable X("X");
    Variable Y("Y");
    vector<Term *> v = {&X};
    Struct s(Atom("s"), v);
    Y.match(s);
    ASSERT_EQ( "Y", Y.symbol());
    ASSERT_EQ( "s(X)", Y.value());

}

// Give there is a Struct s contains Variable X
// And another Variable Y
// When Y matches Struct s
// And X matches Atom "teddy"
// Then #symbol() of Y should return "Y"
// And #value() of Y should return "s(teddy)"
TEST (Variable, Struct2) {
    Atom a("teddy");
    Variable X("X");
    Variable Y("Y");
    vector<Term *> v = {&X};
    Struct s(Atom("s"), v);
    //cout<<"--------s.value() 1 = "<<s.value()<<endl;
    Y.match(s);
    X.match(a);
    //cout<<"--------s.value() 2 = "<<s.value()<<endl;
    ASSERT_EQ( "Y", Y.symbol());
    ASSERT_EQ( "s(teddy)", Y.value());
}



#endif
