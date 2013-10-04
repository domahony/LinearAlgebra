/*
 * BodyCreator.h
 *
 *  Created on: 2013-09-06
 *      Author: domahony
 */

#ifndef BODYCREATOR_H_
#define BODYCREATOR_H_

#include <glm/glm.hpp>
#include <btBulletDynamicsCommon.h>
#include <boost/shared_ptr.hpp>

namespace domahony {

namespace applications {
	class AppObject;
}

namespace physics {

class BodyCreator {
public:
	BodyCreator(boost::shared_ptr<btDiscreteDynamicsWorld> world) : world(world) {

	}

	void add_point(const glm::vec3&);

	void finish(domahony::applications::AppObject *o) {

		btRigidBody* body = new btRigidBody(0, NULL, NULL, btVector3(0,0,0));

		body->setUserPointer(static_cast<void *>(o));
		world->addRigidBody(body);

	}

	virtual ~BodyCreator();
private:
	boost::shared_ptr<btDiscreteDynamicsWorld> world;

};

} /* namespace physics */
} /* namespace domahony */
#endif /* BODYCREATOR_H_ */
