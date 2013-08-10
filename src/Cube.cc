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
using glm::ivec3;
using glm::ivec4;
using glm::normalize;
using glm::triangleNormal;

static vec3 VERTS[] = {
		// front
		vec3(.5,.5,.5), 	/*0 ftr */
		vec3(-.5,.5,.5),	/*1 ftl */
		vec3(-.5,-.5,.5),	/*2 fbl */
		vec3(.5,-.5,.5),	/*3 fbr */

		//back
		vec3(.5,.5,-.5),	/*4 btr */
		vec3(.5,-.5,-.5),	/*5 bbr */
		vec3(-.5,-.5,-.5),	/*6 bbl */
		vec3(-.5,.5,-.5),	/*7 btl */
};

static ivec4 FACE[] = {
		/* front * */
		ivec4(0,1,2,3),
		/* bottom */
		ivec4(3,2,6,5),
		/* left */
		ivec4(1,7,6,2),
		/* right * */
		ivec4(0,3,5,4),
		/* back * */
		ivec4(4,5,6,7),
		/* top */
		ivec4(0,4,7,1),
};

static ivec3 FIDX[] = {
		ivec3(0,1,2),
		ivec3(2,3,0),
};

static vec3 COLOR[] = {
		vec3(1,1,0),
		vec3(1,0,1),
		vec3(0,1,1),
		vec3(0,0,1),
		vec3(0,1,0),
		vec3(1,0,0),
};

static std::vector<GLfloat> data() {

	std::vector<GLfloat> data;

	for (int i = 0; i < sizeof(FACE)/sizeof(FACE[0]); i++) {

		vec3 norm = triangleNormal(VERTS[FACE[i][0]], VERTS[FACE[i][1]], VERTS[FACE[i][2]]);

		for (int j = 0; j < 2; j++) {

			for (int k = 0; k < 3; k++) {

				data.push_back(VERTS[FACE[i][FIDX[j][k]]].x);
				data.push_back(VERTS[FACE[i][FIDX[j][k]]].y);
				data.push_back(VERTS[FACE[i][FIDX[j][k]]].z);

				data.push_back(norm.x);
				data.push_back(norm.y);
				data.push_back(norm.z);

				data.push_back(COLOR[i].r);
				data.push_back(COLOR[i].g);
				data.push_back(COLOR[i].b);
			}

		}
	}

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

void Cube::doDraw(const domahony::framework::Camera& c) {

	/*
	 * need to know location of
	 * location = location * local_location
	 *	draw(location)
	 */


	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_BACK, GL_LINE);

	push_location(glm::translate(get_location(), glm::vec3(0.5,0,0)));
	program.set_mvp_matrix(c.projection() * c.view() * get_location());
	glDrawArrays(GL_TRIANGLES, 0, 54);
	pop_location();

	push_location(glm::translate(get_location(), glm::vec3(-0.5,0,0)));
	program.set_mvp_matrix(c.projection() * c.view() * get_location());
	glDrawArrays(GL_TRIANGLES, 0, 54);
	pop_location();

	push_location(glm::translate(get_location(), glm::vec3(-0.5,1,0)));
	program.set_mvp_matrix(c.projection() * c.view() * get_location());
	glDrawArrays(GL_TRIANGLES, 0, 54);
	pop_location();


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
