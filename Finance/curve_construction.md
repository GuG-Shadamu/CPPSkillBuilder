[<- Finance](finance.md)\
[<- Behavior](behaviour.md)

# Yield Curve Construction (Bootstrap)

### Step 1: Market Data

Gather market data on fixed income instruments, including their prices and corresponding maturities.

### Step 2: Initial Estimation Point

Choose an initial estimation point on the yield curve, which will serve as the starting point for the bootstrap process.

### Step 3: Initial Yield Assignment

Assign the initial yield estimate to the instrument with the maturity closest to the chosen estimation point.

### Step 4: Construct the Cash Flow Matrix

Create a cash flow matrix that represents the cash flows of each instrument at their respective maturities. Each row of the matrix corresponds to an instrument, and each column represents a maturity point.

### Step 5: Calculate the Price Vector

Compute the theoretical price vector for all instruments using the assigned initial yield estimates and the cash flow matrix. This can be done by multiplying the cash flow matrix by the discount factors derived from the initial yield estimates.

### Step 6: Compare with Market Prices

Compare the calculated price vector with the market price vector. The market price vector contains the market prices of the instruments.

### Step 7: Calculate the Jacobian Matrix

Compute the Jacobian matrix, which represents the sensitivity of the instrument prices to changes in the yield estimates. Each element of the Jacobian matrix is obtained by taking the partial derivative of the instrument price with respect to the yield estimate at the corresponding maturity.

### Step 8: Determine the Discrepancy Vector

Calculate the discrepancy vector by taking the difference between the calculated price vector and the market price vector.

### Step 9: Calculate the Adjustment Vector

Compute the adjustment vector by multiplying the inverse of the Jacobian matrix with the discrepancy vector.

### Step 10: Update the Yield Estimates

Update the yield estimates by adding the corresponding values from the adjustment vector.

### Step 11: Iterate

Repeat steps 4-10 until the calculated prices closely match the market prices for all instruments. This can be assessed by monitoring the convergence of the discrepancy vector.

### Step 12: Interpolate or Extrapolate

Once the yield estimates have converged, use interpolation or extrapolation techniques to estimate yields for other maturities based on the derived yield curve.

### Step 13: Yield Curve Construction

Plot the derived yields against their corresponding maturities to visualize the yield curve, representing the term structure of interest rates.