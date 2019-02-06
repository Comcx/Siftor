module Main

import Core
import Engine
import Parser



main : IO ()
main = putStrLn "Testing..."



square : Parser RegExpr
square = do
  char '['
  s <- many anyChar
  char ']'
  pure $ Pack (pack s)
  

unit : Parser RegExpr
unit = do
  s <- anyChar `except` "|*+_"
  pure $ Unit s
  
empty : Parser RegExpr
empty = do 
  char '('; char ')'; pure Empty
  
wild : Parser RegExpr
wild = do
  char '_'
  pure Wild

mutual {
expr : Parser RegExpr
expr = unit <|> empty <|> wild <|> square 
   <|> join <|> mult <|> star <|> optional
  
join : Parser RegExpr
join = do
  char '('
  space
  char '|'
  space
  a <- expr
  space
  b <- expr
  char ')'
  pure $ Plus a b

mult : Parser RegExpr
mult = do
  char '('
  a <- expr
  space
  b <- expr
  char ')'
  pure $ Mult a b

star : Parser RegExpr
star = do
  char '('
  space
  char '*'
  space
  e <- expr
  char ')'
  pure $ Star e

optional : Parser RegExpr
optional = do
  char '('
  space
  char '+'
  space
  e <- expr
  char ')'
  pure $ Plus e Empty

}






test : String -> String -> Bool
test e s = case parse expr e of
  [(r, "")] => match r s
  others    => False






