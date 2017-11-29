#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
using namespace std;
//using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  Node *expressionTree(){
    return _expressionTree;
  }

  void matchings(){
    Term *term = createTerm();
    if(term != nullptr){
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == '=' || _currentToken == ',' || _currentToken == ';') {
        if (_currentToken == '=')
        {
          Node *left = new Node(TERM, _terms.back(), nullptr, nullptr);
          _terms.push_back(createTerm());
          Node *right = new Node(TERM, _terms.back(), nullptr, nullptr);
          Node * root = new Node(EQUALITY, nullptr, left, right);
          _expressionTree = root;
        }
        else if (_currentToken == ',')
        {
          Node *left = _expressionTree;
          matchings();
          Node * root = new Node(COMMA, nullptr, left, expressionTree());
          _expressionTree = root;
          Update();
        }
        else if (_currentToken == ';')
        {
          _indexStart = _terms.size();
          Node *left = _expressionTree;
          matchings();
          Node * root = new Node(SEMICOLON, nullptr, left, expressionTree());
          _expressionTree = root;
        }
      }
    }
    if (symtable.back().first == ".")
      symtable.pop_back();
  }

void Update(){
  for(int i = _indexStart; i < _terms.size() ; i++){
    Variable * var = dynamic_cast<Variable*>(_terms[i]);
    if(var!=nullptr){
      for(int j = _indexStart; j < _terms.size() ; j++){
        Struct * s = dynamic_cast<Struct*>(_terms[j]);
        if (s != nullptr && s->isContain(var->symbol()))
        {
          var->match(*(s->findBySymbol(var->symbol())));
        }
        else if (var->symbol() == _terms[j]->symbol() && j > i)
          var->match(*(_terms[j]));
      }
    }
  }

}


private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken, isCOMMA=0, _indexStart=0;
  Node *_expressionTree;
};
#endif

