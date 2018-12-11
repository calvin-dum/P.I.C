#include "randoms.h"
#include <iostream>
#include <chrono>
#include <random>

double uniform(double a, double b)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator (seed);
  std::uniform_real_distribution<double> distribution(a,b);
  return distribution(generator);

}
