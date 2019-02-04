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
    
--Alternative Parser where
  

Monad Parser where
  p >>= f = MKParser (\cs => 
    concat [parse (f a) cs' | (a, cs') <- parse p cs])



item : Parser Char
item = MKParser $ \cs => case unpack cs of
  []        => []
  (x :: xs) => [(x, pack xs)]

test : Parser (Char, Char)
test = do
  c <- item
  item
  d <- item
  pure (c, d)
  



