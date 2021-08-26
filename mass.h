#ifndef __MASS_H__
#define __MASS_H__

#include "vector.h"


class Mass
{
	public:
		Mass();
		Mass( vector &v );
		Mass( vector &v, float m );
		virtual ~Mass();

		virtual float  mass();
		virtual vector pos();
		virtual vector velo();
		virtual vector acc();
		virtual vector force();

		virtual void setPos  ( vector &v );
		virtual void setVelo ( vector &v );
		virtual void setAcc  ( vector &v );

		virtual void move( vector &v );
		virtual void rotate( vector &r0, vector &v, float fi );
		virtual void setForce( vector &v );
		virtual void addForce( vector &v );
		virtual void update();

	protected:
		float  m_mass;		// massa
		vector m_pos;		// masscentrums position
		vector m_velo;		// hastighet
		vector m_acc;		// acceleration
		vector m_force;		// kraft på masscentrum
};

#endif
