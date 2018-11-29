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

void write_in(char& buffer[256], int& numero_du_fichier, string const& fichier) {

  snprintf(buffer, sizeof(buffer), fichier, numero_du_fichier);
    while (exists_test(buffer)) {
    snprintf(buffer, sizeof(buffer), fichier, numero_du_fichier);
    numero_du_fichier+=1;
    }
    ofstream test;
    test.open(buffer, ios::app);
    if (test.is_open())
    {
    test << "Hello world \n";
    test.close();
    }
    else cout << "unable to open text";

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
  char buffer[256];



 write_in(buffer, numero_du_fichier, "test%04d.txt");


  return 0;
}
