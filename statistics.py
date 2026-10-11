"""Object-oriented statistics calculator for integer datasets."""
from collections import Counter


class StatisticsCalculator:
    def __init__(self, values: list[int]) -> None:
        if not values:
            raise ValueError("Input cannot be empty")
        if any(type(value) is not int for value in values):
            raise TypeError("All values must be integers")
        self._values = list(values)

    def mean(self) -> float:
        return sum(self._values) / len(self._values)

    def median(self) -> float:
        ordered = sorted(self._values)
        n = len(ordered)
        if n % 2:
            return float(ordered[n // 2])
        return (ordered[n // 2 - 1] + ordered[n // 2]) / 2

    def mode(self) -> list[int]:
        frequencies = Counter(self._values)
        highest = max(frequencies.values())
        return sorted(value for value, count in frequencies.items()
                      if count == highest) if highest > 1 else []


if __name__ == "__main__":
    calculator = StatisticsCalculator([4, 2, 7, 2, 9, 4, 2])
    print("Python (Object-Oriented) | Count: 7")
    print(f"Mean: {calculator.mean():.2f}")
    print(f"Median: {calculator.median():.2f}")
    result = calculator.mode()
    print("Mode(s): " + ", ".join(map(str, result)) if result
          else "Mode: none (all values occur once)")
