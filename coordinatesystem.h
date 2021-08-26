#ifndef __COORDINATESYSTEM_H__
#define __COORDINATESYSTEM_H__

#include "vector.h"

class CoordinateSystem
{
	public:
		CoordinateSystem();
		virtual ~CoordinateSystem();

		vector i();
		vector j();
		vector k();

		void rotate( vector &v, float fi );

	private:
		vector m_i;
		vector m_j;
		vector m_k;
};

#endif