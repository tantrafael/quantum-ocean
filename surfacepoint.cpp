#include "SurfacePoint.h"

SurfacePoint::SurfacePoint()
{
}

SurfacePoint::SurfacePoint( vector &v ):Mass(v)
{
	m_mass  = 1.0f;
}

SurfacePoint::~SurfacePoint() {}
