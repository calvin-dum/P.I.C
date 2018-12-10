#include "randoms.h"
#include <iostream>
#include <random>

double uniform()
{
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  return distribution(generator);

}
