#include "Input.h"
#include "Game.h"

Input::Input()
{
	m_pDI = NULL;
	m_pKeyboard = NULL;
}

Input::~Input()
{
	m_TermDI();
}


//-----------------------------------------------------------------------------
// Name: init()
// Desc:
//-----------------------------------------------------------------------------
void Input::init( Game *pGame )
{
	m_pGame = pGame;
	m_InitDI();
}


//-----------------------------------------------------------------------------
// Name: read()
// Desc:
//-----------------------------------------------------------------------------
void Input::read()
{
	#define KEYDOWN( name, key ) ( name[key] & 0x80 )

	char     buffer[256];
	HRESULT  hr;

	m_pKeyboard->Acquire();
	hr = m_pKeyboard->GetDeviceState( sizeof(buffer), (LPVOID)&buffer );

	if( KEYDOWN( buffer, DIK_LEFT ) )
	{
		vector axis = m_pGame->world()->camera()->getCoordinateSystem()->k();
		m_pGame->world()->camera()->addTorque( axis * ( -0.015f ) );
	}

	if ( KEYDOWN( buffer, DIK_RIGHT ) )
	{
		vector axis = m_pGame->world()->camera()->getCoordinateSystem()->k();
		m_pGame->world()->camera()->addTorque( axis * 0.015f );
	}

	if ( KEYDOWN( buffer, DIK_UP ) )
	{
		vector dir = m_pGame->world()->camera()->getCoordinateSystem()->j();
		m_pGame->world()->camera()->addForce( dir * 0.015f );
	}

	if ( KEYDOWN( buffer, DIK_DOWN ) )
	{
		vector dir = m_pGame->world()->camera()->getCoordinateSystem()->j();
		m_pGame->world()->camera()->addForce( dir * ( -0.015f ) );
	}
}


//-----------------------------------------------------------------------------
// Name: m_InitDI()
// Desc:
//-----------------------------------------------------------------------------
HRESULT Input::m_InitDI()
{
	HRESULT hr;

	// Create DirectInput object
	hr = DirectInput8Create( m_pGame->window()->hInst(),
							 DIRECTINPUT_VERSION,
							 IID_IDirectInput8,
							 (void**) &m_pDI,
							 NULL );
	if( FAILED(hr) )
		return hr;

	// Create DirectInput device
	hr = m_pDI->CreateDevice( GUID_SysKeyboard,
							  &m_pKeyboard,
							  NULL );
	if( FAILED(hr) )
		return hr;

	// Set data format
	hr = m_pKeyboard->SetDataFormat( &c_dfDIKeyboard );

	if( FAILED(hr) )
		return hr;

	// Set cooperative level 
	hr = m_pKeyboard->SetCooperativeLevel( m_pGame->window()->hWnd(),
										   DISCL_FOREGROUND |
										   DISCL_NONEXCLUSIVE );
	if( FAILED(hr) )
		return hr;

	// Acquire access
	if( m_pKeyboard ) m_pKeyboard->Acquire();
	m_pKeyboard->Acquire(); 

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: m_TermDI()
// Desc:
//-----------------------------------------------------------------------------
void WINAPI Input::m_TermDI()
{
	if( m_pDI )
	{
		if( m_pKeyboard )
		{
			m_pKeyboard->Release();
			m_pKeyboard = NULL;
		}
		m_pDI->Release();
		m_pDI = NULL;
	}
}
