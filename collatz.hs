module Collatz where

-- one step of the Collatz sequence
step :: Integer -> Integer
step x = if even x then down else up
    where down = div x 2
          up = 3 * x + 1

-- collatz x computes how many steps it takes for the Collatz
-- sequence to reach 1 when starting from x
collatz :: Integer -> Integer
collatz 1 = 0
collatz x = 1 + collatz (step x)

-- longest finds the number with the longest Collatz sequence
-- for values between 1 and upperBound
longest :: Integer -> Integer
longest upperBound = longest' 0 0 upperBound

-- helper function for longest
-- used to save the number which achieves the longest Collatz sequence
longest' :: Integer -> Integer -> Integer -> Integer
longest' x _ 0 = x
longest' curBest curMax n = if length > curMax
    then longest' n length (n-1)
    else longest' curBest curMax (n-1)
    where length = collatz n
