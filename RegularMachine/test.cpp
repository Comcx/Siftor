#include "Mix.h"
#include "Grammar.h"
#include <iostream>

use module std;


Int main() {

  Seq left {symbol(V_N, "S")};
  Seq rig0 {symbol(V_T, "a"), symbol(V_N, "A")};
  Seq rig1 {symbol(V_T, "a"), symbol(V_N, "B")};
  Rule r0 = rule(left, rig0);
  Rule r1 = rule(left, rig1);
  Grammar g {r0, r1};
  RuleType rt = ruleType(r0);
  
  cout << show(g) << endl
       << rt      << endl;

  return 0;
}
















