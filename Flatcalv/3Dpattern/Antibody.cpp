
#include "Antibody.h"
#include <stdlib.h>
#include <time.h>
#include <random>



Antibody::Antibody()
{
	
	m_state=true;
	m_yposition=0;
	m_xposition=(double)rand()/(float)(RAND_MAX);
	m_zposition=0.1*(double)rand()/(float)(RAND_MAX);
	m_binding=0;

}
double Antibody::getxposition() const

{
	return m_xposition;
}

double Antibody::getyposition() const

{
	return m_yposition;
}

double Antibody::getzposition() const

{
	return m_zposition;
}

bool Antibody::getstate() const
{
	return m_state;
}

void Antibody::changestate() //lie un antigene
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

double Antibody::getenergy() //retourne l'energie de liaison
{
	return m_binding;
}
