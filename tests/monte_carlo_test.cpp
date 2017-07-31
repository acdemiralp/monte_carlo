#include "catch.hpp"

#include <monte_carlo/monte_carlo.hpp>

TEST_CASE("Monte Carlo estimator is tested.", "[monte_carlo_estimator]") 
{
  monte_carlo<double> pi_estimator(
    [] (const std::function<double()>& rng)
    {
      return sqrtf(pow(rng(), 2) + pow(rng(), 2)) <= 1.0F ? 1.0F : 0.0F;
    });
  WARN("Pi is estimated as " << pi_estimator.simulate(30000) * 4);
}
