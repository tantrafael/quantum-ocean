#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Body.h"
#include "Graphics.h"

class Game;


class Light : public Body
{
	public:
		Light();
		Light( vector &pos, Color &color );
		~Light();

		Color color();

	protected:
		Game *m_pGame;

		Color m_color;
		float m_intensity;
};

#endif