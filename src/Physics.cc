/*
 * Physics.cc
 *
 *  Created on: 2013-08-31
 *      Author: domahony
 */

#include "Physics.h"
#include <btBulletDynamicsCommon.h>

namespace domahony {
namespace physics {

Physics::Physics() :
			broadphase(new btDbvtBroadphase()),
			collisionConfiguration(new btDefaultCollisionConfiguration()),
			dispatcher(new btCollisionDispatcher(collisionConfiguration.get())),
			solver(new btSequentialImpulseConstraintSolver()),
			dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(), solver.get(), collisionConfiguration.get()))
{

}

Physics::~Physics() {
	// TODO Auto-generated destructor stub
}

} /* namespace physics */
} /* namespace domahony */
