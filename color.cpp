#include "Graphics.h"

Color::Color()
{
	m_r = 0;
	m_g = 0;
	m_b = 0;

	m_color = D3DCOLOR_XRGB( m_r, m_g, m_b );
}

Color::Color( int r, int g, int b )
{
	m_r = r;
	m_g = g;
	m_b = b;

	m_color = D3DCOLOR_XRGB( m_r, m_g, m_b );
}

Color::~Color()
{}


Color Color::operator+ ( Color &c )
{
	int r, g, b;

	r = m_r + c.r();
	g = m_g + c.g();
	b = m_b + c.b();

	return Color(r,g,b);
}


Color Color::operator* ( float t )
{
	int r, g, b;

	r = int( m_r * t );
	g = int( m_g * t );
	b = int( m_b * t );

	return Color(r,g,b);
}


void Color::clamp()
{
	if( m_r < 0 ) { m_r = 0; }
	if( m_g < 0 ) { m_g = 0; }
	if( m_b < 0 ) { m_b = 0; }

	if( m_r > 255 ) { m_r = 255; }
	if( m_g > 255 ) { m_g = 255; }
	if( m_b > 255 ) { m_b = 255; }
}


int Color::r() { return m_r; }
int Color::g() { return m_g; }
int Color::b() { return m_b; }


D3DCOLOR Color::getColor()
{
	return m_color;
}


Color clamp( Color &color )
{
	int r = color.r();
	int g = color.g();
	int b = color.b();

	if( r < 0 ) { r = 0; }
	if( g < 0 ) { g = 0; }
	if( b < 0 ) { b = 0; }

	if( r > 255 ) { r = 255; }
	if( g > 255 ) { g = 255; }
	if( b > 255 ) { b = 255; }

	return Color( r, g, b );
}
