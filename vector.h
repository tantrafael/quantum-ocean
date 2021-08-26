#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>


class vector
{
	public:
		vector();
		vector( float x, float y, float z );
		virtual ~vector();

		float x();
		float y();
		float z();

		vector operator+ ( vector &v );
		vector operator- ( vector &v );
		vector operator* ( float t );
		vector operator/ ( float t );
		float  operator* ( vector &v );
		vector operator^ ( vector &v );

		void rotate( vector &v, float fi );
		friend vector rotation( vector &pos, vector &axis, float fi );

		friend vector reflection( vector &v, vector &n );

		friend float norm( vector &v );
		friend vector normalize( vector &v );
		void normate();

	protected:
		float  m_x;
		float  m_y;
		float  m_z;
};

#endif
