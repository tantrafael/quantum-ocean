#include "Mass.h"

Mass::Mass()
{
	m_mass  = 1.0f;
	m_pos   = vector(0,0,0);
	m_velo  = vector(0,0,0);
	m_acc   = vector(0,0,0);
	m_force = vector(0,0,0);
}

Mass::Mass( vector &v )
{
	m_mass  = 1.0f;
	m_pos   = v;
	m_velo  = vector(0,0,0);
	m_acc   = vector(0,0,0);
	m_force = vector(0,0,0);
}

Mass::Mass( vector &v, float m )
{
	m_mass  = m;
	m_pos   = v;
	m_velo  = vector(0,0,0);
	m_acc   = vector(0,0,0);
	m_force = vector(0,0,0);
}

Mass::~Mass() {}


float  Mass::mass()		{ return m_mass;  }
vector Mass::pos()		{ return m_pos;	  }
vector Mass::velo()		{ return m_velo;  }
vector Mass::acc()		{ return m_acc;	  }
vector Mass::force()	{ return m_force; }


void Mass::setPos  ( vector &v ) { m_pos   = v; }
void Mass::setVelo ( vector &v ) { m_velo  = v; }
void Mass::setAcc  ( vector &v ) { m_acc   = v; }


void Mass::move( vector &v ) { m_pos = m_pos + v; }

void Mass::rotate( vector &r0, vector &v, float fi )
{
	vector d = m_pos - r0;
	d.rotate( v, fi );
	m_pos = r0 + d;
}

void Mass::setForce( vector &v ) { m_force = v; }
void Mass::addForce( vector &v ) { m_force = m_force + v; }


void Mass::update()
{
	m_acc  = m_force / m_mass;
	m_velo = m_velo + m_acc;
	move( m_velo );

	m_force = vector(0,0,0);
}
