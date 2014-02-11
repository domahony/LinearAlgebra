/*
 * ObjShape.cc
 *
 *  Created on: 2013-06-24
 *      Author: domahony
 */

#include "ObjParser.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
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

struct Material {
	float Ns;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ks;
	float Ni;
	float d;
	short illum;
};

struct Face {
	std::string m;
	std::vector<ivec3> v;
};

static std::map<std::string, Material>
get_material(const char* mtl)
{
	std::map<std::string, Material> ret;

	if (!mtl) {
		return ret;
	}

	istringstream iss(mtl);

	std::string buf;
	std::string name;

	while (std::getline(iss, buf, '\n')) {

		istringstream iss2(buf);
		std::string c;
		iss2 >> std::skipws >> c;
		std::cout << "'" << c << "'" << std::endl;

		if (!c.compare("newmtl")) {

			if (!iss2.eof()) {
				iss2 >> std::skipws >> name;
			}

		} else if (!c.compare("Ns")) {

			if (!iss2.eof()) {
				iss2 >> std::skipws >> ret[name].Ns;
			}

		} else if (!c.compare("Ka")) {

			while (!iss2.eof()) {
				iss2 >> std::skipws >> ret[name].Ka.r
					>> std::skipws >> ret[name].Ka.g
					>> std::skipws >> ret[name].Ka.b;
			}

		} else if (!c.compare("Kd")) {

			while (!iss2.eof()) {
				iss2 >> std::skipws >> ret[name].Kd.r
					>> std::skipws >> ret[name].Kd.g
					>> std::skipws >> ret[name].Kd.b;
			}

		} else if (!c.compare("Ks")) {

			while (!iss2.eof()) {
				iss2 >> std::skipws >> ret[name].Ks.r
					>> std::skipws >> ret[name].Ks.g
					>> std::skipws >> ret[name].Ks.b;
			}

		} else if (!c.compare("Ni")) {

			if (!iss2.eof()) {
				iss2 >> std::skipws >> ret[name].Ni;
			}

		} else if (!c.compare("d")) {

			if (!iss2.eof()) {
				iss2 >> std::skipws >> ret[name].d;
			}

		} else if (!c.compare("illum")) {

			if (!iss2.eof()) {
				iss2 >> std::skipws >> ret[name].illum;
			}

		}
	}

	return ret;
}

static ivec3
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
handle_face(std::vector<Face>& faces, const std::string& material, istringstream& iss)
{
	std::string buf1, buf2, buf3;
	Face face;
	face.m = material;

	iss >>
		std::skipws >> buf1 >>
		std::skipws >> buf2 >>
		std::skipws >> buf3;

	ivec3 ibuf1 = handle_face_buf(buf1);
	ivec3 ibuf2 = handle_face_buf(buf2);
	ivec3 ibuf3 = handle_face_buf(buf3);

	face.v.push_back(ibuf1);
	face.v.push_back(ibuf2);
	face.v.push_back(ibuf3);

	faces.push_back(face);

	if (!iss.eof()) {
		face = Face();
		face.m = material;
		iss >> std::skipws >> buf1;
		ibuf1 = handle_face_buf(buf1);

		face.v.push_back(ibuf2);
		face.v.push_back(ibuf1);
		face.v.push_back(ibuf3);
	}

}

static void
handle_line(std::vector<Face>& faces, const std::string& material, istringstream& iss)
{
	std::string buf1, buf2;
	Face face;
	face.m = material;

	iss >>
		std::skipws >> buf1 >>
		std::skipws >> buf2;

	ivec3 ibuf1 = handle_face_buf(buf1);
	ivec3 ibuf2 = handle_face_buf(buf2);

	face.v.push_back(ibuf1);
	face.v.push_back(ibuf2);

	faces.push_back(face);

	if (!iss.eof()) {
		face = Face();
		face.m = material;
		iss >> std::skipws >> buf1;
		ibuf1 = handle_face_buf(buf1);

		face.v.push_back(ibuf2);
		face.v.push_back(ibuf1);
	}

}

static void
data(const char* data, const char* mtl, std::vector<GLfloat>& ret)
{
	std::vector<glm::vec4> verts;
	std::vector<glm::vec4> normals;
	std::vector<Face> faces;
	std::vector<Face> lines;

	std::map<std::string, Material> material = get_material(mtl);

	istringstream iss(data);

	std::string buf;
	std::string mat;

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
			handle_face(faces, mat, iss2);
		} else if (!c.compare("l"))	 {
			handle_line(lines, mat, iss2);
		} else if (!c.compare("usemtl")) {
			iss2 >> std::skipws >> mat;
			std::cout << "MATERIAL: " << mat << std::endl;
		}

	}

	for (std::map<std::string, Material>::iterator iter = material.begin(); iter != material.end(); iter++) {

		std::cout << "First: " << iter->first << std::endl;
		std::cout << "Second: " << iter->second.Kd.r << std::endl;
		std::cout << "Second: " << iter->second.Kd.g << std::endl;
		std::cout << "Second: " << iter->second.Kd.b << std::endl;

	}

		for (std::vector<Face>::iterator iter = faces.begin(); iter != faces.end(); iter++) {

			for (std::vector<ivec3>::iterator iter2 = iter->v.begin(); iter2 != iter->v.end(); iter2++) {

				ret.push_back(verts[(*iter2)[0] - 1].x);
				ret.push_back(verts[(*iter2)[0] - 1].y);
				ret.push_back(verts[(*iter2)[0] - 1].z);

				if (!(*iter2)[2]) {

					ret.push_back(material[iter->m].Kd.r);
					ret.push_back(material[iter->m].Kd.g);
					ret.push_back(material[iter->m].Kd.b);

				} else {

					ret.push_back(normals[(*iter2)[2] - 1].x);
					ret.push_back(normals[(*iter2)[2] - 1].y);
					ret.push_back(normals[(*iter2)[2] - 1].z);

				}

				ret.push_back(material[iter->m].Kd.r);
				ret.push_back(material[iter->m].Kd.g);
				ret.push_back(material[iter->m].Kd.b);

			}
		}

		for (std::vector<Face>::iterator iter = lines.begin(); iter != lines.end(); iter++) {

			for (std::vector<ivec3>::iterator iter2 = iter->v.begin(); iter2 != iter->v.end(); iter2++) {
				ret.push_back(verts[(*iter2)[0] - 1].x);
				ret.push_back(verts[(*iter2)[0] - 1].y);
				ret.push_back(verts[(*iter2)[0] - 1].z);
			}
		}
}

void ObjParser::
get_data(const char* buf, std::vector<GLfloat>& ret)
{
	data(buf, 0, ret);
}

void ObjParser::
get_data(const char* buf, const char* mtl, std::vector<GLfloat>& ret)
{
	data(buf, mtl, ret);
}

} /* namespace opengl */
} /* namespace domahony */
