#ifndef DEF_ANTIGENE
#define DEF_ANTIGENE

#include <iostream>
#include <string>
#include<math.h>
#include "Antibody.h"
class Antigene
{
	public:
	Antigene(); //constructeur
	void bind(Antibody *cible, double M, double dG, double T);
	void motion(double A,double Br);
	void changestate();
	bool getstate() const;
	double getxposition() const;
	double getyposition() const;
	double getradius() const;
	private:
  
	bool m_state;
	double m_xposition;
	double m_yposition;
	double m_xspeed;
	double m_yspeed;
	double m_cinetic;
	double m_radius;  
};

#endif

