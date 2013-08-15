/*
 * ObjShape.cc
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#include "ObjShape.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>
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
using glm::vec4;
using glm::ivec3;
using glm::ivec4;
using glm::normalize;
using glm::triangleNormal;
using std::istringstream;

#ifdef __cplusplus
extern "C" {
#endif
extern char redcube[];
#ifdef __cplusplus
}
#endif

ivec3
handle_face_buf(const std::string& buf)
{
	std::string tmp = buf;
	size_t idx = tmp.find("/");
	ivec3 ret(0);

	if (idx == std::string::npos) {
		ret.x = std::atoi(tmp.c_str());
		return ret;
	}

	ret.x = std::atoi(tmp.substr(0,idx).c_str());

	tmp = tmp.substr(idx + 1);

	if (!tmp.length()) {
		return ret;
	}

	idx = tmp.find("/");

	if (idx == std::string::npos) {
		ret.y = std::atoi(tmp.c_str());
		return ret;
	}

	if (idx != 1) {
		ret.y = std::atoi(tmp.substr(0,idx).c_str());
	}

	tmp = tmp.substr(idx + 1);

	if (!tmp.length()) {
		return ret;
	}

	ret.z = std::atoi(tmp.c_str());

	return ret;
}

static void
handle_face(std::vector<std::vector<ivec3> >& faces, istringstream& iss)
{
	std::string buf1, buf2, buf3;
	std::vector<ivec3> face;

	iss >>
		std::skipws >> buf1 >>
		std::skipws >> buf2 >>
		std::skipws >> buf3;

	ivec3 ibuf1 = handle_face_buf(buf1);
	ivec3 ibuf2 = handle_face_buf(buf2);
	ivec3 ibuf3 = handle_face_buf(buf3);

	face.push_back(ibuf1);
	face.push_back(ibuf2);
	face.push_back(ibuf3);

	faces.push_back(face);

	if (!iss.eof()) {
		face = std::vector<ivec3>();
		iss >> std::skipws >> buf1;
		ibuf1 = handle_face_buf(buf1);

		face.push_back(ibuf2);
		face.push_back(ibuf1);
		face.push_back(ibuf3);
	}

}

static std::vector<GLfloat>
data() 
{
	std::vector<GLfloat> ret;
	std::vector<glm::vec4> verts;
	std::vector<glm::vec4> normals;
	std::vector<std::vector<ivec3> > faces;

	istringstream iss(redcube);

	std::string buf;

	while (std::getline(iss, buf, '\n')) {

		istringstream iss2(buf);
		std::string c;
		iss2 >> std::skipws >> c;
		std::cout << "'" << c << "'" << std::endl;

		if (!c.compare("v")) {

			vec4 f;
			while (!iss2.eof()) {

				iss2 >> std::skipws >> f.x
					>> std::skipws >> f.y
					>> std::skipws >> f.z;

				if (!iss2.eof()) {
					iss2 >> std::skipws >> f.w;
				}

				std::cout << "(" <<
							f.x << "," <<
							f.y << "," <<
							f.z << "," <<
							f.w << ")" << std::endl;

				verts.push_back(f);
			}

		} else if (!c.compare("vn")) {

			vec4 f;
			while (!iss2.eof()) {

				iss2 >> std::skipws >> f.x
					>> std::skipws >> f.y
					>> std::skipws >> f.z;

				if (!iss2.eof()) {
					iss2 >> std::skipws >> f.w;
				}

				std::cout << "(" <<
							f.x << "," <<
							f.y << "," <<
							f.z << "," <<
							f.w << ")" << std::endl;

				normals.push_back(f);
			}

		} else if (!c.compare("f")) {
			handle_face(faces, iss2);
		}

	}

		for (std::vector<std::vector<ivec3> >::iterator iter = faces.begin(); iter != faces.end(); iter++) {

			for (std::vector<ivec3>::iterator iter2 = iter->begin(); iter2 != iter->end(); iter2++) {

				ret.push_back(verts[(*iter2)[0] - 1].x);
				ret.push_back(verts[(*iter2)[0] - 1].y);
				ret.push_back(verts[(*iter2)[0] - 1].z);

				if (!(*iter2)[2]) {
					ret.push_back(1);
					ret.push_back(0);
					ret.push_back(0);

				} else {

					ret.push_back(normals[(*iter2)[2] - 1].x);
					ret.push_back(normals[(*iter2)[2] - 1].y);
					ret.push_back(normals[(*iter2)[2] - 1].z);

				}

				ret.push_back(1);
				ret.push_back(0);
				ret.push_back(0);

			}
		}

	return ret;

}

ObjShape::ObjShape(const domahony::opengl::Program& p, const glm::mat4& l, const domahony::framework::Material& m) :
		domahony::applications::Drawable(p, data(), l, m)
{

}

void ObjShape::enableVertexAttributes() const {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
}

void ObjShape::doDraw(const domahony::framework::Camera& c) const {

	/*
	 * need to know location of
	 * location = location * local_location
	 *	draw(location)
	 */
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode( GL_FRONT, GL_FILL);
	glPolygonMode( GL_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 54);
}

void ObjShape::disableVertexAttributes() const {
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

ObjShape::~ObjShape() {
	// TODO Auto-generated destructor stub
}

} /* namespace opengl */
} /* namespace domahony */
