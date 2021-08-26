#ifndef __INPUT_H__
#define __INPUT_H__

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dxguid.lib" )

class Game;


class Input
{
	public:
		Input();
		virtual ~Input();

		void init( Game *pGame );
		void read();

	protected:
		Game *m_pGame;

		LPDIRECTINPUT8 m_pDI;
		LPDIRECTINPUTDEVICE8 m_pKeyboard;

		HRESULT m_InitDI();
		void WINAPI m_TermDI();
};

#endif