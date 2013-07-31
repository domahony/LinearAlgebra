/*
 * Sphere.cc
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#define _USE_MATH_DEFINES

#include "Sphere.h"
#include "NormalCalculator.h"
#include <vector>
#include <cmath>
#include <iostream>

#define NSEGMENTS 30

namespace domahony {
namespace opengl {

struct triangle {
	glm::vec3 vert[3];
	glm::vec3 color;
	glm::vec3 normal;
};

static void surface_normal(triangle& t) {
		glm::vec3 u = t.vert[1] - t.vert[0];
		glm::vec3 v = t.vert[2] - t.vert[0];

		t.normal = glm::vec3(
				u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x
		);
}

static void
disk(const int& nsegments, const float& y, const float& r, std::vector<triangle>& data,
		std::vector<GLfloat>& data2, int& nverts)
{
	double x;
	double z;

	double A = 0;
	double increment = 2.0f * M_PI / static_cast<float>(nsegments);

	int t_idx = 0;
	triangle t;
	data.push_back(t);
	for (int xinc = 0; xinc <= nsegments; xinc++) {

		std::vector<triangle>::iterator tri = data.end() - 1;

		z = r * sin(A);
		x = r * cos(A);
		A += increment;
		std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;

		/* location */
		tri->vert[t_idx].x = x;
		tri->vert[t_idx].y = y;
		tri->vert[t_idx].z = z;

		data2.push_back(x);
		data2.push_back(y);
		data2.push_back(z);

		data2.push_back(1);
		data2.push_back(0);
		data2.push_back(0);

		data2.push_back(1);
		data2.push_back(0);
		data2.push_back(0);

		nverts++;

		t_idx = (t_idx + 1)	% 3;

		if (t_idx == 0) {
			tri->color = glm::vec3(1, 0, 0);
			surface_normal(*tri);
			triangle t;
			data.push_back(t);
		}
	}

}

static std::vector<GLfloat>
data(int &nverts)
{
	std::vector<triangle> tri_data;
	std::vector<GLfloat> data;
	nverts = 0;

	double nsegments = NSEGMENTS;

	double phi = -1.0f * (M_PI / 2.0f);
	double inc = (M_PI) / static_cast<float>(nsegments);

	for (int i = 0; i <= nsegments; i++) {

		double y = sin(phi);
		double r = cos(phi);
		disk(nsegments, y, r, tri_data, data, nverts);
		phi += inc;

	}

	return data;
}

Sphere::
Sphere(const GLint& mvp) : domahony::applications::Drawable(data(nverts), mvp),
idx(GL_ELEMENT_ARRAY_BUFFER)
{
	/*
	 * use the http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
	 */
	std::vector<GLushort> idx_data;

	int nsegments = NSEGMENTS;

	for (GLushort strip = 0; strip <= nsegments; strip++) {

		for (int i = 0; i <= nsegments; i++) {

			int cur = (strip * nsegments) + i;
			int nex = ((strip + 1) * nsegments) + i;

			idx_data.push_back(cur);
			idx_data.push_back(nex);

		}
	}

	idx.buffer_data(idx_data);
	idx_size = idx_data.size();

	std::cout << "Nverts: " << nverts << std::endl;
	std::cout << "IDX Size: " << idx_size << std::endl;

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

void Sphere::
enableVertexAttributes() const
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
}

void Sphere::
doDraw() const
{
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glPolygonMode( GL_FRONT, GL_LINE );
	glPolygonMode( GL_BACK, GL_FILL );
	//glPolygonMode( GL_FRONT, GL_POINT );
	//glPolygonMode( GL_BACK, GL_FILL );
	//glPolygonMode(GL_BACK, GL_FILL );
	//glDrawArrays(GL_LINE_STRIP, 0, nverts);
	idx.bind();
	glDrawElements(GL_TRIANGLE_STRIP, idx_size, GL_UNSIGNED_SHORT, 0);
}

void Sphere::
disableVertexAttributes() const
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

} /* namespace opengl */
} /* namespace domahony */
