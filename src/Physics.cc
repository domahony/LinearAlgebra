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

struct Callback2 : public btCollisionWorld::ContactResultCallback
{

	Callback2(domahony::physics::Physics::ContactInfo* ci, AppObject* target, const glm::vec3& center, const float& radius) :
		info(ci), target(target), center(center), radius(radius) { }

	virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* wrap0, int partId0, int idx0,
			const btCollisionObjectWrapper *wrap1, int partId1, int idx1)
	{

		std::cout << "HI HO!!!" << std::endl;
		AppObject * ao = static_cast<AppObject*>(wrap0->getCollisionObject()->getUserPointer());

		/*
		btVector3 s = wrap0->getWorldTransform().inverse() * cp.getPositionWorldOnA();
		btVector3 s2 = wrap1->getWorldTransform().inverse() * cp.getPositionWorldOnB();
		*/
		btVector3 s =  cp.getPositionWorldOnA();
		btVector3 s2 =  cp.getPositionWorldOnB();
		/*
		btVector3 s = wrap0->getWorldTransform() * cp.getPositionWorldOnA();
		btVector3 s2 = wrap1->getWorldTransform() * cp.getPositionWorldOnB();
		*/
		if (wrap0->getCollisionObject()->getUserPointer() != target) {

			s = cp.getPositionWorldOnA();
			s2 =  cp.getPositionWorldOnB();
			ao = static_cast<AppObject*>(wrap0->getCollisionObject()->getUserPointer());

		} else {
			ao = static_cast<AppObject*>(wrap1->getCollisionObject()->getUserPointer());
			s = cp.getPositionWorldOnB();
			s2 =  cp.getPositionWorldOnA();
		}

		float distance = glm::distance(
				glm::vec3(
						s.getX(),
						s.getY(),
						s.getZ()
						),
						center
		);

		std::cout << "Distance - Radius: " << radius - distance << std::endl;
		std::cout << "*Distance: " << cp.getDistance() << std::endl;
		std::cout << "Scale: " << ao->get_scale() << std::endl;

		if (fabs(radius - distance) <= (2.f * ao->get_scale())) {

			domahony::physics::Physics::ContactInfoItem i;
			i.ptr = 0;
			i.pt = glm::vec3(s2.getX(), s2.getY(), s2.getZ());
			info->items.push_back(i);
			ao->set_front_mode(GL_FILL);

		} else {

			ao->set_front_mode(GL_FILL);

		}

		return 0;

		float distance1 = glm::distance(
				glm::vec3(
						s.getX(),
						s.getY(),
						s.getZ()
						),
						center
				);

		float distance2 = glm::distance(
				glm::vec3(
						s2.getX(),
						s2.getY(),
						s2.getZ()
						),
						center
				);

		std::cout << "Distance: " << radius - distance1 << std::endl;
		std::cout << "Distance: " << radius - distance2 << std::endl;

		std::cout << "A: "
				<< s.getX() << ", "
				<< s.getY() << ", "
				<< s.getZ() << ") B: "
				<< s2.getX() << ", "
				<< s2.getY() << ", "
				<< s2.getZ() << ")" << std::endl;

		domahony::physics::Physics::ContactInfoItem i;
		i.ptr = ao;

		if (wrap0->getCollisionObject()->getUserPointer() != target) {

		if (fabs(radius - distance1) <= 4.5f) {
			i.pt = glm::vec3(s2.getX(), s2.getY(), s2.getZ());
			info->items.push_back(i);
		}

		} else if (wrap1->getCollisionObject()->getUserPointer() != target) {

		if (fabs(radius - distance2) <= 4.5f) {
			i.pt = glm::vec3(s.getX(), s.getY(), s.getZ());
			info->items.push_back(i);
		}

		}

		return 0;
	}

	domahony::physics::Physics::ContactInfo *info;
	domahony::applications::AppObject * target;
	glm::vec3 center;
	float radius;
};

struct Callback : public btCollisionWorld::ContactResultCallback
{

	virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* wrap0, int partId0, int idx0,
			const btCollisionObjectWrapper *wrap1, int partId1, int idx1)
	{
		std::cout << "Contact!!!" << std::endl;

		AppObject * ao = static_cast<AppObject*>(wrap0->getCollisionObject()->getUserPointer());

		glm::vec3 start;
		glm::vec3 end;

		if (!ao->is_active()) {

			btVector3 s = cp.getPositionWorldOnB();
			btVector3 e = cp.getPositionWorldOnA();
			end.x = e.getX();
			end.y = e.getY();
			end.z = e.getZ();

			start.x = s.getX();
			start.y = s.getY();
			start.z = s.getZ();

		} else {

			btVector3 e = cp.getPositionWorldOnB();
			btVector3 s = cp.getPositionWorldOnA();
			end.x = e.getX();
			end.y = e.getY();
			end.z = e.getZ();

			start.x = s.getX();
			start.y = s.getY();
			start.z = s.getZ();

			ao = static_cast<AppObject*>(wrap1->getCollisionObject()->getUserPointer());

		}

		glm::vec3 dir(start - end);

		std::cout <<
				dir.x << ","  <<
				dir.y << ","  <<
				dir.z <<
				std::endl;

		if (dir != glm::vec3(0)) {
			dir = glm::normalize(dir);
		}
		ao->nudge(dir, 0.2);

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

void Physics::
get_contact_info(Physics::ContactInfo& info, AppObject* target, const glm::vec3& center, const float& radius) const
{
	Callback2 cb(&info, target, center, radius);

	dynamicsWorld->performDiscreteCollisionDetection();
	btCollisionObjectArray a = dynamicsWorld->getCollisionObjectArray();

	for (int i=0; i < dynamicsWorld->getNumCollisionObjects(); i++) {
		dynamicsWorld->contactTest(a[i], cb);
	}

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
