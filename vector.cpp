#include "vector.h"

//--------------------------------------------------------------------------
// Constructors, destructors
//--------------------------------------------------------------------------

vector::vector() {}

vector::vector( float x, float y, float z )
{
	m_x = x;
	m_y = y;
	m_z = z;
}

vector::~vector() {}


//--------------------------------------------------------------------------
// Access
//--------------------------------------------------------------------------

float vector::x()	{ return m_x; }
float vector::y()	{ return m_y; }
float vector::z()	{ return m_z; }


//--------------------------------------------------------------------------
// Operators
//--------------------------------------------------------------------------

vector vector::operator+ ( vector &v )
{	return vector( x()+v.x(), y()+v.y(), z()+v.z() );	}

vector vector::operator- ( vector &v )
{	return vector( x()-v.x(), y()-v.y(), z()-v.z() );	}

vector vector::operator* ( float t )
{	return vector( x()*t, y()*t, z()*t );	}

vector vector::operator/ ( float t )
{	return vector( x()/t, y()/t, z()/t );	}

float vector::operator* ( vector &v )	// skalärprodukt
{	return ( x()*v.x() + y()*v.y() + z()*v.z() );	}

vector vector::operator^ ( vector &v )	// vektorprodukt
{
	return vector(	y()*v.z() - z()*v.y(),
					z()*v.x() - x()*v.z(),
					x()*v.y() - y()*v.x() );
}


//--------------------------------------------------------------------------
// Rotation
//--------------------------------------------------------------------------

void vector::rotate( vector &v, float fi )	// kring vektor v, med vinkel fi.
{
										// Låt rotationsaxeln utgöra z-axeln i ett
										// tänkt koordinatsystem, med enhetsvektorer x1, y1, z1.

	if( norm( v ) > 0.001f )			// Bara rotation kring en vektor
										// skild från 0 ger resultat.
	{
		vector z1 = normalize( v );		// Vektorn v med rotationsaxelns riktning ger z1
										// genom normering.

		float s = norm( z1 ^ *this );	// Beräkna längden av projektionen
										// på normalplanet till rotationsaxeln.
										// Den ska bli vårt x1-värde.

										// Skulle detta vara 0,
										// d.v.s. vektorn som ska roteras
										// sammanfaller med rotationsaxeln
										// påverkas den ej.

		if( s > 0.001f )				// I annat fall är s > 0, men vi skriver
		{								// 0.0001 för säkerhets skull
										// så att inga avrundningar ska kunna
										// orsaka division med 0 vid normering.

			float t = z1 * (*this);		// Beräkna längden av projektionen
										// på rotationsaxeln. Den blir vår z1-koordinat.

			vector w = *this - z1*t;	// Låt projektionen på normalplanet till rotationsaxeln
										// ange riktningen för vår tänkta x-axel.
			vector x1 = normalize(w);	// Normering ger x1.
									
			vector y1 = x1 ^ z1;		// y1 är vinkelrät mot x1 och z1,
										// och ges av deras vektorprodukt.

			*this = x1*s*cosf(fi) +		// I vårt tänkta koordinatsystem blir
					y1*s*sinf(fi) +		// rotationen kring z-axeln
					z1*t;				// nu en enkel beräkning.
		}
	}
}


vector rotation( vector &pos, vector &axis, float fi )
{
	vector r = pos;
	r.rotate( axis, fi );
	return r;
}


//--------------------------------------------------------------------------
// Reflection
//--------------------------------------------------------------------------

vector reflection( vector &v, vector &n )
{
	return v - n * (v*n*2);
}


//--------------------------------------------------------------------------
// Normation
//--------------------------------------------------------------------------

float norm( vector &v )
{	return sqrtf( v.x()*v.x() + v.y()*v.y() + v.z()*v.z() );	}


vector normalize( vector &v )
{
	float n = norm( v );
	if( n > 0.0f ) return v / n;
	else		   return vector(0,0,0);
}


void vector::normate()
{
	float n = norm( *this );

	m_x = m_x / n;
	m_y = m_y / n;
	m_z = m_z / n;
}
