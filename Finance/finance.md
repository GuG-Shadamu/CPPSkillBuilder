[<- Finance](finance.md)\
[<- Behavior](behaviour.md)



# Quant Finance Knowledge

## Valuing a Swaption

Valuing a swaption involves several steps, including model selection, interest rate path simulation, swap rate calculation, and option payoff discounting. The Black's model is commonly used due to its simplicity and widespread use. Below are the steps using this model.

### Step 1: Define the Swaption Terms

First, we need to define the terms of the swaption, such as:

- The option expiry (T), i.e., the date until which the option can be exercised.
- The length of the underlying swap contract.
- The fixed swap rate (K).
- The notional amount (N).
- The payment frequency.
- The day count convention.

### Step 2: Determine the Underlying Swap Value

Next, we need to calculate the value of the underlying swap contract at the option expiry date. This involves projecting forward rates for each payment date and calculating the discounted cash flows using the appropriate yield curve.

The swap value (V) at time T can be expressed as the difference between fixed and floating leg present values:

V(T) = B(T, T + n) - K * Σ B(T, T + i)

Here, B(T, T + i) represents the discount factor for the i-th payment date, K is the fixed swap rate, and n is the swap length.

### Step 3: Determine the Swaption Payoff

The payoff of a swaption depends on whether it is a payer swaption (the holder has the right to enter into a swap as a fixed rate payer) or a receiver swaption (the holder has the right to enter into a swap as a fixed rate receiver).

For a payer swaption, the payoff at time T is:

Max[V(T), 0]

For a receiver swaption, the payoff at time T is:

Max[-V(T), 0]

### Step 4: Value the Swaption Using Black's Model

Black's model can be used to value the swaption. The formula is:

Swaption Price = N * Σ B(0, T + i) * (F * N(d1) - K * N(d2))

Here,

- d1 = [ln(F/K) + 0.5 * σ^2 * T] / (σ * √T)
- d2 = d1 - σ * √T
- F is the forward swap rate
- σ is the swaption's implied volatility
- N(*) is the cumulative standard normal distribution function

### Step 5: Consider Practical Adjustments

Consider the inclusion of bid-offer spreads, the impact of collateral agreements (CSAs), and potential adjustments for counterparty credit risk.

The Black's model makes simplifying assumptions, such as constant volatility, which may not hold in real markets. Therefore, more complex models may be needed for accurate pricing in certain market conditions.


## Swaption models:

| Model            | Rate Process         | Volatility                       | Term Structure | Mean Reversion | Suitable For                                                                                                                                                            |
| ---------------- | -------------------- | -------------------------------- | -------------- | -------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Black-76         | Log-normal           | Constant                         | No             | No             | European options on forwards; particularly useful when rates are always positive.                                                                                       |
| Bachelier        | Normal               | Constant                         | No             | No             | European options on forwards; handles negative rates better than Black-76.                                                                                              |
| SABR             | Log-normal           | Stochastic                       | Yes            | No             | Any options, especially those sensitive to the volatility smile, such as swaptions, caps, and floors.                                                                   |
| Ho–Lee           | Log-normal           | Deterministic and time-dependent | Yes            | No             | Interest rate derivatives; particularly for creating a riskless portfolio and modeling a set future term structure of interest rates.                                   |
| Black-Derman-Toy | Log-normal           | Deterministic and time-dependent | Yes            | No             | Interest rate derivatives; it allows for a more flexible, term-structure of volatility compared to Ho-Lee.                                                              |
| Hull-White       | Normal or log-normal | Mean-reverting (time-dependent)  | Yes            | Yes            | Interest rate derivatives, especially for options like Bermudan and American options, that require a model of the term structure of interest rates with mean reversion. |


The Ho–Lee, Black-Derman-Toy, and Hull-White models are often implemented using a lattice or tree-based approach, which can handle a variety of interest rate derivatives and allow for early exercise features, making these models particularly well suited for pricing American and Bermudan style options. In these models, the evolution of interest rates is discretized into a binomial or trinomial tree, allowing for explicit modeling of the potential paths of interest rates.

The Black-76, Bachelier, and SABR models, on the other hand, are typically implemented in a continuous framework using analytic formulas or numerical methods such as Monte Carlo simulation or finite difference methods. These models are particularly suited for European options, which only have one exercise date at maturity.

However, while it is common to use a lattice-based approach for the Ho–Lee, Black-Derman-Toy, and Hull-White models, it is also possible to use other methods such as Monte Carlo simulation or finite difference methods with these models. Similarly, while the Black-76, Bachelier, and SABR models are typically implemented in a continuous framework, they could also potentially be implemented in a lattice-based framework under certain circumstances. The choice of method depends on a variety of factors, including the specific type of derivative, the model assumptions, and computational considerations.


## Differences in Valuing Crude Oil Swaptions VS. Interest Rate Swaptions

From a mathematical perspective, the process for valuing swaptions, whether they're on interest rates or crude oil, is similar. You need to set up the appropriate stochastic differential equations (SDEs) describing the evolution of the underlying variables, solve these SDEs (either analytically or numerically), calculate the payoff of the swaption, and then discount this payoff back to the present.

However, the choice of the model may differ for crude oil swaptions compared to interest rate swaptions, due to the different nature of the underlying assets.

### Interest Rate Swaptions

