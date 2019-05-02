#include "Mix.h"
#include "Grammar.h"
#include <iostream>

use module std;


Int main() {

  Seq left {symbol(V_N, "S")};
  Seq rig0 {symbol(V_T, "a"), symbol(V_N, "A")};
  Seq rig1 {symbol(V_T, "a"), symbol(V_N, "B")};
  Seq raw  {symbol(V_T, "s"), symbol(V_N, "S")};
  Rule r0 = rule(left, rig0);
  Rule r1 = rule(left, rig1);
  Grammar g {r0, r1};
  RuleType rt = ruleType(r0);

  val ss = infer2l(raw, r0);
  val m = emptyTable(g);

  for(val &e : m) {

    cout << show(e.first) << " " << e.second << endl;
  }
  
  cout << show(g)  << endl
       << show(ss) << endl;

  return 0;
}
















