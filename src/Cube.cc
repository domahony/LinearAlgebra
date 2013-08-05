/*
 * Cube.cc
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#include "Cube.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include "OpenGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>


namespace domahony {
namespace opengl {

using glm::mat4;
using glm::vec3;
using glm::normalize;
using glm::triangleNormal;

static std::vector<GLfloat> data() {

	std::vector<GLfloat> data;

	vec3 vertices[] = {

		//front
		vec3(.5,.5,.5),
		vec3(-.5,.5,.5),
		vec3(-.5,-.5,.5),

		vec3(-.5,-.5,.5),
		vec3(.5,-.5,.5),
		vec3(.5,.5,.5),

		//right
		vec3(.5,.5,-.5),
		vec3(.5,.5,.5),
		vec3(.5,-.5,.5),

		vec3(.5,-.5,.5),
		vec3(.5,-.5,-.5),
		vec3(.5,.5,-.5),

		//left
		vec3(-.5,.5,.5),
		vec3(-.5,.5,-.5),
		vec3(-.5,-.5,-.5),

		vec3(-.5,-.5,-.5),
		vec3(-.5,-.5,.5),
		vec3(-.5,.5,.5),

		//top
		vec3(-.5,.5,.5),
		vec3(.5,.5,.5),
		vec3(.5,.5,-.5),

		vec3(.5,.5,-.5),
		vec3(-.5,.5,-.5),
		vec3(-.5,.5,.5),

	};

	std::vector<vec3> vec(vertices, vertices + ( sizeof(vertices) / sizeof(vec3) ));

	for (std::vector<vec3>::iterator iter = vec.begin(); iter != vec.end(); iter+=3) {
		vec3 norm = triangleNormal(*iter, *(iter+1), *(iter+2));
		vec3 color(1,0,0);

		vec3 v = *iter;

		data.push_back(v.x);
		data.push_back(v.y);
		data.push_back(v.z);

		data.push_back(norm.x);
		data.push_back(norm.y);
		data.push_back(norm.z);

		data.push_back(color.r);
		data.push_back(color.g);
		data.push_back(color.b);

		v = *(iter+1);
		data.push_back(v.x);
		data.push_back(v.y);
		data.push_back(v.z);

		data.push_back(norm.x);
		data.push_back(norm.y);
		data.push_back(norm.z);

		data.push_back(color.r);
		data.push_back(color.g);
		data.push_back(color.b);

		v = *(iter+2);
		data.push_back(v.x);
		data.push_back(v.y);
		data.push_back(v.z);

		data.push_back(norm.x);
		data.push_back(norm.y);
		data.push_back(norm.z);

		data.push_back(color.r);
		data.push_back(color.g);
		data.push_back(color.b);
	}

	return data;
}

static std::vector<GLfloat> datax() {
	GLfloat vertexPositions[] = {
			/* front */
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,

			/* bottom */
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			/* back */
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,

			/* top */
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f,

			/* right */
			0.5f, 0.5f, 0.5f,
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, 0.5f,
			0.5f, -0.5f, -0.5f,

			/* left */
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, 0.5f,
	};

	std::vector<GLfloat> data(vertexPositions,
			vertexPositions + (sizeof(vertexPositions) / sizeof(GLfloat)));

	return data;
}

Cube::Cube(const domahony::opengl::Program& p, const glm::mat4& l, const domahony::framework::Material& m) :
		domahony::applications::Drawable(p, data(), l, m)
{

}

void Cube::enableVertexAttributes() const {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
}

void Cube::doDraw(const domahony::framework::Camera& c) const {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 54);
}

void Cube::disableVertexAttributes() const {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
