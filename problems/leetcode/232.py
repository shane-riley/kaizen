# Implement Queue using Stacks
class MyQueue:

    def __init__(self):

        # Top of out_stack is next-out
        # Top of in_stack is last-in
        # When out_stack is empty, flip over in_stack into out_stack

        # Make the stacks
        self.in_stack = []
        self.out_stack = []
        
    # O(1)
    def push(self, x: int) -> None:
        self.in_stack.append(x)

    # O(1) amortized
    def pop(self) -> int:
        self.ensure_out_stack()
        return self.out_stack.pop()
        
    # O(1) amortized
    def peek(self) -> int:
        self.ensure_out_stack()
        return self.out_stack[-1]

    # O(1)
    def empty(self) -> bool:
        return (len(self.out_stack) == 0 and len(self.in_stack) == 0)

    # O(n) but only called sometimes
    def ensure_out_stack(self) -> None:
        # If out_stack is empty, flip over
        if len(self.out_stack) == 0:
            while len(self.in_stack) > 0:
                self.out_stack.append(self.in_stack.pop())
