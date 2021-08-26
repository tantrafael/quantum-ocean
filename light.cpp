#include "Light.h"

Light::Light()
{}

Light::Light( vector &pos, Color &color ):Body( pos )
{
	m_pGame = NULL;
	m_color = color;
	m_intensity = 1.0f;
}

Light::~Light() {}

Color Light::color() { return m_color; }