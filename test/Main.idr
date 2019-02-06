module Main

import Core
import Engine
import Parser



main : IO ()
main = putStrLn "Testing..."



square : Parser RegExpr
square = do
  char '['
  s <- many1 anyChar
  char ']'
  pure $ Pack (pack s)

unit : Parser RegExpr
unit = do
  s <- anyChar
  pure $ Unit s


mutual {
expr : Parser RegExpr
expr = unit <|> square <|> join <|> mult <|> star
  
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
  char '*'
  space
  e <- expr
  char ')'
  pure $ Star e

}






test : String -> String -> Bool
test e s = case parse expr e of
  [(r, "")] => match r s
  [(r, xs)] => False






