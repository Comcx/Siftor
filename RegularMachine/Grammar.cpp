#include "Grammar.h"



Symbol symbol(SymbolType t, String v) {

  Symbol ans = {t, v};
  return ans;
}

Rule rule(Seq l, Seq r) {

  Rule ans = {l, r};
  return ans;
}
RuleType ruleType(const Rule &r) {

  RuleType ans(TURING);
  //1 type?
  if(r.left.size() <= r.right.size()) {
    ans = CONTEXT;
    //2 type?
    if(r.left.size() == 1) {
      ans = CONTEXT_FREE;
      //3 type?
      if(r.right.size() == 1 &&
	 r.right.at(0).type == V_T
	 ||
	 r.right.size() == 2 &&
	 r.right.at(0).type == V_T &&
	 r.right.at(1).type == V_N) ans = REGULAR;
    }
  }
  return ans;
}



String show(const SymbolType &t) {

  String ans("NONE");
  switch(t) {
  case V_T: ans = "V_T"; break;
  case V_N: ans = "V_N"; break;
  default:  ;
  }
  return ans;
}

String show(const Symbol &s) {

  return s.type == V_N  ?
    "[" + s.value + "]" :
    s.value;
}

String show(const Seq &s) {

  String ans("");
  for(val &e : s) ans += show(e);
  
  return ans;
}

String show(const Rule &r) {

  return show(r.left) + "\t->\t" + show(r.right);
}

String show(const Grammar &g) {

  String ans("");
  for(val &r : g) ans += show(r) + "\n";

  return ans;
}












