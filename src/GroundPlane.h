/*
 * GroundPlane.h
 *
 *  Created on: Feb 19, 2014
 *      Author: domahony
 */

#ifndef GROUNDPLANE_H_
#define GROUNDPLANE_H_

#include <glm/glm.hpp>
#include <vector>
#include <btBulletCollisionCommon.h>

namespace domahony {

class GroundPlane {
public:
	GroundPlane() : data(), cshape(new btStaticPlaneShape(btVector3(0,1,0),1)) {};
	virtual ~GroundPlane() {};

	float get_mass() const {
		return 0;
	}

	btCollisionShape *get_collision_shape() const {
		return cshape;
	}

	void enable() const {
	}

	void disable() const {
	}

	void set_eye_location(const glm::vec3& v) {
	}

	void set_global_light(const float& g) {
	}

	void set_mvp_matrix(const glm::mat4& m) {
	}

	void set_normal_matrix(const glm::mat3& m) {
	}

	void set_projection_matrix(const glm::mat4& m) {
	}

	void set_view_matrix(const glm::mat3& m) {
	}

	void set_light_direction(const glm::vec3& d) {
	}

	void set_light_color(const glm::vec3& c) {
	}

	void set_specular_color(const glm::vec3& c) {
	}

	void set_gloss(const float& g) {
	}

	void set_data(const std::vector<float>&) {

	}

	std::vector<float> get_data() const {
		return data;
	}

	void render() const {
	}

private:
	std::vector<float> data;
	btCollisionShape *cshape;
};

} /* namespace domahony */

#endif /* GROUNDPLANE_H_ */
