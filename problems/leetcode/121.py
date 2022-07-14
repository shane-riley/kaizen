## 121. Best Time to Buy and Sell Stock
from typing import List
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        # Find the indeces that produce the largest positive difference,
        # and return the difference
        # O(n) time, O(1) space

        best_profit = 0
        buy = 0
        for sell in range(1,len(prices)):
            
            # Is it the best yet
            if prices[sell] - prices[buy] > best_profit:
                best_profit = prices[sell] - prices[buy]

            # If we're losing money, move buy to sell
            if prices[sell] - prices[buy] < 0:
                buy = sell

        return best_profit
