/* compiler avec : c++ -Wall -O3 -std=c++11 "Fct/Randomness/randoms.cpp" Antigene.cpp Antibody.cpp Frstat.cpp -lm -DAFFICHAGE `sdl2-config --cflags --libs`


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
#ifdef AFFICHAGE
#include <SDL.h>
#include <fstream>
#include "Antigene.h"
#include "Antibody.h"
//#include <SDL_gfxPrimitives.h>
#endif

using namespace std;
//Définit une fonction testant si le fichier "name" est accessible (existe)
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

int main(int argc, char* argv[])
{

	int numero_du_fichier= 0;
	int numero_d_image= 0;
	char* modele_nom_fichier = "Fr%04d.txt";


	random_device rd{};
	mt19937 gen{rd()};


  	double prefact=1.0;
  	double probabt=pow(10,-9);
	double tc=pow(10,-14);
	double m=3.18*pow(10,-23);
	double M=6.02*pow(10,23)*m;
	double xc=pow(10,-6);
	double l=1.8*pow(10,-10);
	double Fr=0.0066;
	double A=-l*tc/m;
	int Ng=60;
	int Nb=100;
	int T=0;
	int target_sat=40;
	double dG=pow(tc,2)/pow(xc,2)*8.314*T*log(2*pow(10,-5))/M;
/*on va repeter l'exp pour différentes conditoins initiale*/
	for (int f=0;f<10;f++)
	{
		define_name(modele_nom_fichier, numero_du_fichier);
		Fr=Fr/2;
		double Br=Fr*pow(tc,2)/(m*xc); // Br est précisé
		for (int e=0;e<10;e++)//pour chaque conditions initiales on fait des stats sur 10 itérations de l'exp
		{
			srand (time(NULL));//seed la fonction random sur le temps

			int Nba=0; //Nombre servant à compter le nombre d'anticorps liés
			int t=0;//pour compter le temps de simulation
			Antigene *tabg[Ng+target_sat];
			for(int i=0; i<Ng+target_sat; i++)
			{
				tabg[i]=new Antigene();
  			for (int i = Ng; i <Ng + target_sat; i++)
			{
	    			tabg[i]->pull_out();
			}
			Antibody *tabb[Nb];
			for(int j=0;j<Nb; j++)
			{
				tabb[j]= new Antibody();
			}
			while (Nba<target_sat)
			{

			for (int i = 0; i < Ng; i++)
			{
				if (tabg[i]->getstate()==true)
				{
					if (tabg[i]->getyposition()<tabg[i]->getradius())
					{
						for (int j=0;j<Nb;j++)
						{
          					tabg[i]->notifyzones();
          					tabg[i]->incrementtimeinzone();
							tabg[i]->bind(tabb[j],M,dG,T,probabt,tc,prefact);
          					if (tabg[i]->getstate()==false)
            				{
             					Nba++;
              					*tabg[Ng+Nba-1]=*tabg[i];
              					tabg[i]=new Antigene();
            				}
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
			t+=1;
			Nba=Nbp;
		}
			write_in(numero_du_fichier, modele_nom_fichier,Fr);//le numero de l'experience
			write_in(numero_du_fichier, modele_nom_fichier,t);//le temps adimenssionné avant la fin d'une experience
			write_endl(numero_du_fichier, modele_nom_fichier);
		}
	}
	return 0;
}
