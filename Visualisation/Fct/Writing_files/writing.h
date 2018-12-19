#ifndef WRITING_H_INCLUDED
#define WRITING_H_INCLUDED
#include <string>


bool exists_test (const std::string& name); //Définit une fonction testant si le fichier "name" est accessible (existe)
void define_name(const char* modele_nom_fichier, int& numero_du_fichier ); //on definit une serie de fonctions qui servent à écrire dans un fichier texte nos résultats__
void write_in(int& numero_du_fichier, const char* modele_nom_fichier, const double& position_ou_vitesse);
void write_endl(int& numero_du_fichier, const char* modele_nom_fichier);




#endif //WRITING_H_INCLUDED
