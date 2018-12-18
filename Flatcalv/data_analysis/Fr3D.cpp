/* compiler avec : c++ -Wall -O3 -std=c++11 "Fct/Randomness/randoms.cpp" Antigene.cpp Antibody.cpp stat3D.cpp -lm -DAFFICHAGE `sdl2-config --cflags --libs`


Pour assembler un film a partir des images enregistrees dans des fichiers, utiliser :
ffmpeg -f image2 -pattern_type glob -framerate 100 -i 'image*.bmp' film.avi */

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <fstream>
#include "Antigene.h"
#include "Antibody.h"

using namespace std;
/*___on définit des fonctions servant à écrire dans un .txt___*/

bool exists_test (const std::string& name)//Définit une fonction testant si le fichier "name" est accessible (existe)
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
		test << " ";
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

int main(int argc, char* argv[])
{	

//Pour écriture fichier
  int numero_du_fichier= 0;
  char* modele_nom_fichier = "Fr%04d.txt";

/*___on initialise les valeurs de paramètres___*/

  	double prefact=1.0; //prefacteur devant fonction erfc dans probabt
  	double probabt=pow(10,-9); 
	double tc=pow(10,-14); //??? Constante de temps pour adimensionnement choisie inferieur à 10-¹²
	double m=3.18*pow(10,-23); //masse de la molecule
	double M=6.02*pow(10,23)*m;//masse molaire
	double xc=pow(10,-5); //Longueur pour adimensionnement telque Br~1 pour tc
	double l=1.8*pow(10,-10); // amortissement lambda
	float Fr=0.066; //ecart type de la force random
	double A=-l*tc/m; //A et Br sont les paramètres restant après adimensionnement ~1
	
	int Ng=60; //Nombre d'antigène pour 100um3 de solution 1nM
	int T=310;//température 
	
	
	double dG=pow(tc,2)/pow(xc,2)*8.314*T*log(2*pow(10,-5))/M;//dG adimensionné

	
	for (int Nb=10;Nb<150;Nb=Nb+10)//Nb=nombre anticorps
	{
		define_name(modele_nom_fichier, numero_du_fichier);
		Fr=Fr/2;
		double Br=Fr*pow(tc,2)/(m*xc); // Br est précisé
		for (int e=1;e<11;e++)// e est le numéro de l'experience
		{
			srand (time(NULL));//seed la fonction random sur le temps
			int Nba=0; //Nombre servant à compter le nombre d'anticorps liés
			int t=0;
			Antigene *tabg[Ng];//creer un tableau contenant Ng adresses d'antigene
			for(int i=0; i<Ng; i++)
			{
				tabg[i]=new Antigene(); 
			}
			Antibody *tabb[Nb];//creer un tableau contenant Nb adresses d'antibody
			for(int j=0;j<Nb; j++)
			{
				tabb[j]= new Antibody(); 
			}
			while ((float)Nba/Nb<0.4) // simuler tant jusqu'à un nombre de paire .
			{

/*___Mouvement brownien des particules___*/

			for (int i = 0; i < Ng; i++)
			{
				if (tabg[i]->getstate()==true) //la flèche permet d'appliquer une méthode à l'objet situé à l'adresse à gauche de la flèche
				{
					if (tabg[i]->getyposition()<tabg[i]->getradius())
					{
						for (int j=0;j<Nb;j++)
						{
							tabg[i]->notifyzones();
							tabg[i]->incrementtimeinzone();
							tabg[i]->bind(tabb[j],	M,dG,T,probabt,tc,prefact);
						}
						if (tabg[i]->getstate()==true)
						{
							tabg[i]->motion(A,Br);
						}
					}		
					else
					{
						tabg[i]->motion(A,Br);
					}
				}
			}
			int Nbp=0;// pour compter les anticorps libres
/*On va tracer Nb lié(t)*/
			for (int j=0;j<Nb;j++)
			{
				if ((tabb[j]->getstate())==false)
				{
					Nbp+=1;
				}
			}
				t+=1;//on compte le temps necessaire pour remplir la condition du while
				Nba=Nbp;
				
			}
/*___On va ecrire dans le fichier___*/
			write_in(numero_du_fichier, modele_nom_fichier,Fr);//le numero de l'experience
			write_in(numero_du_fichier, modele_nom_fichier,t*tc);//on redimensionne le temps
			write_endl(numero_du_fichier, modele_nom_fichier);
		}
	}
	return 0;
}
