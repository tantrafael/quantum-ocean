#ifndef __WORLD_H__
#define __WORLD_H__

#include "constants.h"
#include "Camera.h"
#include "Light.h"

class Game;


struct Block
{
	int nx;
	int ny;
	int value;
};


struct Map
{
	int rows;
	int cols;
	int *pArray;
	Block *pBlock;
};


struct Intersection
{
	Color color;
	vector pos;
};


class World
{
	public:
		World();
		virtual ~World();

		void init( Game *pGame );
		Camera* camera();
		Color SkyColor();
		void update();
		void draw();

	protected:
		Color   m_SkyColor;
		Game   *m_pGame;
		Camera *m_pCamera;

		Map *m_pMap;

		HBITMAP m_hBmp;

		float m_dx, m_dy, m_dz;

		int m_nrLights;
		Light *m_pLights;

		Color **m_array;

		float m_h0;

		vector m_pLightDir;

		void m_UpdateCamera();

		void RayCast( Map *pMap, Light *pLights );

		void Cast( int colNr,
				   vector &p0,
				   vector &v,
				   Map *pMap,
				   Light *pLights,
				   float intensity0 );

		void Step( vector &p, vector &v1 );

		float Content( vector &p, Map *pMap );
};

#endif