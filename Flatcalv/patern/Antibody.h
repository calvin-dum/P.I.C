#ifndef DEF_ANTIBODY
#define DEF_ANTIBODY


class Antibody
{

	public:
	Antibody();
	double getxposition() const;
	double getyposition() const;
	bool getstate() const;
	void changestate();
	double getenergy();
	private:
  
	bool m_state;
	double m_xposition;
	double m_yposition;
	double m_binding;
};

#endif

