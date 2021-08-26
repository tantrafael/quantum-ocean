#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <windows.h>

#include "Body.h"
#include "SurfacePoint.h"

class Game;


class Camera : public Body
{
	public:
		Camera();
		Camera( vector v );
		Camera( vector v, float m );
		~Camera();

		void init( Game *pGame );

		float R();
		RECT* ViewPort();

		POINT  project   ( vector &pos );
		vector translate ( vector &pos );

		void update();

	protected:
		Game *m_pGame;

		float m_R;
		POINT m_P0;
		RECT  m_ViewPort;

		float m_t;
};

#endif