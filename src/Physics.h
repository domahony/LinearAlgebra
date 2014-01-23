/*
 * Physics.h
 *
 *  Created on: 2013-08-31
 *      Author: domahony
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <ctime>
#include <vector>
#include "Body.h"
#include "AppObject.h"

namespace domahony {
namespace physics {

class Physics {

public:

	struct ContactInfoItem {
		glm::vec3 pt;
		void *ptr;
	};

	struct ContactInfo {
		std::vector<ContactInfoItem> items;
	};

	Physics();

	void * get_click_object(const glm::vec4& start, const glm::vec3& direction) const;

	int tick() {
		clock_t cur_tick = clock();

		btScalar delta = static_cast<btScalar>((cur_tick - last_tick)) / CLOCKS_PER_SEC;
		//std::cout << "Physics Step: " << delta << std::endl;

		last_tick = cur_tick;

		btCollisionObjectArray a =  dynamicsWorld->getCollisionObjectArray();

		return dynamicsWorld->stepSimulation(delta, 7);
	}

	bool any_touches();

	void add_body(Body& body) {


		dynamicsWorld->addRigidBody(body.getRigidBody());
	}

	int internal_tick(btScalar step) {
			//std::cout << "Internal Step: " << step << std::endl;
			return 1;
	}

	void get_contact_info(ContactInfo& ci, domahony::applications::AppObject*, const glm::vec3&, const float&) const;

	virtual ~Physics();

private:
	boost::shared_ptr<btBroadphaseInterface> broadphase;
	boost::shared_ptr<btDefaultCollisionConfiguration> collisionConfiguration;
	boost::shared_ptr<btCollisionDispatcher> dispatcher;
	boost::shared_ptr<btSequentialImpulseConstraintSolver> solver;
	boost::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;
	clock_t last_tick;

};

} /* namespace physics */
} /* namespace domahony */
#endif /* PHYSICS_H_ */
