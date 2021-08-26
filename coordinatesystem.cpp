#include <math.h>

#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem()
{
	m_i = vector( 1.0f, 0, 0 );
	m_j = vector( 0, 1.0f, 0 );
	m_k = vector( 0, 0, 1.0f );
}

CoordinateSystem::~CoordinateSystem() {}

vector CoordinateSystem::i() { return m_i; }
vector CoordinateSystem::j() { return m_j; }
vector CoordinateSystem::k() { return m_k; }

void CoordinateSystem::rotate( vector &v, float fi )
{
	m_i.rotate( v, fi );
	m_j.rotate( v, fi );
	m_k.rotate( v, fi );

	m_i.normate();		// För att
	m_j.normate();		// undvika
	m_k.normate();		// avrundningsfel
}
