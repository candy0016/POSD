#ifndef UTTERM_H
#define UTTERM_H
#include "atom.h"
#include "variable.h"
#include "number.h"

#include <iostream>
using namespace std;

//test Number.value()
TEST (Number,ctor) {
	Number testNum(5);
 	ASSERT_EQ("5", testNum.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number testNum("N");
 	ASSERT_EQ("N", testNum.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number testNum1(25);
    Number testNum2(25);
    EXPECT_TRUE(testNum1.match(&testNum2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number testNum1(25);
    Number testNum2(0);
    EXPECT_FALSE(testNum1.match(&testNum2));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number testNum(25);
    Atom tom("tom");
    EXPECT_FALSE(testNum.match(&tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number testNum(25);
    Variable X("X");
    EXPECT_TRUE(testNum.match(&X));
}
//------------------------------------------------------
//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom tom("tom");
    Number testNum(25);
    EXPECT_FALSE(tom.match(&testNum));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom tom("tom");
    Variable X("X");
    EXPECT_TRUE(tom.match(&X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom tom("tom");
    Variable X("X");
    EXPECT_TRUE(tom.match(&X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Atom tom("tom");
    Atom jerry("jerry");
    Variable X("X");
    X.match(&jerry);
    EXPECT_FALSE(tom.match(&X));
}
//------------------------------------------------------
// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Variable X("X");
    Number N(5);
    EXPECT_TRUE(X.match(&N));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Variable X("X");
    Number N1(25);
    Number N2(100);
    X.match(&N1);
    EXPECT_FALSE(X.match(&N2));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Variable X("X");
    Number N(25);
    Atom tom("tom");
    X.match(&tom);
    EXPECT_FALSE(X.match(&N));

}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Variable X("X");
    Number N(25);
    Atom tom("tom");
    tom.match(&X);
    EXPECT_FALSE(N.match(&X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Variable X("X");
    Atom tom("tom");
    //cout<<"the first address of X: "<<&X<<endl;
    //cout<<"build the object tom: "<<&tom<<endl;
    X.match(&tom);
    //cout<<"the second address of X: "<<&X<<endl;
    //cout<<"first match tom: "<<&tom<<endl;
    EXPECT_TRUE(X.match(&tom));

}
#endif
