#### Getting Started
- Copy monte_carlo.hpp to your project.

#### Example Usage 
- Estimating Pi:

    ```cpp
    // Template arguments are the data type and the random number type.
    monte_carlo<double, double> pi_estimator(
        // Sampling function. Provides a callable random number generator 
        // and expects a data type (double for this case) return value.
        [] (const std::function<double()>& rng) -> double
        {
            // Sample a point within the unit square i.e.
            // x in [0,1], y in [0,1].
            auto x = rng();
            auto y = rng();
      
            // Calculate distance from the origin.
            auto distance = sqrtf(x * x + y * y);
      
            // If the point is within the quarter circle, append 1.0F.
            return distance <= 1.0 ? 1.0 : 0.0;
        },
        // Reduction function (optional). Provides two data type values 
        // and expects a data type return value.
        [] (const double& lhs, const double& rhs) -> double
        {
            return lhs + rhs;
        }
    );
    
    // Apply 30,000 times.
    auto pi = pi_estimator.simulate(30000);
    
    // Multiply by 4 to exterpolate the quarter circle to the full circle.
    pi *= 4.0F;
    ```
