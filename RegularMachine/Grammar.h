#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Mix.h"
#include <vector>
#include <list>

use module Mix;
use module Mix::Alias;
mix<Set t>
def Vector = std::vector<t>;
mix<Set t>
def LinkedList = std::list<t>;

enum SymbolType {V_T, V_N, NONE};
struct Symbol {
  
  SymbolType type;
  String value;
  Bool operator==(const Symbol &that) const {
				       
    return this->type  == that.type &&
           this->value == that.value; 
  }
};
Symbol symbol(SymbolType, String);
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
RuleType ruleType(const Rule&);


def Grammar = Vector<Rule>;


String show(const SymbolType&);
String show(const Symbol&);
String show(const Seq&);
String show(const Rule&);
String show(const Grammar&);


Seq infer2l(const Seq&, const Rule&);
Seq infer2r(const Seq&, const Rule&);
Seq infer(const Grammar&, const Vector<Int>&);

Symbols first(const Seq&, const Grammar&);



#endif







