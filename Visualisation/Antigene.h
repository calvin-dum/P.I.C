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
	void bind(Antibody *cible, double M, double dG, double T, double probabt, double tc, double prefact);
	void motion(double A,double Br);
	void changestate();
	void notifyzones();
	void pull_out();
	void incrementtimeinzone();
	bool getstate() const;
	bool getzones() const;
	int gettimeinzone() const;
	double getxposition() const;
	double getyposition() const;
	double getzposition() const;
	double getradius() const;
	double getxspeed() const;
	double getyspeed() const;
	private:

	bool m_state;
	bool in_zones;
	int time_in_zone;
	double m_xposition;
	double m_yposition;
	double m_zposition;
	double m_xspeed;
	double m_yspeed;
	double m_zspeed;
	double m_kinetic;
	double m_radius;
};

#endif
