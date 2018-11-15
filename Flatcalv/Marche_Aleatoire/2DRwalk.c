/* Essai de programme utilisant SDL2. Compiler avec :
cc -Wall -O3 -std=c99 exemple.c -DAFFICHAGE `sdl2-config --cflags --libs`
(attention, sous Windows avec MinGW il est indispensables que les
bibliotheques, donc `sdl-config --cflags --libs`, soient a la fin de la
ligne de commande, sinon l'edition de lien echoue).
 Pour assembler un film a partir des images enregistrees dans des
fichiers, utiliser :
ffmpeg -f image2 -pattern_type glob -framerate 100 -i 'image*.bmp' film.avi
 */
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

  SDL_Rect r= {(x-rayon/2) * largeur_de_l_affichage,
               (y-rayon/2) * hauteur_de_l_affichage,
               rayon * largeur_de_l_affichage,
               rayon * hauteur_de_l_affichage};
  SDL_RenderDrawRect(rendeur1, &r);
}
#endif

int main(int argc, char* argv[])
{
  int fin_demandee= 0;
#ifdef AFFICHAGE
  SDL_Event evenement;

  /* Initialiser la bibliotheque SDL2 */
  if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    fprintf(stderr, "Impossible d'initialiser SDL2: %s\n", SDL_GetError());
    exit(1);
  }

  /* Initialiser une premiere fenetre (on peut en ouvrir d'autres). */
  fenetre1= SDL_CreateWindow("Fenetre 1",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    largeur_de_l_affichage, hauteur_de_l_affichage, SDL_SWSURFACE);
  if ( fenetre1 == NULL ) {
    fprintf(stderr, "Je n'ai pas reussi a creer la premiere fenetre "
            "de taille %ux%u pour la raison suivante : %s\n",
            largeur_de_l_affichage, hauteur_de_l_affichage,
            SDL_GetError());
    exit(1);
  }
  rendeur1= SDL_CreateRenderer(fenetre1, -1, 0);
  if ( rendeur1 == NULL ) {
    fprintf(stderr, "Je n'ai pas reussi a creer le premier rendeur "
            "pour la raison suivante : %s\n",
            SDL_GetError());
    exit(1);
  }
   /* Remplir la fenetre avec un fond noir */
  SDL_SetRenderDrawColor(rendeur1, 0, 0, 0, 255);
  SDL_RenderClear(rendeur1);
#endif
//initialise la matrice des positions
double position[2][5];
  for (int i = 0; i < 5; i++) {
  position[0][i]= (double)rand()/(float)(RAND_MAX),
  position[1][i]= (double)rand()/(float)(RAND_MAX);

}

  int numero_d_image= 0;

//seed random gaussien
random_device rd{};
mt19937 gen{rd()};

// values near the mean are the most likely
// standard deviation affects the dispersion of generated values from the mean
normal_distribution<double> d{0,0.001};

  //seed la fonction random sur le temps
    srand (time(NULL));
    /* Afficher le mouvement de la cellule 2 tant que l'utilisateur
      n'a pas demande la fin du programme. */
  while (! fin_demandee)
    {
#ifdef AFFICHAGE
    /* On doit (avec SDL2) effacer toute la fenetre : */
    SDL_SetRenderDrawColor(rendeur1, 0, 0, 0, 255);
    SDL_RenderClear(rendeur1);
#endif

// Mouvement brownien des particules
for (int i = 0; i < 5; i++) {
if (position[1][i]>0.1) {
  /* //Mouvement aleatoire non gaussien
  position[0][i] += 0.05*(((double)rand()/(float)(RAND_MAX))-0.5);
  position[1][i] += 0.05*(((double)rand()/(float)(RAND_MAX))-0.5);*/
  position[0][i] += d(gen);
  position[1][i] += d(gen);
  position[0][i] -= floor(position[0][i]); //condition periodique sur x
  if (position[1][i]>1) {
    position[1][i] = 2-position[1][i];
  }
}
}
//if (y_antigene_1>0.1 /*Condition de blocage au bord */) {
/*
    x_antigene_1 += 0.1*(((double)rand()/(float)(RAND_MAX))-0.5);
    y_antigene_1 += 0.05*(((double)rand()/(float)(RAND_MAX))-0.5);
    x_antigene_1 -= floor(x_antigene_1);
    if (y_antigene_1>1) {
      y_antigene_1 = 2-y_antigene_1;
    }
  // y_antigene_1 -= floor(y_antigene_1);
  }
*/

#ifdef AFFICHAGE

for (int i = 0; i < 5; i++) {

    trace_antigene(position[0][i], position[1][i], 0.05, jaune);
  }
     /* Mettre a jour l'affichage */
    SDL_RenderPresent(rendeur1);

/*
   /* Enregistrer l'image dans un fichier
    numero_d_image++;
    if (numero_d_image < 10000)
      {
      SDL_Surface * s= SDL_CreateRGBSurface(0, largeur_de_l_affichage,
        hauteur_de_l_affichage, 32,
        0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
      SDL_RenderReadPixels(rendeur1, NULL, SDL_PIXELFORMAT_ARGB8888,
                           s->pixels, s->pitch);
      char nom_de_fichier[256];
      snprintf(nom_de_fichier, sizeof(nom_de_fichier), "image%04d.bmp",
               numero_d_image);
      if (SDL_SaveBMP(s, nom_de_fichier))
        fputs(SDL_GetError(), stderr);
      SDL_FreeSurface(s);
      }
*/
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
