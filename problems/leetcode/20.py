class Solution:
    def isValid(self, s: str) -> bool:

        pairs = {
            ")": "(",
            "}": "{",
            "]": "["
        }

        # Use a stack
        char_stack = []
        for char in s:

            # If opener add to stack
            if char in ['{', '(', '[']:
                char_stack.append(char)

            # If closer look for opener on top of stack
            elif char in ['}', ')', ']']:
                if len(char_stack) == 0 or char_stack[-1] != pairs[char]:
                    return False
                char_stack.pop()
        
        # Success if stack is empty
        return len(char_stack) == 0