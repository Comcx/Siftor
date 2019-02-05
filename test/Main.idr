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
  c <- anyChar
  pure $ Unit c

mutual
  expr : Parser RegExpr
  expr = plain --<|> square <|> join <|> star
  
  join : Parser RegExpr
  join = do
    char '('
    a <- expr
    char '|'
    b <- expr
    char ')'
    pure $ Plus a b

  star : Parser RegExpr
  star = do
    e <- expr
    char '*'
    pure $ Star e


