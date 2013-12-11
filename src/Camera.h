/*
 * Camera.h
 *
 *  Created on: 2013-06-17
 *      Author: domahony
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace domahony {
namespace framework {

/**
 * @class Camera
 * @brief The camera object.
 *
 * This object encapsulates the camera.
 */

class Camera {
public:
	Camera() :
		m_projection(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f)),
		m_location(glm::vec3(0,2,6)),
		m_quaternion(glm::quat_cast(glm::lookAt(m_location, glm::vec3(0,0,0), glm::vec3(0,1,0))))
	{
	}

	/**
	 * @brief Updates the projection matrix
	 * 
	 * Updates the projection matrix based on changing the width and hieight of the view
	 */
	void update_perspective(const int& w, const int& h) {
		m_projection = glm::perspective(45.f, w/static_cast<float>(h), 0.1f, 100.0f);
	}

	/**
	 * @brief Returns the view matrix.
	 *
	 * This matrix converts between world space and camera space.
	 */
	const glm::mat4 view() const {
		return glm::mat4_cast(m_quaternion) * glm::translate(glm::mat4(1), m_location * -1.f);
	}

	/**
	 * @brief Returns the projection matrix.
	 *
	 * This matrix converts between camera space to screen space.
	 */
	const glm::mat4 projection() const {
		return m_projection;
	}

	/**
	 * @brief Returns the location of the camera.
	 *
	 * I think this location is in world space.
	 */
	const glm::vec3 location() const {
		return glm::vec3(glm::inverse(view()) * glm::vec4(m_location, 1));
	}


	/**
	 * Move the laterally left
	 */
	void left() {
		move2(glm::vec3(-.1, 0, 0), -1);
	}

	/**
	 * Move the laterally right
	 */
	void right() {
		move2(glm::vec3(.1, 0, 0), 1);
	}

	/**
	 * Move the camera up
	 */
	void up() {
		move2(glm::vec3(0,.1, 0), 1);
	}

	/**
	 * Move the camera down
	 */
	void down() {
		move2(glm::vec3(0,-.1, 0), -1);
	}

	/**
	 * Move the camera forward
	 */
	void in() {
		move2(glm::vec3(0, 0, -.1), -1);
	}

	/**
	 * Move the camera backward
	 */
	void out() {
		move2(glm::vec3(0, 0, .1), 1);
	}


	/**
	 * Turn left
	 */
	void yaw_left() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 1, 0), -2.f);
	}

	/**
	 * Turn right
	 */
	void yaw_right() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 1, 0), 2.f);
	}

	/**
	 * Tilt the camera up
	 */
	void pitch_up() {
		m_quaternion = m_quaternion * spin(glm::vec3(1, 0, 0), -2.f);
	}

	/**
	 * Tilt the camera down
	 */
	void pitch_down() {
		m_quaternion = m_quaternion * spin(glm::vec3(1, 0, 0), 2.f);
	}

	/**
	 * Roll the camera to the left
	 */
	void roll_left() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 0, 1), 2.f);
	}

	/**
	 * Roll the camera to the right
	 */
	void roll_right() {
		m_quaternion = m_quaternion * spin(glm::vec3(0, 0, 1), -2.f);
	}

private:

	void move2(const glm::vec3& v, const float& m) {

		glm::vec3 v2 = glm::normalize(glm::mat3(glm::inverse(view())) * v);
		glm::mat4 t = glm::translate(glm::mat4(1.f), v2);
		glm::vec4 n = t * glm::vec4(m_location.x, m_location.y, m_location.z, 1.f);
		m_location = glm::vec3(n);
	}

	glm::quat spin(const glm::vec3& v, const float& a) const {
		glm::vec3 axis(glm::mat3(glm::inverse(view())) * v);
		glm::quat local = glm::angleAxis(a, axis);
		return local;
	}

	glm::mat4 m_projection;
	glm::vec3 m_location;
	glm::quat m_quaternion;

};

} /* namespace framework */
} /* namespace domahony */
#endif /* CAMERA_H_ */
