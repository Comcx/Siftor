module Parser

import Core


%access public export

letter : Parser Char
letter = satisfy isAlpha

digit : Parser Char
digit = satisfy isDigit

aSpace : Parser Char
aSpace = satisfy isSpace

anyChar : Parser Char
anyChar = oneOf "~!@#$%^&_+`s-=:;\"<>,.?/\\"
      <|> letter <|> digit <|> aSpace

parens : Parser a -> Parser a
parens m = do
  char '('
  n <- m
  char ')'
  pure n






