#ifndef MONTE_CARLO_HPP_
#define MONTE_CARLO_HPP_

#include <algorithm>
#include <functional>
#include <numeric>
#include <random>

template<typename data_type, typename rng_type = data_type>
class monte_carlo
{
public:
  explicit monte_carlo(
    const std::function<data_type(const std::function<rng_type()>&)>&   sampling_function  ,
    const std::function<data_type(const data_type&, const data_type&)>& reduction_function = std::plus<data_type>())
  : sampling_function_ (sampling_function )
  , reduction_function_(reduction_function)
  {
    
  }
  monte_carlo           (const monte_carlo&  that) = default;
  monte_carlo           (      monte_carlo&& temp) = default;
  virtual ~monte_carlo  ()                         = default;
  monte_carlo& operator=(const monte_carlo&  that) = default;
  monte_carlo& operator=(      monte_carlo&& temp) = default;

  data_type simulate(const std::size_t& sampling_count)
  {
    std::random_device                       random_device   ;
    std::mt19937                             mersenne_twister(random_device());
    std::uniform_real_distribution<rng_type> distribution    ;
    auto rng_function = [&mersenne_twister, &distribution] ()
    {
      return distribution(mersenne_twister);
    };

    std::vector<data_type> intermediates(sampling_count);
    std::generate_n(
      intermediates.begin(),
      intermediates.size (),
      [&]
      { 
        return sampling_function_(rng_function); 
      });

    return std::accumulate(
      intermediates.begin(), 
      intermediates.end  (), 
      data_type(0), 
      reduction_function_)
      / sampling_count;
  }

protected:
  std::function<data_type(const std::function<rng_type()>&)>   sampling_function_ ;
  std::function<data_type(const data_type&, const data_type&)> reduction_function_;
};

#endif
