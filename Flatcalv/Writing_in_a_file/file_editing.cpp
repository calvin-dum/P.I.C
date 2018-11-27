#include <iostream>
#include <fstream>
using namespace std;



bool exists_test (const std::string& name) {
  if (FILE *file = fopen(name.c_str(), "r")) {
      fclose(file);
      return true;
  } else {
      return false;
  }
}


int main() {
/*  char nom_de_fichier[256];
  snprintf(nom_de_fichier, sizeof(nom_de_fichier), "image%04d.bmp",
           numero_d_image);
  ofstream test ("test.txt");
  */
  //Bloc ayant pour fonction de checker l'existence d'un fichier
  int numero_du_fichier;
  numero_du_fichier=1;
  char name[256];




snprintf(name, sizeof(name), "test%04d.txt",numero_du_fichier);
  while (exists_test(name)) {
  snprintf(name, sizeof(name), "test%04d.txt",numero_du_fichier);
  numero_du_fichier+=1;
  }
  ofstream test;
  test.open(name, ios::app);
  if (test.is_open())
  {
  test << "Hello world \n";
  test.close();
  }
  else cout << "unable to open text";


  return 0;
}
