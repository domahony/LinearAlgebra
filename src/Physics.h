/*
 * Physics.h
 *
 *  Created on: 2013-08-31
 *      Author: domahony
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <boost/shared_ptr.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace domahony {
namespace physics {

class Physics {

public:

	Physics();

	void add_body(btRigidBody* body) {
		dynamicsWorld->addRigidBody(body);
	}

	virtual ~Physics();

private:
	boost::shared_ptr<btBroadphaseInterface> broadphase;
	boost::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
	boost::shared_ptr<btCollisionDispatcher> dispatcher;
	boost::shared_ptr<btSequentialImpulseConstraintSolver> solver;
	boost::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;

};

} /* namespace physics */
} /* namespace domahony */
#endif /* PHYSICS_H_ */
