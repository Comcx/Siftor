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

plain : Parser RegExpr
plain = do
  s <- many1 anyChar
  pure $ Pack (pack s)


mutual {
expr : Parser RegExpr
expr = plain <|> square <|> join <|> mult <|> star
  
join : Parser RegExpr
join = do
  char '('
  a <- expr
  char '|'
  b <- expr
  char ')'
  pure $ Plus a b

mult : Parser RegExpr
mult = do
  char '('
  a <- expr
  b <- expr
  char ')'
  pure $ Mult a b

star : Parser RegExpr
star = do
  char '('
  e <- expr
  char '*'
  char ')'
  pure $ Star e

}






test : String -> String -> Bool
test e s = case parse expr e of
  [(r, "")] => match r s
  [(r, xs)] => False






