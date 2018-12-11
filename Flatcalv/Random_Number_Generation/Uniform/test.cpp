#include <iostream>
#include "randoms.h"
using namespace std;

int main(int argc, char const *argv[]) {
  for (int i = 0; i < 10; i++) {
    std::cout << uniform(0.0,1.0) << '\n';

  }

  return 0;
}
