This application reads an input file('input.csv') and writes out a new file ('output.csv') calculated from the inputs.
Input:
The input file represents a very simplified stream of trades on an exchange.  
Each row represents a trade.  If you don't know what that means don't worry.  
The data can be thought of as a time series of values in columns: 

<TimeStamp>,<Symbol>,<Quantity>,<Price>

Definitions
- TimeStamp is value indicating the microseconds since midnight.
- Symbol is the 3 character unique identifier for a financial 
  instrument (Stock, future etc.)
- Quantity is the amount traded
- Price is the price of the trade for that financial instrument.

Safe Assumptions:
- TimeStamp is always for the same day and won't roll over midnight.
- TimeStamp is increasing or same as previous tick (time gap will never be < 0).
- Price - our currency is an integer based currency.  No decimal points.
- Price - Price is always > 0.

Problem:
Find the following on a per symbol basis:
- Maximum time gap
  (time gap = Amount of time that passes between consecutive trades of a symbol)
  if only 1 trade is in the file then the gap is 0.
- Total Volume traded (Sum of the quantity for all trades in a symbol).
- Max Trade Price.
- Weighted Average Price.  Average price per unit traded not per trade.
  Result should be truncated to whole numbers.

Output:
Your solution should produce a file called 'output.csv'.
file should be a comma separate file with this format:
<symbol>,<MaxTimeGap>,<Volume>,<WeightedAveragePrice>,<MaxPrice>

The output should be sorted by symbol ascending ('aaa' should be first).