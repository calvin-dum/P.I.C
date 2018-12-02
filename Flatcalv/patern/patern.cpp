/* compiler avec : c++ -Wall -O3 -std=c++11 Antigene.cpp Antibody.cpp patern.cpp -lm -DAFFICHAGE `sdl2-config --cflags --libs`


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
#ifdef AFFICHAGE
using namespace std;
const unsigned largeur_de_l_affichage=480, hauteur_de_l_affichage=480;
const Uint8 couleurs[][4]=
  {
    { 0,     0, 255, 255 }, /* bleu */
    { 255, 255,   0, 255 }, /* jaune */
    { 0,     0,   0, 255 }, /* noir */
  };
const int bleu= 0, jaune= 1, noir= 2;
SDL_Window * fenetre1;
SDL_Renderer * rendeur1;
static void trace_antigene(float x, float y, float rayon, int numero_de_couleur)
{
	SDL_SetRenderDrawColor(rendeur1, couleurs[numero_de_couleur][0],
	couleurs[numero_de_couleur][1], couleurs[numero_de_couleur][2],
	couleurs[numero_de_couleur][3]);
	SDL_Rect r= {(int)((x-rayon/2) * largeur_de_l_affichage),
	             (int)((y-rayon/2) * hauteur_de_l_affichage),
	             (int)(rayon * largeur_de_l_affichage),
	             (int)(rayon * hauteur_de_l_affichage)};
	SDL_RenderDrawRect(rendeur1, &r);
}
#endif

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
	int fin_demandee= 0;
	#ifdef AFFICHAGE
	SDL_Event evenement;
/* Initialiser la bibliotheque SDL2 */
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		fprintf(stderr, "Impossible d'initialiser SDL2: %s\n", SDL_GetError());
		exit(1);
	}
/* Initialiser une premiere fenetre (on peut en ouvrir d'autres). */
	fenetre1= SDL_CreateWindow("Fenetre 1",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	largeur_de_l_affichage, hauteur_de_l_affichage, SDL_SWSURFACE);
	if ( fenetre1 == NULL ) 
	{
		fprintf(stderr, "Je n'ai pas reussi a creer la premiere fenetre "
         	"de taille %ux%u pour la raison suivante : %s\n",
                largeur_de_l_affichage, hauteur_de_l_affichage,
                SDL_GetError());
		exit(1); 
	}
	rendeur1= SDL_CreateRenderer(fenetre1, -1, 0);
	if ( rendeur1 == NULL ) 
	{
	fprintf(stderr, "Je n'ai pas reussi a creer le premier rendeur "
		"pour la raison suivante : %s\n",
		SDL_GetError());
		exit(1);
	}
/* Remplir la fenetre avec un fond noir */
	SDL_SetRenderDrawColor(rendeur1, 0, 0, 0, 255);
	SDL_RenderClear(rendeur1);
	#endif

	int numero_du_fichier= 1;
	int numero_d_image= 0;
	char* modele_nom_fichier = "test%04d.txt";
//seed random gaussien
	random_device rd{};
	mt19937 gen{rd()};
	define_name(modele_nom_fichier, numero_du_fichier);
// values near the mean are the most likely
// standard deviation affects the dispersion of generated values from the mean

	double tc=pow(10,-14); //??? Constante de temps pour adimensionnement choisie inferieur à 10-¹²
	double m=3.18*pow(10,-23); //masse de la molecule
	double xc=pow(10,-3); //Longueur pour adimensionnement telque Br~1 pour tc
	double l=1.8*pow(10,-10); // amortissement lambda
	double Fr=0.066; //ecart type de la force random
	double A=-l*tc/m; //A et Br sont les paramètres restant après adimensionnement ~1
	double Br=Fr*pow(tc,2)/(m*xc); // Br est précisé
	int Ng=50; //Nombre de antigenes en solution
	int Nb=1; //Nombre d'anticorps en solution

	int Nba=0; //Nombre servant à compter le nombre d'anticorps libre
	int T=0; //Nombre servant à avoir le temps
	normal_distribution<double> d{0,Br};

	srand (time(NULL));//seed la fonction random sur le temps

	Antigene *tabg[Ng]; 
	for(int i=0; i<Ng; i++)
	{
		tabg[i]=new Antigene(); //creer un tableau contenant Ng adresses d'antigene
	}
	Antibody *tabb[Nb];
	for(int j=0;j<Nb; j++)
	{
		tabb[j]= new Antibody(); //creer un tableau contenant Nb adresses d'antibody
	}	
	while (! fin_demandee) // Afficher le mouvement de la cellule 2 tant que l'utilisateur n'a pas demande la fin du programme. 
	{
		#ifdef AFFICHAGE
		/* On doit (avec SDL2) effacer toute la fenetre : */
		SDL_SetRenderDrawColor(rendeur1, 0, 0, 0, 255);
		SDL_RenderClear(rendeur1);
		#endif
	// Mouvement brownien des particules
	for (int i = 0; i < Ng; i++)
	{
		if (tabg[i]->getstate()==true) //la flèche permet d'appliquer une méthode à l'objet situé à l'adresse à gauche de la flèche
		{
			if (tabg[i]->getyposition()<tabg[i]->getradius())
			{
				for (int j=0;j<Nb;j++)
				{
					tabg[i]->bind(tabb[j]);
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
	if ((Nbp-Nba)!=0)
	{
		write_in(numero_du_fichier, modele_nom_fichier, Nba);
		write_in(numero_du_fichier, modele_nom_fichier, T);
		write_endl(numero_du_fichier, modele_nom_fichier);
	}
	T+=1;
	Nba=Nbp;
	

	#ifdef AFFICHAGE
	for (int i = 0; i < Ng; i++)
	{
		trace_antigene(tabg[i]->getxposition(), tabg[i]->getyposition(), 0.05, jaune);
	}
	for (int j=0;j<Nb;j++)
	{
		trace_antigene(tabb[j]->getxposition(),tabb[j]->getyposition(),0.05,bleu);
	}
	/* Mettre a jour l'affichage */
	SDL_RenderPresent(rendeur1);
	/* Enregistrer l'image dans un fichier*/
	/*numero_d_image++;
	if (numero_d_image < 10000)
	{
		SDL_Surface * s= SDL_CreateRGBSurface(0, largeur_de_l_affichage,hauteur_de_l_affichage, 32,0x00ff0000, 0x0000ff00, 0x000000ff, 			0xff000000);
		SDL_RenderReadPixels(rendeur1, NULL, SDL_PIXELFORMAT_ARGB8888,s->pixels, s->pitch);
		char nom_de_fichier[256];
		snprintf(nom_de_fichier, sizeof(nom_de_fichier), "image%04d.bmp",numero_d_image);
		if (SDL_SaveBMP(s, nom_de_fichier))
			fputs(SDL_GetError(), stderr);
		SDL_FreeSurface(s);
	}*/
	if (SDL_PollEvent(&evenement))
	
		switch (evenement.type)
        	{
	        	case SDL_QUIT: fin_demandee= 1; break;
        	}
	#endif
	}
	/* Fermer l'affichage */
	#ifdef AFFICHAGE
	SDL_DestroyWindow(fenetre1);
	SDL_Quit();
	#endif
	return 0;
}
