#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <windows.h>
#include <string>
#include <math.h>
#include <d3d8.h>
#include <d3dx8math.h>
#include <mmsystem.h>
#pragma comment ( lib, "d3d8.lib" )
#pragma comment ( lib, "d3dx8.lib" )
#pragma comment ( lib, "dxguid.lib" )
#pragma comment ( lib, "winmm.lib" )

using namespace std;

#include "vector.h"

class Game;


class Color
{
	public:
		Color();
		Color( int r, int g, int b );
		virtual ~Color();

		Color operator+ ( Color &c );
		Color operator* ( float t );

		void clamp();

		int r();
		int g();
		int b();

		D3DCOLOR getColor();

		friend Color clamp( Color &color );

	protected:
		int m_r, m_g, m_b;
		D3DCOLOR m_color;
};


class Graphics
{
	public:
		Graphics();
		Graphics( Game *pGame );
		virtual ~Graphics();

		void init( Game *pGame );
		void ClearBuffer( Color *pColor );
		void BeginScene();
		void EndScene();
		void Present();
		void PutPixel( int x, int y, Color &color );

		void ColumnColor( int x, int y1, int y2, Color &color );
		void DrawColumn( int x, int y_top, int y_bottom, Color **m_array );

		void ColumnTexture( int x,
							int y1,
							int y2,
							HBITMAP hBmp,
							int u);

		IDirect3DSurface8* LoadBitmap( string filename );

	protected:
		Game *m_pGame;
		LPDIRECT3D8 m_pD3D;
		LPDIRECT3DDEVICE8 m_pD3Ddevice;

		HRESULT m_InitD3D();
		void WINAPI m_TermD3D();
};

#endif
