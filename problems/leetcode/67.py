## 67. Add Binary
class Solution:
    def addBinary(self, a: str, b: str) -> str:
        
        # List for new binary
        new_digits = []
        
        # Iterate from least significant
        carry = 0
        for i in range(max(len(a), len(b))):
            a_b = int(a[-(i+1)]) if (i+1) <= len(a) else 0
            b_b = int(b[-(i+1)]) if (i+1) <= len(b) else 0
            new_b = a_b + b_b + carry
            if (new_b > 1):
                new_b -= 2
                carry = 1
            else:
                carry = 0
            new_digits.insert(0,str(new_b))
        
        # Check carry
        if (carry):
            new_digits.insert(0,'1')
        
        # Turn to string
        return ''.join(new_digits)
        