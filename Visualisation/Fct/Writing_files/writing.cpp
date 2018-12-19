#include "writing.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <assert.h>
#include <stdio.h>
#include <map>

using namespace std;

#include <string>

bool exists_test (const std::string& name)
{
	if (FILE *file = fopen(name.c_str(), "r"))
	{
	    fclose(file);
	    return true;
	}
	 else
	{
	    return false;
	}
}

void define_name(const char* modele_nom_fichier, int& numero_du_fichier )
{
	char buffer[256];
	snprintf(buffer, sizeof(buffer), modele_nom_fichier, numero_du_fichier);
	while (exists_test(buffer))
	{
		printf(modele_nom_fichier, numero_du_fichier);
		std::cout << numero_du_fichier << exists_test(buffer) <<'\n';
		numero_du_fichier+=1;
		snprintf(buffer, sizeof(buffer), modele_nom_fichier, numero_du_fichier);
	}
}


void write_in(int& numero_du_fichier, const char* modele_nom_fichier, const double& position_ou_vitesse)
{
	char buffer[256];
	snprintf(buffer, sizeof(buffer), modele_nom_fichier, numero_du_fichier);
	ofstream test;
	test.open(buffer, ios::app);
	if (test.is_open())
	{
		test << position_ou_vitesse;
		test << "  ";
		test.close();
	}
	else
	{
		cout << "unable to open text";
	}
}

void write_endl(int& numero_du_fichier, const char* modele_nom_fichier)
{
	char buffer[256];
	snprintf(buffer, sizeof(buffer), modele_nom_fichier, numero_du_fichier);
	ofstream test;
	test.open(buffer, ios::app);
	if (test.is_open())
	{
		test << "\n";
		test.close();
	}
	else
	{
		cout << "unable to open text";
	}
}
