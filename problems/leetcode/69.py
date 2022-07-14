## 69. Sqrt(x)
class Solution:
    def mySqrt(self, x: int) -> int:
        if (x == 0): return 0
        # Use mechanics rule
        guess_1 = -1
        guess = x / 2
        while abs(guess_1 - guess) > 0.5:
            guess_1 = guess
            guess = 0.5 * (guess_1 + (x / guess_1))
        return int(guess)
            