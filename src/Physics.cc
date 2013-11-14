/*
 * Physics.cc
 *
 *  Created on: 2013-08-31
 *      Author: domahony
 */

#include "Physics.h"
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

namespace domahony {
namespace physics {

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

void
Physics::any_touches()
{

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
