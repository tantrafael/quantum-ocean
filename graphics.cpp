#include "Graphics.h"
#include "Game.h"


Graphics::Graphics()
{
	m_pGame		  = NULL;
	m_pD3D		  = NULL;
	m_pD3Ddevice  = NULL;
}

Graphics::~Graphics()
{
	m_TermD3D();
}


void Graphics::init( Game *pGame )
{
	m_pGame = pGame;
	m_InitD3D();
}


//-----------------------------------------------------------------------------
// m_InitD3D()
//-----------------------------------------------------------------------------
HRESULT Graphics::m_InitD3D()
{
	HRESULT hr;
	
	// Create D3D object
	m_pD3D = Direct3DCreate8( D3D_SDK_VERSION );
	
	if( m_pD3D == NULL )
		return E_FAIL;

	// Get current desktop display mode
	D3DDISPLAYMODE d3ddm;
	hr = m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	if( FAILED(hr) )
        return E_FAIL;

	// Set parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.BackBufferWidth  = m_pGame->window()->cols();
	d3dpp.BackBufferHeight = m_pGame->window()->rows();
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = m_pGame->window()->hWnd();
	d3dpp.Windowed = 1;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;	// För att kunna skriva
														// till backbuffer

	// Create D3D device
	hr = m_pD3D->CreateDevice( D3DADAPTER_DEFAULT,
							   D3DDEVTYPE_HAL,
							   m_pGame->window()->hWnd(),
							   D3DCREATE_SOFTWARE_VERTEXPROCESSING,
							   &d3dpp,
							   &m_pD3Ddevice );
	if( FAILED(hr) )
		return E_FAIL;

	return S_OK;
}


//-----------------------------------------------------------------------------
// m_TermD3D()
//-----------------------------------------------------------------------------
void WINAPI Graphics::m_TermD3D()
{
	if (m_pD3D)
	{
		if (m_pD3Ddevice)
		{
			m_pD3Ddevice->Release();
			m_pD3Ddevice = NULL;
		}
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}


//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------
void Graphics::ClearBuffer( Color *pColor )
{
	m_pD3Ddevice->Clear( 0, NULL, D3DCLEAR_TARGET,
						 pColor->getColor(), 1.0f, 0 );
}


void Graphics::BeginScene()
{
	m_pD3Ddevice->BeginScene();
}


void Graphics::EndScene()
{
	m_pD3Ddevice->EndScene();
}


void Graphics::Present()
{
	m_pD3Ddevice->Present( NULL, NULL, NULL, NULL );
}


//-----------------------------------------------------------------------------
// PutPixel()
//-----------------------------------------------------------------------------
void Graphics::PutPixel( int x, int y, Color &color )
{
	IDirect3DSurface8 *pDstSurf;
	m_pD3Ddevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pDstSurf );

	D3DLOCKED_RECT lDstRect;
	pDstSurf->LockRect( &lDstRect, NULL, 0 );
	unsigned long bpp = 4;
	unsigned char *DstBuffer = (unsigned char *) lDstRect.pBits;
	unsigned long dst_basepos = 0, dst_bufpos = 0;

	dst_bufpos = y * lDstRect.Pitch + x * bpp;
	D3DCOLOR D3Dcolor = color.getColor();
	memcpy( &DstBuffer[dst_bufpos], &D3Dcolor, bpp );

	pDstSurf->UnlockRect();
}


//-----------------------------------------------------------------------------
// ColumnColor()
//-----------------------------------------------------------------------------
void Graphics::ColumnColor( int x, int y1, int y2, Color &color )
{
	IDirect3DSurface8 *pDstSurf;
	m_pD3Ddevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pDstSurf );

	D3DLOCKED_RECT lDstRect;
	pDstSurf->LockRect( &lDstRect, NULL, 0 );
	unsigned long bpp = 4;
	unsigned char *DstBuffer = (unsigned char *) lDstRect.pBits;
	unsigned long dst_basepos = 0, dst_bufpos = 0;

	int R = m_pGame->window()->rows();
	int y_start = y1;
	int	y_stop  = y2;
	if( y1 < 0 ) y_start = 0;
	if( y2 > R ) y_stop  = R;

	for( int y = y_start; y <= y_stop; y++ )
	{
		D3DCOLOR D3DColor = color.getColor();
		dst_bufpos = y * lDstRect.Pitch + x * bpp;

		memcpy( &DstBuffer[dst_bufpos], &D3DColor, bpp );
	}

	pDstSurf->UnlockRect();
}


