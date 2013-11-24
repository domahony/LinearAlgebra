/*
 * Physics.cc
 *
 *  Created on: 2013-08-31
 *      Author: domahony
 */

#include "Physics.h"
#include "AppObject.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <glm/glm.hpp>

namespace domahony {
namespace physics {

using domahony::applications::AppObject;

struct Callback : public btCollisionWorld::ContactResultCallback
{

	virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* wrap0, int partId0, int idx0,
			const btCollisionObjectWrapper *wrap1, int partId1, int idx1)
	{
		std::cout << "Contact!!!" << std::endl;

		AppObject * ao = static_cast<AppObject*>(wrap0->getCollisionObject()->getUserPointer());

		if (!ao->is_active()) {

			btVector3 v = cp.getPositionWorldOnA();
			glm::vec3 dir(v.getX(), v.getY(), v.getZ());
			ao->spin(dir);
		}

		ao = static_cast<AppObject*>(wrap1->getCollisionObject()->getUserPointer());

		btVector3 v = cp.getPositionWorldOnA();
		glm::vec3 dir(v.getX(), v.getY(), v.getZ());
		ao->spin(dir);

		return 0;
	}


};

static void callback(btDynamicsWorld* w, btScalar step) {

	Physics * p = static_cast<Physics*>(w->getWorldUserInfo());

	p->internal_tick(step);

}

void *
Physics::get_click_object(const glm::vec4& start, const glm::vec3& dir) const
{
	glm::vec3 direction = dir*1000.0f;

	btCollisionWorld::ClosestRayResultCallback RayCallback(
	    btVector3(start.x, start.y, start.z),
	    btVector3(direction.x, direction.y, direction.z)
	);

	dynamicsWorld->rayTest(
	    btVector3(start.x, start.y, start.z),
	    btVector3(direction.x, direction.y, direction.z),
	    RayCallback
	);

	if(RayCallback.hasHit()) {
	    return RayCallback.m_collisionObject->getUserPointer();
	}else{
		return 0;
	}
}

bool
Physics::any_touches()
{

	btVector3 aabbmin;
	btVector3 aabbmax;

	Callback cb;

	dynamicsWorld->performDiscreteCollisionDetection();

	btCollisionObjectArray a = dynamicsWorld->getCollisionObjectArray();

	for (int i=0; i < dynamicsWorld->getNumCollisionObjects(); i++) {
		dynamicsWorld->contactTest(a[i], cb);
	}


	return false;
}

Physics::Physics() :
			broadphase(new btDbvtBroadphase()),
			collisionConfiguration(new btDefaultCollisionConfiguration()),
			dispatcher(new btCollisionDispatcher(collisionConfiguration.get())),
			solver(new btSequentialImpulseConstraintSolver()),
			dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get())),
			last_tick(clock())
{

	dynamicsWorld->setInternalTickCallback(callback, static_cast<void *>(this), true);

}

Physics::~Physics() {
	// TODO Auto-generated destructor stub
}

} /* namespace physics */
} /* namespace domahony */
