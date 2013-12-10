/*
 * Body.h
 *
 *  Created on: 2013-09-07
 *      Author: domahony
 */

#ifndef BODY_H_
#define BODY_H_

#include <boost/shared_ptr.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace domahony {
namespace physics {

static btTransform get_transform(const glm::mat4& m) {

	btTransform ret;
	ret.setFromOpenGLMatrix(glm::value_ptr(m));

	return ret;
}

class Body {
public:
	Body(void *ptr, glm::mat4 state, const float& bounding_sphere_radius, const float& mass) :
		motion_state(get_transform(state)),
		collision(new btSphereShape(bounding_sphere_radius)),
		body(0, &motion_state, collision)
	{

		body.setUserPointer(ptr);
		//body.setGravity(btVector3(0,0,0));

	}

	glm::vec3 get_origin() const {

		btTransform t;
		body.getMotionState()->getWorldTransform(t);

		btVector3 origin = t.getOrigin();

		glm::vec3 ret(origin.x(), origin.y(), origin.z());

		return ret;
	}

	glm::mat4 get_location() const {

		btTransform t;
		body.getMotionState()->getWorldTransform(t);

		glm::mat4 ret;

		t.getOpenGLMatrix(glm::value_ptr(ret));

		return ret;
	}

	glm::quat get_rotation() const {

		btTransform t;
		body.getMotionState()->getWorldTransform(t);

		btQuaternion q = t.getRotation();

		glm::quat ret(q.getW(), q.getX(), q.getY(), q.getZ());
		//glm::quat ret = glm::normalize(glm::angleAxis(q.getAngle(), q.getAxis().getX(), q.getAxis().getY(), q.getAxis().getZ()));

		return ret;

		/*
		return glm::vec4(
				q.getX(),
				q.getY(),
				q.getZ(),
				q.getW()
				);
			*/
	}

	void set_locationx(const glm::vec3& loc) {

		btTransform t;
		body.getMotionState()->getWorldTransform(t);
		t.setOrigin(btVector3(loc.x,loc.y, loc.z));
		body.getMotionState()->setWorldTransform(t);

	}

	void set_location(const glm::mat4& loc, const glm::quat& rot=glm::quat(1,0,0,0)) {

		btTransform t = get_transform(loc);
		//btQuaternion q(rot.x, rot.y, rot.z, rot.w);
		//btQuaternion q(rot.x, rot.y, rot.z, rot.w);

		glm::quat rotn(glm::normalize(rot));

		//btScalar angle = glm::angle(rotn);
		//glm::vec3 axis = glm::axis(rotn);
		//btQuaternion q(btVector3(axis.x, axis.y, axis.z), angle * (M_PI / 180.f));

		btQuaternion q(rotn.x, rotn.y, rotn.z, rotn.w);

		t.setRotation(q);

		body.getMotionState()->setWorldTransform(t);
		body.setWorldTransform(t);
	}

	btRigidBody * getRigidBody() {
		return &body;
	}

	virtual ~Body() {

	}

private:
	btDefaultMotionState motion_state;
	btCollisionShape *collision;
	btRigidBody body;

};

} /* namespace physics */
} /* namespace domahony */
#endif /* BODY_H_ */
