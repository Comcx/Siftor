#include "Grammar.h"
#include <iostream>


Symbol
symbol(SymbolType t, String v) {

  Symbol ans = {t, v};
  return ans;
}

Seq
seq(String raw) {

  Seq ans;
  Bool literalMode(false);
  Bool V_NMode(false);

  var it = raw.begin();
  String cur("");
  while(it != raw.end()) {

    Char c(*it);
    switch(c) {
    case '[':
      V_NMode = true;
      it++;
      break;
    case ']':
      V_NMode = false;
      if(cur == "") ans.push_back(symbol(V_T, cur));
      else ans.push_back(symbol(V_N, cur));
      it++;
      cur = "";
      break;
    case '<':
      literalMode = true;
      it++;
      break;
    case '>':
      literalMode = false;
      ans.push_back(symbol(V_T, cur));
      it++;
      cur = "";
      break;
    default:
      if(V_NMode) {
	cur += c;
	it++;
      }
      else if(literalMode) {
	cur += c;
	it++;
      }
      else {
	ans.push_back(symbol(V_T, String(1, c)));
	it++;
      }
    }//end seitch
    
  }//end while
  return ans;
}

Rule
rule(Seq l, Seq r) {

  Rule ans = {l, r};
  return ans;
}

Rule
rule(String s) {

  String l("");
  String r("");

  //-> to blanks
  for(var it = s.begin(); it != s.end(); it++) {

    if(*it == '-')
      if(*(++it) == '>') {
	*it = ' ';
	*(--it) = ' ';
      }
  }

  var it = s.begin();
  for(;it != s.end() && *it != ' ';
      it++) {
    
    l.push_back(*it);
  }//end for left

  //skip blanks
  for(; it != s.end() && *it == ' ';
      it++);

  for(;it != s.end() && *it != ' ';
      it++) {
    
    r.push_back(*it);
  }//end for right

  return rule(seq(l), seq(r));
}

static Bool containV_N(const Seq &s) {

  Bool ans(false);
  for(val &c : s)
    if(c.type == V_N) {
      ans = true;
      break;
    }
  return ans;
}

static Bool containV_T(const Seq &s) {

  Bool ans(false);
  for(val &c : s)
    if(c.type == V_T) {
      ans = true;
      break;
    }
  return ans;
}


static Bool existLeft(const Seq &s, const Grammar &g) {

  for(val &r : g) {

    if(r.left == s) return true;
  }
  return false;
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



static Rules
gatherSame(const Seq &s, const Grammar &g) {

  Rules ans {};
  for(val &r : g) {
    if(r.left == s) ans.push_back(r);
  }
  return ans;
}


//enum ThreeLogic
//{ OK, NO, UN };

static ThreeLogic
canBeEmpty(const Seq &s, Map<Symbol, ThreeLogic> &m) {

  ThreeLogic ans(UN);
  //can be empty directly
  if(s.size() == 1 && s.front().value == "") ans = OK;
  //can not be empty
  else if(containV_T(s)) ans = NO;
  else {// test
    Int counter(0);
    for(val &c : s) {
      if(m.count(c) > 0 && m[c] == NO) {
	ans = NO;
	break;
      }
      else if(m.count(c) > 0 && m[c] == OK) {
	counter++;
      }
    }//end for
    if(counter == s.size()) ans = OK;
  }
  /*
  std::cout << ">>" << show(s) << "\t" << ans << std::endl;
  for(val &e : m) {

    std::cout << show(e.first) << " " << e.second << std::endl << std::endl;;
    }*/
  return ans;
}

Map<Symbol, ThreeLogic>
emptyTable(const Grammar &g) {

  Map<Symbol, ThreeLogic> ans {};
  Grammar gg(g);

  Int counter(gg.size());
  while(!gg.empty()) {//std::cout << show(gg) << std::endl << std::endl;
    for(var it = gg.begin(); it!= gg.end();) {

      assert(it->left.size() == 1);
      val cur = it->left;
      val res = canBeEmpty(it->right, ans);

      if(res != UN) {
	it = gg.erase(it); 
        if(res == OK) ans[cur.front()] = OK;
        if(res == NO && !existLeft(cur, gg))
	  if(ans.count(cur.front()) > 0 &&
	     ans[cur.front()] == OK);
	  else ans[cur.front()] = NO;
      }
      else ++it;
    }
    if(counter == gg.size()) break;
    else counter = gg.size();
  }

  return ans;
}

static Symbols
firstOf(const Seqs &ss, const Grammar &g) {

  Symbols ans {};


  return ans;
}


Symbols
first(const Seq &s, const Grammar &g) {

  Seqs ss {s};
  return firstOf(ss, g);
}








