

#include "Antigene.h"
#include "Antibody.h"
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace std;



Antigene::Antigene() //constructeur 
{
	srand (time(NULL));  //seed rand sur le temps
	m_state=true;
	m_xposition=(double)rand()/(float)(RAND_MAX);
	m_yposition=(double)rand()/(float)(RAND_MAX);
	m_xspeed=0;
	m_yspeed=0;
	m_radius=0.1;
	m_cinetic=0;
}

void Antigene::bind(Antibody *cible) //méthode testant si un anticorps dispo est dans le rayon de antigene et alors change l'etat des deux en false
{
	if (m_state==true) //si l'antigene n'est pas apparié peut paraitre redondant mais permet d'éviter echange entre deux anticorps proches
	{
		if (cible->getstate()==true) //si l'anticorps n'est pas apparié
		{
			double xcible=cible->getxposition(); 
			if ( (pow(xcible-m_xposition,2)+pow(m_yposition,2))< m_radius) //on regarde si l'anticorps est dans la zone effet
			{
				m_state=false;
				cible->changestate(); // on lie les deux
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
