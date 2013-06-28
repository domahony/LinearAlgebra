/*
 * Sphere.cc
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#define _USE_MATH_DEFINES

#include "Sphere.h"
#include <vector>
#include <cmath>
#include <iostream>

#define NSEGMENTS 5

namespace domahony {
namespace opengl {

static void
disk(const int& nsegments, const float& y, const float& r, std::vector<GLfloat>& data, int& nverts)
{
	double x;
	double z;

	double A = 0;
	double increment = 2.0f * M_PI / static_cast<float>(nsegments);

	for (int xinc = 0; xinc <= nsegments; xinc++) {
			z = r * sin(A);
			x = r * cos(A);
			A += increment;
			std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
			data.push_back(x);
			data.push_back(y);
			data.push_back(z);

			nverts++;
	}

}

static std::vector<GLfloat>
data(int &nverts)
{
	std::vector<GLfloat> data;
	nverts = 0;

	double nsegments = 48;

	double phi = -1.0f * (M_PI / 2.0f);
	double inc = (M_PI) / static_cast<float>(nsegments);

	for (int i = 0; i <= nsegments; i++) {

		double y = sin(phi);
		double r = cos(phi);
		disk(nsegments, y, r, data, nverts);
		phi += inc;

	}

	return data;
}

Sphere::
Sphere(const glm::mat4& location, const GLint& mvp) : domahony::applications::Drawable(data(nverts), location, mvp)
{
	// TODO Auto-generated constructor stub

}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

void Sphere::
enableVertexAttributes() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void Sphere::
doDraw() const
{
	glDrawArrays(GL_LINE_STRIP, 0, nverts);
}

void Sphere::
disableVertexAttributes() const
{
	glDisableVertexAttribArray(0);
}

} /* namespace opengl */
} /* namespace domahony */
