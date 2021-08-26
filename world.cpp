#include "World.h"
#include "Game.h"

World::World()
{
	m_SkyColor  = Color(0,16,32);
	m_pGame	    = NULL;
	m_pCamera   = NULL;
	m_pMap		= NULL;
	m_pLights	= NULL;
}

World::~World()
{
//	delete m_pCamera;

//	for( int i=0; i<480; i++)
//	{
//		if( m_array[i] ) delete m_array[i];
//		m_array[i] = NULL;
//	}

//	m_array = NULL;
}

void World::init( Game *pGame )
{
	m_pGame = pGame;
	m_pCamera = new Camera( vector( 0.5f, 0.5f, 0), 1.0f );
	m_pCamera->rotate( vector(0,0,1), -1.25f );

	m_dx = 0.1f;
	m_dy = m_dx;
	m_dz = m_dx;

	m_h0 = 5.0f;

	m_nrLights = 1;
	m_pLights = new Light[ m_nrLights ];

	for( int i=0; i<m_nrLights; i++ )
	{
		float k = i / float( m_nrLights );
		float t = 2*pi * k;
		vector pos = vector( 0.0f, -1.0f, 1.25f ) * 250.0f;

		m_pLights[i] = Light( pos, Color(255,255,255) );
	}

	m_pLightDir = vector(1,0,0);

	string filename = "texture1.bmp";
	m_hBmp = (HBITMAP) LoadImage( NULL, filename.c_str(),
								IMAGE_BITMAP, 0, 0,
								LR_LOADFROMFILE );

	m_array = new Color*[480];

	for( int i=0; i<480; i++)
	{
		m_array[i] = new Color(0,0,0);
	}

	m_pGame->graphics()->ClearBuffer( &m_SkyColor );
	m_pGame->graphics()->Present();
}

//-----------------------------------------------------------------------------
// Access
//-----------------------------------------------------------------------------
Camera*  World::camera()   { return m_pCamera; }
Color    World::SkyColor() { return m_SkyColor; }


//-----------------------------------------------------------------------------
// update()
//-----------------------------------------------------------------------------
void World::update()
{
	m_UpdateCamera();
}


//-----------------------------------------------------------------------------
// draw()
//-----------------------------------------------------------------------------
void World::draw()
{
	m_pGame->graphics()->ClearBuffer( &m_SkyColor );
	m_pGame->graphics()->BeginScene();

	RayCast( m_pMap, m_pLights );

	m_pGame->graphics()->EndScene();
	m_pGame->graphics()->Present();
}


//-----------------------------------------------------------------------------
// RayCast()
//-----------------------------------------------------------------------------
void World::RayCast( Map *pMap, Light *pLights )
{
	vector p0 = m_pCamera->pos();
	vector x1 = m_pCamera->getCoordinateSystem()->i();
	vector y1 = m_pCamera->getCoordinateSystem()->j();
	float  R  = m_pCamera->R();
	vector p1 = y1 * R;

	int cols = m_pGame->window()->cols();

	for( int i=0; i<cols; i++ )
	{
		int    j = i - cols/2;
		float  t = j / float( cols );
		vector v = p1 + x1 * t;
		Cast( i, p0, v, pMap, pLights, 1.0f );
	}
}



//-----------------------------------------------------------------------------
// Cast()
//-----------------------------------------------------------------------------
void World::Cast( int colNr,
				  vector &p0,
				  vector &v,
				  Map *pMap,
				  Light *pLights,
				  float intensity0 )
{
	float  d1 = norm( v );
	vector v1 = v / d1;
	vector p  = p0;

	int y_bottom = 479;
	int y_top = y_bottom;

	int i_start = 2;

	for( int i = 0; i < i_start; i++ )
	{
		Step( p, v1 );
	}

	for( int i = i_start; i < 24; i++ )
	{
		Step( p, v1 );

		float h  = Content( p + v1 * 0.0001f, pMap );
		float d  = norm( p - p0 );
		float h1 = m_dz * ( h - m_h0 ) * d1 / d;

		y_top = int( 240 * ( 1.0f - h1 ) );
		if( y_top < 0 )        y_top = 0;
		if( y_top > y_bottom ) y_top = y_bottom;

		Color color = Color(0,156,128);
		float t = 1.0f / ( 2.0f * d*d + 1.0f );
	//	float t = 1.0f / ( 0.1f * i + 1.0f );

		for( int y = y_bottom; y >= y_top; y-- )
	//	for( int y = y_top; y > y_top - 1; y-- )
		{
			*m_array[ y ] = color * t;
		}

	/*
		float t;
		float dx = p.x() - floorf( p.x() );
		float dy = p.y() - floorf( p.y() );
		if( fabs( dx ) > 0 ) t = dx / m_dx;
		else				 t = dy / m_dy;
		int u = int( t * 255 );

		m_pGame->graphics()->ColumnTexture( col, y1, y2, m_hBmp, u );
	*/

		y_bottom = y_top;
	}

	m_pGame->graphics()->DrawColumn( colNr, y_top, 480, m_array );
}


//-----------------------------------------------------------------------------
// NextIntersection()
//-----------------------------------------------------------------------------
void World::Step( vector &p, vector &v1 )
{

	float t;
	float tx = 1000.0f;
	float ty = 1000.0f;
	float nx, ny;
	float h  = 0.0001f;

//	if( fabs( v1.x() ) > 0 )
//	{
		if( v1.x() > 0 ) nx = ceilf ( 10.0f * p.x() + h );
		else			 nx = floorf( 10.0f * p.x() - h );
		tx = ( nx * m_dx - p.x() ) / v1.x();
//	}

//	if( fabs( v1.y() ) > 0 )
//	{
		if( v1.y() > 0 ) ny = ceilf ( 10.0f * p.y() + h );
		else			 ny = floorf( 10.0f * p.y() - h );
		ty = ( ny * m_dy - p.y() ) / v1.y();
//	}

	tx < ty ? t = tx : t = ty;

	p = p + v1 * t;
}


//-----------------------------------------------------------------------------
// Content()
//-----------------------------------------------------------------------------
float World::Content( vector &p, Map *pMap )
{
	int nx = (int) floorf( p.x() / m_dx );
	int ny = (int) floorf( p.y() / m_dy );

	float r = sqrtf( float( nx*nx + ny*ny ) );

	float t = 0.001f * GetTickCount();

	return 4.0f * sinf( 0.5f * r - t );

//	return 0;
}


//-----------------------------------------------------------------------------
// m_UpdateCamera()
//-----------------------------------------------------------------------------
void World::m_UpdateCamera()
{
	vector F = m_pCamera->velo() * ( -0.2f );
	m_pCamera->addForce( F );

	vector T = m_pCamera->omega() * ( -0.2f );
	m_pCamera->addTorque( T );

	m_pCamera->update();
}
