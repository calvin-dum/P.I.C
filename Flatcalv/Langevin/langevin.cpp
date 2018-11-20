#include <iostream>
#include <math.h>
using namespace std;

/* programme se servant de l'equation de langevin pour calculer les vitesses
instantanees de particules diffusant dans un fluide.
On en déduira les positions
*/

/* Rappel : equation m*a = -gamma*v + R(t) + Fext
R(t) force random modelisant interaction
avec un grand nombre de molecules d'eau.
*/
int main() {
// Const maths
const double PI =3.141592653589793238463;
// Initialisation des variables pour t=0 et init des parametres
  long double v[2] = {0};
  long double a[2] = {0};
  // parametres
  float gamma;
  const float m_antigene = 3.8*pow(10,-23);
  const float m_eau = 18.01528*pow(10,-3)/(6.02*pow(10,23));
  const float R_ANTIGENE = 2e-9;
  const float ETA = 1e-3;
  double tau = 1e-12;

  gamma = 6*PI*ETA*R_ANTIGENE;


  std::cout << "m_antigene" << m_antigene << endl << "m_eau" << m_eau << endl;
  std::cout << "matrices" << v[1] << endl;
  std::cout << gamma/m_antigene << endl;

  return 0;
}
