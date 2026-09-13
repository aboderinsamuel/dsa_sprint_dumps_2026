from collections import deque
from typing import Optional

class PriceWindow:
    """
    maintains a sliding window of (timestamp, price) over the last `window_seconds`.
    Provides O(1) amortized access to the maximum and minimum price in the window
    using monotonic deques.
    """
    def __init__(self, window_seconds: int = 600):
        self.window_seconds = window_seconds
        self.max_deque = deque()  # stores (timestamp, price) decreasing order front = maximum
        self.min_deque = deque()  # stores (timestamp, price) inreasing order front = minimum
        self.triggered = False  # flag to indicate if the threshold has been triggered

    def add_price(self, timestamp: int, price: float):
        # Remove old prices from the deques
        cutoff = timestamp - self.window_seconds
        while self.max_deque and self.max_deque[0][0] < cutoff:
            self.max_deque.popleft()
        while self.min_deque and self.min_deque[0][0] < cutoff:
            self.min_deque.popleft()
        while self.max_deque and self.max_deque[-1][1] <= price:
            self.max_deque.pop()
        self.max_deque.append((timestamp, price))
        while self.min_deque and self.min_deque[-1][1] >= price:
            self.min_deque.pop()
        self.min_deque.append((timestamp, price))

    def get_max(self) -> Optional[float]:
        return self.max_deque[0][1] if self.max_deque else None
    def get_min(self) -> Optional[float]:
        return self.min_deque[0][1] if self.min_deque else None
    def check_change(self, threshold: float = 0.10) -> bool:
        """
        Check if the price change in the window exceeds the threshold.
        Returns True if the change exceeds the threshold, False otherwise.
        """
        if not self.max_deque or not self.min_deque:
            return False
        max_price = self.max_deque[0][1]
        min_price = self.min_deque[0][1]
        if min_price == 0:
            return False  # Avoid division by zero
        change = (max_price - min_price) / min_price
        if change >= threshold and not self.triggered:
            self.triggered = True
            return True
        elif change < threshold*0.9:
            self.triggered = False  # Reset the triggered flag if the change drops below 90% of the threshold
        return False
    