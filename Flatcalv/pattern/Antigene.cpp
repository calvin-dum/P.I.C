

#include "Antigene.h"
#include "Antibody.h"
#include "Fct/Randomness/randoms.h"
#include <stdlib.h>
#include <time.h>
#include <random>
#include<math.h>
#include <iostream>

using namespace std;



Antigene::Antigene() //constructeur
{
	m_state=true;
	m_xposition=(double)rand()/(float)(RAND_MAX);
	m_yposition=(double)rand()/(float)(RAND_MAX);
	m_xspeed=0;
	m_yspeed=0;
	m_radius=0.1;
	m_cinetic=0;
}

void Antigene::bind(Antibody *cible, double M,double dG, double T, double probab) //méthode testant si un anticorps dispo est dans le rayon de antigene et alors change l'etat des deux en false
{
	if (m_state==true) //si l'antigene n'est pas apparié peut paraitre redondant mais permet d'éviter echange entre deux anticorps proches
	{
		if (cible->getstate()==true) //si l'anticorps n'est pas apparié
		{
			double xcible=cible->getxposition();
			if ( (pow(xcible-m_xposition,2)+pow(m_yposition,2))< pow(m_radius,2)) //on regarde si l'anticorps est dans la zone effet, longueur au carré
			{
				double p=uniform(0.0,1.0);
				std::cout << "p" << p << '\n';
				std::cout << "compared to" << '\n';
				std::cout << "proba" << probab << '\n';
				//if (l> exp(-(dG-(M*(pow(m_xspeed,2)+pow(m_yspeed,2)))/2)/(T*1.3*pow(10,-23))))//proba est exp(-beta (Delta E)) delta E étant dG- somme energies sur x et y
				if(p<probab)
				{
					m_state=false;
					cible->changestate(); // on lie les deux
				}
			}
		}
	 }
}

bool Antigene::getstate() const //accede à l'état true=libre false=lié
{
	return m_state;
}

void Antigene::motion(double A, double Br) //fait se déplacer selon Langevin de paramètres adimensionnés A et Br
{
	random_device rd{};
	mt19937 gen{rd()};
	normal_distribution<double> d{0,Br}; //on initialise la force random
	m_xspeed+=d(gen)+A*m_xspeed;
	m_yspeed+=d(gen)+A*m_yspeed;
	m_xposition+=m_xspeed;
	m_yposition+=m_yspeed;
	m_xposition-=floor(m_xposition);//conditions periodiques sur l'horizontal
	if (m_yposition<0)
	{
		m_yposition=-m_yposition;
	}
	if ( m_yposition>1)
	{
		m_yposition=2-m_yposition;
	}
}

void Antigene::changestate() //lie un antigene
{
	if (m_state==true)
	{
		m_state=false;
		m_xspeed=0;
		m_yspeed=0;
	}
	else
	{
		m_state=true;
	}
}

double Antigene::getxposition() const //accede à la position x
{
	return m_xposition;
}

double Antigene::getyposition() const //accede à la position y
{
	return m_yposition;
}

double Antigene::getradius() const //accede au rayon de la zone d'effet
{
	return m_radius;
}

double Antigene::getxspeed() const //accede au rayon de la zone d'effet
{
	return m_xspeed;
}

double Antigene::getyspeed() const //accede au rayon de la zone d'effet
{
	return m_yspeed;
}
