#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
#include <stack>
using namespace std;


#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "exp.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(), _indexStart(0){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if (token == VAR)
    {
      for (int i = _indexStart; i < _varTable.size(); i++)
        if (symtable[_scanner.tokenValue()].first == _varTable[i]->symbol())
          return _varTable[i];
      Variable *variable = new Variable(symtable[_scanner.tokenValue()].first);
      _varTable.push_back(variable);
      return variable;
    }
    else if (token == NUMBER)
      return new Number(_scanner.tokenValue());
    else if (token == ATOM || token == ATOMSC)
    {
      Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
      if (_scanner.currentChar() == '(')
        return structure();
      else
        return atom;
    }
    else if (token == '[')
      return list();
    else
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
    } 
    else if (_currentToken == ';')
      throw string("Unbalanced operator");
    else {
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
    } 
    else if (_currentToken == ';')
      throw string("Unbalanced operator");
    else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  Node *expressionTree(){
    return _expressionTree;
  }

/*
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

}*/

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


Exp *getExpressionTree() { return _expStack.top(); }

Exp *buildExpression()
{
    if (_scanner.getBuffer().find(";.") != string::npos)
      throw string("Unexpected ';' before '.'");
    if (_scanner.getBuffer().find(",.") != string::npos)
      throw string("Unexpected ',' before '.'");
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.')
      throw string("Missing token '.'");
    return _expStack.top();
}

void disjunctionMatch()
{
    conjunctionMatch();
    restConjunctionMatch();
}

void restDisjunctionMatch()
{
    if (_scanner.currentChar() == ';')
    {
      _indexStart = _varTable.size();
      createTerm();
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
};

void conjunctionMatch()
{
    Term *left = createTerm();
    if (createTerm() == nullptr && _currentToken == '=')
    {
      Term *right = createTerm();
      _expStack.push(new MatchExp(left, right));
    }
    else
      throw string(left->symbol() + " does never get assignment");
}

void restConjunctionMatch()
{
    if (_scanner.currentChar() == ',')
    {
      createTerm();
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
}



  vector<Term *> _terms;
  vector<Variable *> _varTable;
  Scanner _scanner;
  int _currentToken, isCOMMA=0, _indexStart=0;
  Node *_expressionTree;
  stack<Exp*> _expStack;
};




#endif

