module Core


Parsc : (a : Type) -> Type
Parsc a = String -> List (a, String)

record Parser (a : Type) where
  constructor MKParser
  parse : Parsc a


Functor Parser where
  map f (MKParser p) = MKParser $ 
    \cs => [(f a, s) | (a, s) <- p cs]

Applicative Parser where
  pure a  = MKParser $ \cs => [(a, cs)]
  (<*>) (MKParser f) (MKParser p) = MKParser $ 
    \s => [(f a, s2) | (f, s1) <- f s, (a, s2) <- p s1]

Semigroup (Parser a) where
  p <+> q = MKParser $ \cs => 
    parse p cs <+> parse q cs
    
Monoid (Parser a) where
  neutral = MKParser $ \cs => []


Alternative Parser where
  empty = neutral
  p <|> q = MKParser $ \cs => case parse (p <+> q) cs of
    []        => []
    (x :: xs) => [x]

Monad Parser where
  p >>= f = MKParser $ \cs => 
    concat [parse (f a) s | (a, s) <- parse p cs]



item : Parser Char
item = MKParser $ \cs => case unpack cs of
  []        => []
  (x :: xs) => [(x, pack xs)]

satisfy : (Char -> Bool) -> Parser Char
satisfy p = do 
  c <- item
  if p c then pure c else neutral



mutual
  many1 : Parser a -> Parser (List a)
  many1 p = do 
    a  <- p
    as <- many p
    pure (a :: as)

  many : Parser a -> Parser (List a)
  many p = many1 p <|> pure []

  sepBy : Parser a -> Parser b -> Parser (List a)
  sepBy p sep =  (sepBy1 p sep) <|> pure []

  sepBy1 : Parser a -> Parser b -> Parser (List a)
  sepBy1 p sep = do 
    a  <- p
    as <- many (do sep; p)
    pure (a :: as)



char : Char -> Parser Char
char c = satisfy (c ==)

string : String -> Parser String
string ss = case unpack ss of
  []        => pure ""
  (c :: cs) => do 
    char c
    string $ pack cs
    pure $ pack (c :: cs)

space : Parser String
space = do
  s <- many $ satisfy isSpace
  pure (pack s)

token : Parser a -> Parser a
token p = do 
  a <- p
  space
  pure a






test : Parser (Char, Char)
test = do
  c <- item
  item
  d <- item
  pure (c, d)
  



