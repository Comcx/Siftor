#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Mix.h"
#include <vector>


use module Mix;
use module Mix::Alias;
mix<Set t>
def Vector = std::vector<t>;


enum SymbolType {V_T, V_N, NONE};
struct Symbol {
  
  SymbolType type;
  String value;
};
Symbol symbol(SymbolType, String);


def Seq = Vector<Symbol>;
Seq seq(String raw);
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


Seq infer(const Grammar &g, const Vector<Int>&);




#endif







