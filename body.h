#ifndef __BODY_H__
#define __BODY_H__

#include "Mass.h"
#include "CoordinateSystem.h"

class Body : public Mass
{
	public:
		Body();
		Body( vector &v );
		Body( vector &v, float m );
		virtual ~Body();

		virtual vector pos();
		virtual float  inertia( vector &p );
		virtual vector cm();
		virtual vector omega();
		virtual vector alpha();
		virtual vector torque();
		virtual float  volume();

		CoordinateSystem* getCoordinateSystem();

		virtual void setOmega ( vector &v );
		virtual void setTorque( vector &v );
		virtual void addTorque( vector &v );

		virtual void rotate( vector &v, float fi );
		virtual void rotate( vector &r0, vector &v, float fi );

		void update();

	protected:
		CoordinateSystem *m_pCoordinateSystem;

		vector m_omega;			// rotationshastighet
		vector m_alpha;			// rotationsacceleration
		vector m_torque;		// vridmoment
		float  m_volume;
};

#endif
