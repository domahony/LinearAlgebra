/*
 * Camera.cc
 *
 *  Created on: 2013-06-17
 *      Author: domahony
 */

#include "Camera.h"
#include <iostream>

namespace domahony {
namespace framework {

Camera::Camera() :
		m_projection(glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 10000.0f)),
		m_location(glm::vec3(0,2,14)),
		m_quaternion(glm::normalize(glm::quat_cast(glm::lookAt(m_location, glm::vec3(0,0,0), glm::vec3(0,1,0))))),
		m_camera_quat(1, 0, 0, 0),
		width(640), height(480)
	{
		glm::vec3 q_axis = glm::axis(m_quaternion);
		float q_angle = glm::angle(m_quaternion);
		std::cout << "Quaternion Axis: " << q_axis.x << "," << q_axis.y << "," << q_axis.z << std::endl;
		std::cout << "Quaternion Angle: " << q_angle << std::endl;

		glm::vec3 loc1 = m_quaternion * m_location * glm::inverse(m_quaternion);
		std::cout << "Loc 1: " << loc1.x << "," << loc1.y << "," << loc1.z << std::endl;
		glm::vec3 loc2 = glm::inverse(m_quaternion) * m_location * (m_quaternion);
		std::cout << "Loc 2: " << loc2.x << "," << loc2.y << "," << loc2.z << std::endl;

		glm::vec4 loc3 = m_quaternion * glm::vec4(0, 0, 0, 1) * glm::inverse(m_quaternion);
		std::cout << "Loc 3: " << loc3.x << "," << loc3.y << "," << loc3.z << std::endl;

		glm::quat trans = glm::quat_cast(glm::translate(glm::mat4(1), -m_location));
		glm::quat q2 = trans * m_quaternion;

		glm::vec4 loc4 = q2 * glm::vec4(m_location.x, m_location.y, m_location.z, 1) * glm::inverse(q2);
		std::cout << "Loc 4: " << loc4.x << "," << loc4.y << "," << loc4.z << std::endl;
		glm::vec4 loc5 = glm::inverse(q2) * glm::vec4(m_location.x, m_location.y, m_location.z, 1) * (q2);
		std::cout << "Loc 5: " << loc5.x << "," << loc5.y << "," << loc5.z << std::endl;

		glm::vec4 loc6 = q2 * glm::vec4(0, 0, 0, 1) * glm::inverse(q2);
		std::cout << "Loc 6: " << loc6.x << "," << loc6.y << "," << loc6.z << std::endl;

		glm::vec3 loc7 = location();
		std::cout << "Loc 7: " << loc7.x << "," << loc7.y << "," << loc7.z << std::endl;

		glm::vec4 loc8 = glm::mat4_cast(m_quaternion) * glm::vec4(m_location, 1);
		std::cout << "Loc 8: " << loc8.x << "," << loc8.y << "," << loc8.z << std::endl;
	}

	glm::quat Camera::
	spin2(const glm::vec3& v, const float& a) const
	{
		glm::quat local = glm::angleAxis(a, v);
		return local;
	}

void Camera::
move(const glm::vec3& v, const float& deg) {
		//glm::quat local = glm::angleAxis(glm::length(v), glm::normalize(v));
		//m_quaternion = local * m_quaternion;

		//m_quaternion = glm::rotate(m_quaternion, glm::length(v), glm::normalize(v));

		//m_quaternion = spin(glm::mat3(view()) * glm::normalize(v), glm::length(v)) * m_quaternion;

		glm::vec3 z(0.f,0.f,1.f);
		glm::vec3 v2 = glm::cross(v, z);
		v2.x *= -1.f;

		m_quaternion = m_quaternion * spin(glm::normalize(v2), deg);
		return;

		/*
		glm::vec4 ndc(v.x, v.y, v.z, 1.0);
		std::cout << "NDC: " << ndc.x << ","  << ndc.y << "," << ndc.z << std::endl;
		glm::vec4 cam_ndc = glm::inverse(projection()) * glm::vec4(ndc.x, ndc.y, ndc.z, 1.f); cam_ndc /= cam_ndc.w;

		//glm::vec4 z(0,0,1.f,1.f);
		glm::vec4 cam_z = glm::inverse(projection()) * z; cam_z /= cam_z.w;
		std::cout << "CAM_Z: " << cam_z.x << ","  << cam_z.y << "," << cam_z.z << std::endl;

		glm::vec3 cam_axis = glm::cross(glm::vec3(cam_z), glm::vec3(cam_ndc));
		std::cout << "CAM_AXIS: " << cam_axis.x << ","  << cam_axis.y << "," << cam_axis.z << std::endl;

		//glm::vec4 cam = glm::inverse(projection()) * glm::vec4(axis.x, axis.y, axis.z, 1.f); cam /= cam.w;

		//glm::mat4 tran = glm::translate(glm::mat4(1.f), m_location);
		//cam = cam * tran;

		glm::vec4 world_axis = glm::inverse(view()) * glm::vec4(cam_axis.x, cam_axis.y, cam_axis.z, 1); world_axis /= world_axis.w;
		std::cout << "WORLD_AXIS: " << world_axis.x << ","  << world_axis.y << "," << world_axis.z << "," << world_axis.w << std::endl;

		glm::mat4 rota = glm::rotate(glm::mat4(1.f), 1.f, glm::normalize(glm::vec3(world_axis)));

		m_location = glm::vec3(rota * glm::vec4(m_location.x, m_location.y, m_location.z, 1.f));
		m_quaternion = glm::quat_cast(rota) * m_quaternion;

		//m_location = m_location + v;
		 *
		 */
	}

} /* namespace framework */
} /* namespace domahony */
