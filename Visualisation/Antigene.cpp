

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
	m_zposition=100*(double)rand()/(float)(RAND_MAX);
	m_xspeed=0;
	m_yspeed=0;
	m_zspeed=0;
	m_radius=0.01;
	m_kinetic=0;
	in_zones=0;
	time_in_zone=1;
}

void Antigene::bind(Antibody *cible, double M,double dG, double T, double probabt, double tc, double prefact) //méthode testant si un anticorps dispo est dans le rayon de antigene et alors change l'etat des deux en false
{
	if (m_state==true) //si l'antigene n'est pas apparié peut paraitre redondant mais permet d'éviter echange entre deux anticorps proches
	{
		if (cible->getstate()==true) //si l'anticorps n'est pas apparié
		{
			double xcible=cible->getxposition();
			double zcible=cible->getzposition();
			if ( (pow(xcible-m_xposition,2)+pow(m_yposition,2)+pow(zcible-m_zposition,2))< pow(m_radius,2)) //on regarde si l'anticorps est dans la zone effet, longueur au carré
			{
				double p=uniform(0.0,1.0);
				if(p<(double) prefact*erfcl(sqrt((double)probabt/(time_in_zone*tc))))
				{
					changestate();
					cible->changestate(); // on lie les deux
				}
			}
		}
	 }
}

void Antigene::pull_out()
{

	m_yposition=0.9;

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
	m_zspeed+=d(gen)+A*m_zspeed;
	m_xposition+=m_xspeed;
	m_yposition+=m_yspeed;
	m_zposition+=m_zspeed;
	m_xposition-=floor(m_xposition);//conditions periodiques sur l'horizontal
//conditions rebond sur la verticale
	if (m_yposition<0)
	{
		m_yposition=-m_yposition;
	}
	if ( m_yposition>1)
	{
		m_yposition=2-m_yposition;
	}

//conditions rebond sur la hauteur
	if (m_zposition<0)
	{
		m_zposition=-m_zposition;
	}
	if ( m_zposition>100)
	{
		m_zposition=200-m_zposition;
	}
}

void Antigene::changestate() //lie un antigene
{
	if (m_state==true)
	{
		m_state=false;
		m_xspeed=0;
		m_yspeed=0;
		m_zspeed=0;
	}
	else
	{
		m_state=true;
	}
}

void Antigene::notifyzones() //modifie le booleen pour indiquer la zone
{
	if (m_yposition<m_radius)
	{
			if (! in_zones) {
				in_zones=true;
			}
	}
	//if (m_yposition>1.1*m_radius)
	else
	{
		//if (in_zones) {
			in_zones=false;
		//}

	}

}

void Antigene::incrementtimeinzone()
{

	if (in_zones) {
		time_in_zone++;
	}
	else
	{
		time_in_zone=1;

	}

}

bool Antigene::getzones() const //liste de deux booléens, 1er renseigne si antigene est dans petite zone, l'autre pour une zone plus grande.
{
	return in_zones;

}


int Antigene::gettimeinzone() const //outil pour multiplier la probab en fonction du temps en in_zones
{

	return time_in_zone;

}
double Antigene::getxposition() const //accede à la position x
{
	return m_xposition;
}

double Antigene::getyposition() const //accede à la position y
{
	return m_yposition;
}

double Antigene::getzposition() const //accede à la position y
{
	return m_zposition;
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