Interest rate swaptions are typically valued using models that describe the evolution of the term structure of interest rates, such as the Hull-White model, Black-Derman-Toy model, or the LIBOR Market Model. The SABR model is also popular for its ability to capture the volatility smile often observed in interest rate markets.

### Crude Oil Swaptions

On the other hand, crude oil swaptions might be valued using commodity models. These models account for features specific to commodity markets, like seasonality or mean-reversion. Some commonly used models in the commodity space are the Black-76 model (a variation of the Black-Scholes model), the Schwartz model, and the Gabillon model. For crude oil specifically, models that can capture jumps or extreme events might be used, given the greater volatility and potential for large price swings in the oil market.

### Volatility Surface

The structure of the volatility surface can also be different between interest rate and crude oil markets. In interest rates, you typically see a volatility smile (higher volatilities for deep in-the-money and out-of-the-money options), while in commodities, you might see a volatility skew (higher volatilities for out-of-the-money options).

### Discounting

Another key difference lies in the discounting process. Interest rate swaptions are discounted using the risk-free rate, while commodity swaptions, like crude oil, would need to be discounted at the risk-free rate plus a convenience yield, which accounts for the benefits of holding the commodity.

In conclusion, the mathematical framework for valuing swaptions is the same across different asset classes, but the choice of the specific model to use can vary depending on the nature of the underlying asset.



# The SABR Model

The SABR model is a stochastic volatility model, which attempts to capture the volatility smile in derivatives markets. The name stands for "Stochastic Alpha, Beta, Rho", referring to the parameters of the model.

In the SABR model, both the underlying asset price and the volatility are assumed to follow stochastic processes. More precisely, for a forward price `F` and a volatility variable `σ` (sigma), the model is typically expressed as the following system of stochastic differential equations (SDEs):

1. dF = σF^\betadW
2. dσ = \alphaσdZ

Here:

- `W` and `Z` are two correlated Wiener processes with correlation coefficient `\rho` (rho), i.e., dWdZ = \rhodt.
- `\alpha` (alpha) is the volatility of volatility – the rate at which `σ` varies.
- `\beta` (beta) is the elasticity parameter (often assumed to be 1 for log-normal model or 0 for normal model).

These SDEs are driven by a Brownian motion, making them quite complex to solve analytically.

However, the SABR model's main strength lies in the approximate solution for the implied volatility, which can be obtained in closed form for options pricing. Using a series expansion technique, Hagan et al. derived the following expression for the implied volatility (IV) in the SABR model:

![equation](
    https://latex.codecogs.com/png.image?\inline&space;\dpi{200}\bg{white}IV&space;\approx&space;&space;(\alpha/(F^K)^(1-\beta))&space;*&space;[(1&space;&plus;&space;((1-\beta)^2/24)*log^2(F/K)&space;&plus;&space;((1-\beta)^4/1920)*log^4(F/K))&space;*&space;z&space;/&space;x(z)&space;&plus;&space;(\beta-1)^2/24&space;*&space;(\alpha^2/((F*K)^(1-\beta)))&space;&plus;&space;\rho*\beta*\nu/4&space;*&space;\alpha&space;/&space;((F*K)^(1-\beta)/2)&space;&plus;&space;(2-3\rho^2)/24&space;*&space;\nu^2]&space;*&space;sqrt(T)
)



where:

- `F` is the forward rate
- `K` is the strike price
- `T` is the time to expiration
- `\alpha, \beta, \rho, \nu` are parameters of the model
- `z = \nu/\alpha * ((F*K)^(1-\beta)/2) * log(F/K)`
- `x(z) = log[(√(1-2\rhoz+z^2) + z - \rho) / (1-\rho)]`

This formula allows one to compute the implied volatility for any strike price, given the model parameters. By calibrating these parameters to market data, the SABR model can accurately reproduce the observed volatility smile. Despite the complexity of the model, the existence of this approximate formula makes it highly practical for options pricing.


## Volatility Models

| Model                    | Key Features                                                    | Formula                       | Explanation                                                                                                         | Typical Usage                                                         |
| ------------------------ | --------------------------------------------------------------- | ----------------------------- | ------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------- |
| SABR Model               | - Captures skew and curvature in the volatility surface         | `See formula in LaTeX format` | The SABR model uses stochastic alpha, beta, and rho parameters to model the volatility of interest rates.           | Pricing interest rate options, managing the volatility smile          |
| Hull-White Model         | - One-factor model for mean-reverting short-term interest rates | `See formula in LaTeX format` | The Hull-White model assumes a mean-reverting process for the short-term interest rate and can estimate volatility. | Pricing interest rate derivatives, modeling term structure            |
| HJM Model                | - Multi-factor model for yield curve dynamics                   | `See formula in LaTeX format` | The HJM model captures the entire yield curve dynamics, including volatility, by specifying the evolution of rates. | Pricing interest rate derivatives, simulating yield curve movements   |
| LIBOR Market Model (LMM) | - Forward-rate-based model for LIBOR rates                      | `See formula in LaTeX format` | The LMM assumes a stochastic process for each forward LIBOR rate, including volatility.                             | Pricing interest rate derivatives such as caps, floors, and swaptions |
| Black-Karasinski Model   | - Short-rate model with log-normal process                      | `See formula in LaTeX format` | The Black-Karasinski model assumes a log-normal process for the short-term interest rate.                           | Pricing interest rate derivatives, modeling term structure            |
