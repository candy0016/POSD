#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <sstream>
#include <vector>


using namespace std;

class Number: public Term {
private:
    string _symbol, _value;
    bool _assignable = false;
    string s1, s2;

public:
    Number (double num){
        stringstream ss;
        ss<<num;
        _symbol = ss.str();
        _value = _symbol;
    }
    string symbol() const{
        return _symbol;
    }
    string value() {
        return _value;
    }
    int getTerm() { return 2; }
    bool get_assign() { return _assignable; }
    void setValue(string s) { this->_symbol = s; }
    void setTemp(Term *t) {}
    vector<Term *> *getTemp() {}
    vector<Term *> *get_args() {}
};

#endif
