#include "Mix.h"
#include "Grammar.h"
#include <iostream>

use module std;


Int main() {

  Rule r0 = rule("[S] -> a[A]");
  Rule r1 = rule("[S] -> a[S]");
  Grammar g
    { rule("[S] -> [A][B]")
    , rule("[S] -> b[C]")
    , rule("[A] -> []")
    , rule("[A] -> b")
    , rule("[B] -> []")
    , rule("[B] -> a[D]")
    , rule("[C] -> [A][D]")
    , rule("[C] -> b")
    , rule("[D] -> a[S]")
    , rule("[D] -> c")
    };
  RuleType rt = ruleType(r0);

  //val ss = infer2l(raw, r0);
  val m = emptyTable(g);
  val set = first(seq("[A][D]"), g);
  val fs = follow(symbol(V_N, "D"), g);

  for(val &e : m) {

    cout << show(e.first) << " " << e.second << endl;
  }
  for(val &e : set) {

    cout << show(e) << " ";
  }cout << endl;
  for(val &e : fs) {

    cout << show(e) << " ";
  }cout << endl;
  
  cout << show(g)  << endl;
    //   << show(ss) << endl;

  return 0;
}
