//-----------------------------------------------------------------------------
// DrawColumn()
//-----------------------------------------------------------------------------
void Graphics::DrawColumn( int x, int y_top, int y_bottom, Color **array )
{
	IDirect3DSurface8 *pDstSurf;
	m_pD3Ddevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pDstSurf );

	D3DLOCKED_RECT lDstRect;
	pDstSurf->LockRect( &lDstRect, NULL, 0 );
	unsigned long bpp = 4;
	unsigned char *DstBuffer = (unsigned char *) lDstRect.pBits;
	unsigned long dst_basepos = 0, dst_bufpos = 0;

	for( int y = y_top; y < y_bottom; y++ )
	{
		D3DCOLOR D3DColor = array[ y ]->getColor();
		dst_bufpos = y * lDstRect.Pitch + x * bpp;
		memcpy( &DstBuffer[dst_bufpos], &D3DColor, bpp );
	}

	pDstSurf->UnlockRect();
}


//-----------------------------------------------------------------------------
// ColumnTexture()
//-----------------------------------------------------------------------------
void Graphics::ColumnTexture( int x,
							  int y1,
							  int y2,
							  HBITMAP hBmp,
							  int u )
{
	IDirect3DSurface8 *pDstSurf;
	m_pD3Ddevice->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pDstSurf );

	D3DLOCKED_RECT lDstRect;
	pDstSurf->LockRect( &lDstRect, NULL, 0 );
	unsigned long bpp = 4;
	unsigned char *DstBuffer = (unsigned char *) lDstRect.pBits;
	unsigned long dst_basepos = 0, dst_bufpos = 0;

	HDC dc = CreateCompatibleDC( NULL );
	SelectObject( dc, hBmp );

	COLORREF icolor;
	D3DCOLOR scolor;
	BYTE *colorByte;
	BYTE r, g, b;

	int R = m_pGame->window()->rows();
	int y_start = y1;
	int	y_stop  = y2;
	if( y1 < 0 ) y_start = 0;
	if( y2 > R ) y_stop  = R;

	for( int y = y_start; y <= y_stop; y++ )
	{
		float t = float( y - y1 ) / float( y2 - y1 );
		int v = int( t * 255 );

		icolor = GetPixel( dc, u, v );
		colorByte = (BYTE *) &icolor;
		r = colorByte[0];
		g = colorByte[1];
		b = colorByte[2];
		scolor = D3DCOLOR_XRGB( r, g, b );

		dst_bufpos = y * lDstRect.Pitch + x * bpp;

		memcpy( &DstBuffer[dst_bufpos], &scolor, bpp );
	}

	DeleteDC( dc );
	pDstSurf->UnlockRect();
}


//-----------------------------------------------------------------------------
// LoadBitmap()
//-----------------------------------------------------------------------------
IDirect3DSurface8* Graphics::LoadBitmap( string filename )
{
	HDC dc;
	HBITMAP new_bmp;
	BITMAP bmp;

	dc = CreateCompatibleDC( NULL );
	new_bmp = (HBITMAP) LoadImage( NULL, filename.c_str(),
								   IMAGE_BITMAP, 0, 0,
								   LR_LOADFROMFILE );

	GetObject( new_bmp, sizeof(bmp), &bmp );
	SelectObject( dc, new_bmp );

	IDirect3DSurface8 *surface;
	m_pD3Ddevice->CreateImageSurface( bmp.bmWidth, bmp.bmHeight,
									  D3DFMT_X8R8G8B8, &surface );
	D3DLOCKED_RECT lrect;
	surface->LockRect( &lrect, NULL, 0 );

	unsigned char *buffer = (unsigned char *) lrect.pBits;
	unsigned long bpp = 4;
	unsigned long bufpos = 0;

	COLORREF icolor;
	D3DCOLOR scolor;
	BYTE *colorByte;
	BYTE r, g, b;

	for( int y = 0; y < bmp.bmHeight; y++ )
	{
		for( int x = 0; x < bmp.bmHeight; x++ )
		{
			icolor = GetPixel( dc, x, y );
			colorByte = (BYTE *) &icolor;
			r = colorByte[0];
			g = colorByte[1];
			b = colorByte[2];
			scolor = D3DCOLOR_XRGB( r, g, b );
			bufpos = ( y - bmp.bmHeight ) * lrect.Pitch +
					 ( x - bmp.bmWidth )  * bpp;

			memcpy( &buffer[bufpos], &scolor, bpp );
		}
	}

	surface->UnlockRect();

	DeleteObject( new_bmp );
	DeleteDC( dc );

	return surface;
}
