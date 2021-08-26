#include "Body.h"

Body::Body()
{
	m_omega  = vector(0,0,0);
	m_alpha  = vector(0,0,0);
	m_torque = vector(0,0,0);
	m_volume = 1.0f;
	m_pCoordinateSystem = new CoordinateSystem();
}

Body::Body( vector &v ):Mass( v )
{
	m_omega  = vector(0,0,0);
	m_alpha  = vector(0,0,0);
	m_torque = vector(0,0,0);
	m_volume = 1.0f;
	m_pCoordinateSystem = new CoordinateSystem();
}

Body::Body( vector &v, float m ):Mass( v, m )
{
	m_omega  = vector(0,0,0);
	m_alpha  = vector(0,0,0);
	m_torque = vector(0,0,0);
	m_volume = 1.0f;
	m_pCoordinateSystem = new CoordinateSystem();
}

Body::~Body() {}


vector Body::pos()				  { return cm();	 }
float  Body::inertia( vector &p ) { return 1.0f;	 }
vector Body::cm()				  { return m_pos;	 }
vector Body::omega()			  { return m_omega;  }
vector Body::alpha()			  { return m_alpha;  }
vector Body::torque()			  { return m_torque; }
float  Body::volume()			  { return m_volume; }

CoordinateSystem* Body::getCoordinateSystem() { return m_pCoordinateSystem; }

void Body::setOmega ( vector &v ) { m_omega  = v; }
void Body::setTorque( vector &v ) { m_torque = v; }
void Body::addTorque( vector &v ) { m_torque = m_torque + v; }

void Body::rotate( vector &v, float fi )
{
	rotate( cm(), v, fi );
}

void Body::rotate( vector &r0, vector &v, float fi )

{
	Mass::rotate( r0, v, fi );
	m_pCoordinateSystem->rotate( v, fi );
}


void Body::update()
{
	Mass::update();

	m_alpha = m_torque / inertia( m_torque );
	m_omega = m_omega + m_alpha;
	rotate( m_omega, norm( m_omega ) );

	m_torque = vector(0,0,0);
}
