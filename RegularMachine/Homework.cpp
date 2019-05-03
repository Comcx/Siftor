
#include "Mix.h"
#include "Homework.h"
#include "Grammar.h"
#include <iostream>


Seq rsrc {};

def hash_t = std::uint64_t;  
literal hash_t prime = 0x100000001B3ull;  
literal hash_t basis = 0xCBF29CE484222325ull;  

literal hash_t hash_compile_time(char const* str, hash_t last_value = basis) {
  
  return *str ?
    hash_compile_time(str+1, (*str ^ last_value) * prime) : last_value;  
}

literal unsigned long long operator "" _hash(char const* p, size_t) {

  return hash_compile_time(p);
}

hash_t str_(const String s) {
  
  hash_t ans{basis};
  for(val &c : s){
    ans ^= c;
    ans *= prime;
  }
  return ans;
}

Unit error(String s = "") {

  std::cout << "NO " << s << std::endl;
  exit(0);
}

Unit token(String s, Seq &cur = rsrc) {

  val ans = cur.back().type == V_T &&
            s == cur.back().value;
  if(ans) cur.pop_back();
  else error(show(cur));
}

Unit symbol_S(Seq &cur = rsrc) {

  switch(str_(cur.back().value)) {

  case "("_hash:
  case "i"_hash:
    symbol_T(cur);
    symbol_S_(cur);
    break;
  default: error(show(cur));
      
  }
}

Unit symbol_S_(Seq &cur = rsrc) {

  switch(str_(cur.back().value)) {

  case "+"_hash:
  case "-"_hash:
    token(cur.back().value, cur);
    symbol_T(cur);
    symbol_S_(cur);
    break;
  case ")"_hash:
  case "#"_hash:
    break;
  default: error(show(cur));
  }
}

Unit symbol_T(Seq &cur = rsrc) {

  switch(str_(cur.back().value)) {
  
  case "("_hash:
  case "i"_hash:
    symbol_F(cur);
    symbol_T_(cur);
    break;
  default: error(show(cur));
  }
}

Unit symbol_T_(Seq &cur = rsrc) {

  switch(str_(cur.back().value)) {

  case "*"_hash:
  case "/"_hash:
    token(cur.back().value, cur);
    symbol_F(cur);
    symbol_T_(cur);
    break;
  case "+"_hash:
  case "-"_hash:
  case ")"_hash:
  case "#"_hash:
    break;
  default: error(show(cur));
  }
}

Unit symbol_F(Seq &cur = rsrc) {

  switch(str_(cur.back().value)) {

  case "("_hash:
    token("(", cur);
    symbol_S(cur);
    token(")", cur);
    break;
  case "i"_hash:
    token("i", cur);
    break;
  default: error(show(cur));
  }
}


Unit start(Seq &cur) {

  symbol_S(cur);
  std::cout << "OK" << std::endl;
}



