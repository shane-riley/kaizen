# Best Time to Buy and Sell Stock
from typing import List
class Solution:
    def maxProfit(self, prices: List[int]) -> int:

        # Indeces and sum
        buy = 0
        sell = 1
        max_found = 0

        while sell < len(prices):
            profit = prices[sell] - prices[buy]
            
            # If profit is negative
            if profit < 0:
                # Move forward
                buy = sell
            else:
                max_found = max(max_found, profit)
            sell += 1
        return max_found
