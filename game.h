#ifndef __GAME_H__
#define __GAME_H__

#include <windows.h>

#include "Window.h"
#include "Graphics.h"
#include "World.h"
#include "Camera.h"
#include "Input.h"
//#include "Score.h"
//#include "Sound.h"


class Game
{
	public:
		Game();
		Game( Window *pWindow );
		virtual ~Game();

		Window*	  window();
		Graphics* graphics();
		World*	  world();
		Input*	  input();

		void update();

	protected:
		Window	 *m_pWindow;
		Graphics *m_pGraphics;
		World	 *m_pWorld;
		Input	 *m_pInput;
//		Score	 *m_pScore;
//		Sound	 *m_pSound;
};

#endif