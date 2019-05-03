#include "Mix.h"
#include "Grammar.h"
#include "Homework.h"
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
    , rule("[D] -> a")
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

  Grammar g2
    { rule("[S]  -> [T][S']")
    , rule("[S'] -> +[T][S']")
    , rule("[S'] -> []")
    , rule("[T]  -> [F][T']")
    , rule("[T'] -> *[F][T']")
    , rule("[T'] -> []")
    , rule("[F]  -> i")
    , rule("[F]  -> ([S])")
    };

  Grammar g3
    { rule("[S]  -> [T][S']")
    , rule("[S'] -> +[T][S']")
    , rule("[S'] -> -[T][S']")
    , rule("[S'] -> []")
    , rule("[T]  -> [F][T']")
    , rule("[T'] -> *[F][T']")
    , rule("[T'] -> /[F][T']")
    , rule("[T'] -> []")
    , rule("[F]  -> i")
    , rule("[F]  -> ([S])")
    };
  
  //val ss = infer2l(raw, r0);
  //val m = emptyTable(g);
  //val set = first(seq("[S]"), g);
  //val fs = select(rule("[D] -> c"), g);

  val test = isLL1(g3);
  //val ss = follow(symbol("[S']"), g2);
  //testGrammar(g3);

  //cout << "==>" << endl;
  //for(val &x : ss)
  //  cout << show(x) << " ";
  //cout << endl;
  
  Seqs src
    { seq("i+i#")
    , seq("i*i#")
    , seq("i+i*i#")
    , seq("i+i*(i+i)#")
      //, seq("i+(i+i*i#")
    };
  Seqs raw {};
  for(val &s : src) {

    Seq temp {};
    for(var it = s.rbegin(); it != s.rend(); ++it) {

      temp.push_back(*it);
    }
    std::cout << show(s) << " => ";
    start(temp);
  }
  
  testMatch(g3, seq("i+(i+i*i)#"));
  
  //cout << show(g3) << endl;
  
  return 0;
}
















