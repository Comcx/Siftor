#include "Grammar.h"
#include <iostream>


Symbol
symbol(SymbolType t, String v) {

  Symbol ans = {t, v};
  return ans;
}

Rule
rule(Seq l, Seq r) {

  Rule ans = {l, r};
  return ans;
}
RuleType
ruleType(const Rule &r) {

  RuleType ans(TURING);
  //1 type?
  if(r.left.size() <= r.right.size()) {
    ans = CONTEXT;
    //2 type?
    if(r.left.size() == 1) {
      ans = CONTEXT_FREE;
      //3 type?
      if(r.right.size() == 1 &&
	 r.right.front().type == V_T
	 ||
	 r.right.size() == 2 &&
	 r.right.front().type == V_T &&
	 (++r.right.cbegin())->type == V_N) ans = REGULAR;
    }
  }
  return ans;
}



String
show(const SymbolType &t) {

  String ans("NONE");
  switch(t) {
  case V_T: ans = "V_T"; break;
  case V_N: ans = "V_N"; break;
  default:  ;
  }
  return ans;
}

String
show(const Symbol &s) {

  return s.type == V_N  ?
    "[" + s.value + "]" :
    s.value;
}

String
show(const Seq &s) {

  String ans("");
  for(val &e : s) ans += show(e);
  
  return ans;
}

String
show(const Rule &r) {

  return show(r.left) + "\t->\t" + show(r.right);
}

String
show(const Grammar &g) {

  String ans("");
  for(val &r : g) ans += show(r) + "\n";

  return ans;
}


static Int
getLeftMost(const Seq &s) {

  Int ans(0);
  var it(s.begin());
  for(; ans < s.size()
	&& it->type != V_N; ++ans, ++it);

  return ans;
}

static Int
getRightMost(const Seq &s) {

  Int ans(s.size());
  var it(--s.end());
  for(; ans >= 0
	&& it->type != V_N; --ans, --it);
  
  return ans;
}

Seq
infer2l(const Seq &s, const Rule &r) {

  Seq ans(s);
  var it = ans.begin();
  it = next(it, getLeftMost(ans));

  if(r.left.size() == 1 && r.left.front() == *it) {
    
    it = ans.erase(it);
    it = ans.insert(it, r.right.begin(), r.right.end());
  }

  return ans;
}

Seq
infer2r(const Seq &s, const Rule &r) {

  Seq ans(s);
  var it = ans.begin();
  it = next(it, getRightMost(ans));

  if(r.left.size() == 1 && r.left.front() == *it) {
    
    it = ans.erase(it);
    it = ans.insert(it, r.right.begin(), r.right.end());
  }

  return ans;
}




static Symbols
firstOf(const Seqs &ss, const Grammar &g) {

  Symbols ans{symbol(NONE, "")};
  

  return ans;
}


Symbols
first(const Seq &s, const Grammar &g) {

  Seqs ss {s};
  return firstOf(ss, g);
}



