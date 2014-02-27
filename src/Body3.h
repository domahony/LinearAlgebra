/*
 * Body3.h
 *
 *  Created on: 2014-01-29
 *      Author: domahony
 */

#ifndef BODY3_H_
#define BODY3_H_

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <boost/shared_ptr.hpp>

namespace domahony {

static btVector3
get_inertia(const float& mass, btCollisionShape* shape)
{
	btVector3 inertia(0,0,0);

	if (shape) {
		shape->calculateLocalInertia(mass, inertia);
	}

	return inertia;
}

class Body3 : btMotionState {
public:
	Body3(const glm::mat4& l, const float mass, btCollisionShape* cshape):
		location(l), material(glm::vec3(.6), 1.f),
		rigid_body(new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(mass, this, cshape, get_inertia(mass, cshape))))
	{
	};

	virtual ~Body3() {};
	virtual void render(const domahony::framework::Camera& c, const domahony::framework::Light& l, const int, const int) const =0;

	void set_location(const glm::mat4& loc) {
		location = loc;

		btTransform t;
		t.setFromOpenGLMatrix(glm::value_ptr(location));
		rigid_body->setWorldTransform(t);
	}

	virtual void reset() { }
	virtual void activate() { }

	glm::mat4 get_location() const
	{
		return location;
	}

	domahony::framework::Material get_material() const
	{
		return material;
	}

	void move(const glm::vec3& v) {
		glm::mat4 t = glm::translate(glm::mat4(1), v);
		location = t * location;
	}

	void getWorldTransform(btTransform& t) const {
		std::cout << "CALLED GET" << std::endl;
		t.setFromOpenGLMatrix(glm::value_ptr(location));
	}

	void setWorldTransform(const btTransform& t) {
		std::cout << "CALLED SET" << std::endl;
		float m[16];
		float *mm = glm::value_ptr(location);

		for (int i = 0; i < 16; i++) {
			std::cout << mm[i] << " ";
		}
		std::cout << std::endl;
		t.getOpenGLMatrix(m);

		for (int i = 0; i < 16; i++) {
			std::cout << m[i] << " ";
		}
		std::cout << std::endl;
		location = glm::make_mat4(m);
	}

	btRigidBody* get_rigid_body() const {
		return rigid_body.get();
	}

private:
	glm::mat4 location;
	domahony::framework::Material material;
protected:
	boost::shared_ptr<btRigidBody> rigid_body;
};

typedef boost::shared_ptr<Body3> Body3Ptr;

} /* namespace domahony */
#endif /* BODY3_H_ */
