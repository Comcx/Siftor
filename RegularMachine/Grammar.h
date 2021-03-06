#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Mix.h"
#include <vector>
#include <stack>
#include <list>
#include <map>

use module Mix;
use module Mix::Alias;
mix<Set t>
def Vector = std::vector<t>;
mix<Set t>
def Stack = std::stack<t>;
mix<Set t>
def LinkedList = std::list<t>;
mix<Set k, Set t>
  def Map = std::map<k, t>;

enum SymbolType {V_T, V_N, NONE};
struct Symbol {
  
  SymbolType type;
  String value;
  Symbol(SymbolType t, String s) {

    type = t;
    value = s;
  }
  Bool operator==(const Symbol &that) const {
				       
    return this->type  == that.type &&
           this->value == that.value; 
  }
  Bool operator!=(const Symbol &that) const {

    return !((*this) == that);
  }
  Bool operator<(const Symbol &that) const {

    return this->type == that.type &&
	   this->value < that.value;
  }
};
Symbol symbol(SymbolType, String);
Symbol symbol(String);
def Symbols = Vector<Symbol>;

def Seq = LinkedList<Symbol>;
Seq seq(String raw);

def Seqs = Vector<Seq>;
enum RuleType

  { TURING       = 0
  , CONTEXT      = 1
  , CONTEXT_FREE = 2
  , REGULAR      = 3
  };
struct Rule {

  Seq left;
  Seq right;
};
Rule rule(Seq, Seq);
Rule rule(String);
RuleType ruleType(const Rule&);

def Rules   = Vector<Rule>;
def Grammar = Vector<Rule>;


String show(const SymbolType&);
String show(const Symbol&);
String show(const Seq&);
String show(const Rule&);
String show(const Grammar&);


Seq infer2l(const Seq&, const Rule&);
Seq infer2r(const Seq&, const Rule&);
Seq infer(const Grammar&, const Vector<Int>&);

Symbols getV_Ns(const Grammar&);
Symbols getV_Ts(const Grammar&);

Symbols first (const Seq&,    const Grammar&);
Symbols follow(const Symbol&, const Grammar&);
Symbols select(const Rule&,   const Grammar&);
Bool isLL1(const Grammar&);

Bool testGrammar(const Grammar&);
Bool testMatch(const Grammar&, const Seq&);

enum ThreeLogic
{ OK, NO, UN };

Map<Symbol, ThreeLogic>
emptyTable(const Grammar &g);


Bool match(const Seq&, const Grammar&);



#endif







