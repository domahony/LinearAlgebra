/*
 * Physics.cc
 *
 *  Created on: 2013-08-31
 *      Author: domahony
 */

#include "Physics2.h"
#include "AppObject.h"
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

namespace domahony {
namespace physics {

using domahony::applications::AppObject;

static void callback(btDynamicsWorld* w, btScalar step) {

	Physics2 * p = static_cast<Physics2*>(w->getWorldUserInfo());

	p->internal_tick(step);

}

void *
Physics2::get_click_object(const glm::vec4& start, const glm::vec3& dir) const
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

Physics2::Physics2() :
			broadphase(new btDbvtBroadphase()),
			collisionConfiguration(new btDefaultCollisionConfiguration()),
			dispatcher(new btCollisionDispatcher(collisionConfiguration.get())),
			solver(new btSequentialImpulseConstraintSolver()),
			dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get())),
			last_tick(clock())
{
	dynamicsWorld->setInternalTickCallback(callback, static_cast<void *>(this), true);
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

Physics2::~Physics2() {
	// TODO Auto-generated destructor stub
}

} /* namespace physics */
} /* namespace domahony */
