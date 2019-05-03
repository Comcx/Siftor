#include "Mix.h"
#include "Grammar.h"
#include <iostream>

use module std;


Int main() {

  Grammar g0
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

  Grammar g1
    { rule("[S] -> [A]p")
    , rule("[S] -> [B]q")
    , rule("[A] -> a")
    , rule("[A] -> c[A]")
    , rule("[B] -> b")
    , rule("[B] -> d[B]")
    };
  //val ss = infer2l(raw, r0);
  //val m = emptyTable(g);
  //val set = first(seq("[S]"), g);
  //val fs = select(rule("[D] -> c"), g);

  val test = isLL1(g0);
  testGrammar(g0);
  //val xx = first(seq("[A]p"), g1);
  //for(val &e : xx)
  //  std::cout << show(e) << " ";
  cout << endl;
  cout << show(g0) << endl
       << test    << endl;;
  
  return 0;
}
















