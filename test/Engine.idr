module Engine


data RegExpr = Empty
             | Unit Char
             | Pack String
             | Plus RegExpr RegExpr
             | Mult RegExpr RegExpr
             | Star RegExpr


matchPart : RegExpr -> String -> Bool -> (Bool, String)
matchPart Empty "" b = (True, "")
matchPart (Pack "") "" b = (True, "")
matchPart e "" b = (b, "")
matchPart e s  b = case e of
  Empty    => (False, s)
  Unit c   => if strHead s == c  then (True, strTail s)
              else (False, s)
  Pack ""  => (True, s)
  Pack ss  => if strHead ss == strHead s
              then case matchPart (Pack $ strTail ss) (strTail s) b of
                (True, s') => (True, s')
                (False, _) => (False, s)
              else (False, s)
  Plus x y => case matchPart x s b of
                (True, ss) => (True, ss)
                (False, _) => matchPart y s b
  Mult x y => case matchPart x s b of
                (True, ss) => matchPart y ss b
                (False, _) => (False, s)
  Star x   => case matchPart x s b of
                (True, ss) => matchPart e ss True
                (False, _) => (b, s)
                 
  
{-
match : RegExpr -> String -> Bool
match e s = case e of
  Empty    => False
  Unit c   => if strHead s == c then True else False
  Pack ss  => if trim s == ss then True else False
  Plus a b => match a s || match b s
  Mult a b => case matchPart e s False of
                (True, ss) => True
                (False, _) => False
  Star x   => case match
-}






