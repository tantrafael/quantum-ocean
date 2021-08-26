#ifndef __SURFACEPOINT_H__
#define __SURFACEPOINT_H__

#include "Mass.h"
#include "vector.h"

#define NULL 0

class Binding;


class SurfacePoint : public Mass
{
	public:
		SurfacePoint();
		SurfacePoint( vector &v );
		virtual ~SurfacePoint();

	protected:

};

#endif