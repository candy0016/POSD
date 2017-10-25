#ifndef UTLIST_H
#define UTLIST_H

#include <string>
#include <iostream>
#include <exception>
using namespace std;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  vector<Term *> args;
  List l(args);
  EXPECT_EQ(string("[]"), l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
    Number n1(8128), n2(496);
    vector<Term *> args = {&n2, &n1};
    List l(args);
    EXPECT_EQ(string("[496, 8128]"), l.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
    Atom a1("terence_tao"), a2("alan_mathison_turing");
    vector<Term *> args = {&a1, &a2};
    List l(args);
    EXPECT_EQ(string("[terence_tao, alan_mathison_turing]"), l.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable X("X"), Y("Y");
    vector<Term *> args = {&X, &Y};
    List l(args);
    EXPECT_EQ(string("[X, Y]"), l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    Atom A2("tom");
    ASSERT_FALSE(A2.match(l));

}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    Number N2(8128);
    ASSERT_FALSE(N2.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    vector<Term *> args2 = {&X};
    Struct S(Atom("S"), args2);
    ASSERT_FALSE(S.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    Variable Y("Y");
    ASSERT_TRUE(Y.match(l));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    ASSERT_FALSE(X.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].--------------------
// true.
TEST(List, matchToSameListShouldSucceed) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    ASSERT_TRUE(l.match(l));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    Variable Y("Y");
    vector<Term *> args2 = {&N, &Y, &A};
    List l2(args2);
    ASSERT_TRUE(l2.match(l));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    Number N2(8128);
    vector<Term *> args2 = {&N, &N2, &A};
    List l2(args2);
    l2.match(l);
    ASSERT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Number N(496);
    Variable X("X");
    Atom A("terence_tao");
    vector<Term *> args = {&N, &X, &A};
    List l(args);

    Variable Y("Y");

    Y.match(l);
    Atom A2("alan_mathison_turing");
    X.match(A2);
    ASSERT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
}

// Example:---------------------------------------------------------
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args1 = {&f};
    List l1(args1);
    vector<Term *> args2 = {&l1, &s, &t};
    List l2(args2);

    EXPECT_EQ(string("[first]"), l2.head()->value());
    EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);

    EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
    EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
    vector<Term *> args;
    List l(args);

    try{
        l.head();
    }
    catch(exception &ex){
        EXPECT_STREQ("Accessing head in an empty list", ex.what());
    }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
    vector<Term *> args;
    List l(args);

    try{
        l.tail();
    }
    catch(exception &ex){
        EXPECT_STREQ("Accessing tail in an empty list", ex.what());
    }
}




#endif

