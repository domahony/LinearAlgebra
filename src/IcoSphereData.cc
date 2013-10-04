/*
 * IcoSphereData.cc
 *
 *  Created on: 2013-09-26
 *      Author: domahony
 */

#include "IcoSphereData.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>
#include <cmath>
#include <map>
#include <iostream>

namespace domahony {
namespace framework {

using glm::mat4;
using glm::vec3;
using glm::normalize;
using glm::triangleNormal;

const double IcoSphereData::phi = (1.0 + sqrt(5)) / 2.0;

struct edge_key {

	edge_key(const int& i1, const int& i2)
	{
		pt[0] = i1 < i2 ? i1 : i2;
		pt[1] = i1 < i2 ? i2 : i1;
	}

	bool operator< (const edge_key& other) const {

		if (this->pt[0] < other.pt[0]) {
			return true;
		}

		return this->pt[1] < other.pt[1];
	}

	int pt[2];
};

struct comp {
	bool operator() (const edge_key& l, const edge_key& r) {
		return l < r;
	}
};

struct triangle_idx {
	triangle_idx(const int& idx0, const int& idx1, const int& idx2) {
		idx[0] = idx0;
		idx[1] = idx1;
		idx[2] = idx2;
	}

	int idx[3];
};

static int
get_middle_point(std::map<edge_key, int>& m,
	std::vector<vec3>& v, int p1, int p2)
{
	edge_key e(p1, p2);
	std::map<edge_key, int>::iterator iter = m.find(e);

	if (iter != m.end()) {
		return iter->second;
	}

	vec3 v1 = v[p1];
	vec3 v2 = v[p2];

	vec3 mid(
			(v1.x + v2.x)/2.0,
			(v1.y + v2.y)/2.0,
			(v1.z + v2.z)/2.0
	);

	v.push_back(normalize(mid));
	int idx = v.size() - 1;

	m.insert(std::pair<edge_key, int>(e, idx));

	return idx;
}

std::vector<int>
find_neighbors(const std::vector<triangle_idx>& tri, const int& idx)
{
	std::vector<int> ret;
	for (std::vector<triangle_idx>::const_iterator iter = tri.begin(); iter != tri.end(); iter++) {
		if (iter->idx[0] == idx || iter->idx[1] == idx || iter->idx[2] == idx) {
			ret.push_back(iter - tri.begin());
		}
	}

	return ret;
}

static std::vector<GLfloat>
data(int& nverts, const int& reso)
{
	std::vector<vec3> verts;
	/*
	 * use the http://blog.andreaskahler.com/2009/06/creating-icosphere-mesh-in-code.html
	 */

	verts.push_back(normalize(vec3(-1,IcoSphereData::phi, 0)));
	verts.push_back(normalize(vec3(1,IcoSphereData::phi, 0)));
	verts.push_back(normalize(vec3(-1,-IcoSphereData::phi, 0)));
	verts.push_back(normalize(vec3(1,-IcoSphereData::phi, 0)));

	verts.push_back(normalize(vec3(0,-1,IcoSphereData::phi)));
	verts.push_back(normalize(vec3(0,1,IcoSphereData::phi)));
	verts.push_back(normalize(vec3(0,-1,-IcoSphereData::phi)));
	verts.push_back(normalize(vec3(0,1,-IcoSphereData::phi)));

	verts.push_back(normalize(vec3(IcoSphereData::phi, 0, -1)));
	verts.push_back(normalize(vec3(IcoSphereData::phi, 0, 1)));
	verts.push_back(normalize(vec3(-IcoSphereData::phi, 0, -1)));
	verts.push_back(normalize(vec3(-IcoSphereData::phi, 0, 1)));

	std::vector<triangle_idx> triangles;
	triangles.push_back(triangle_idx( 0, 11, 5));
	triangles.push_back(triangle_idx( 0, 5, 1));
	triangles.push_back(triangle_idx( 0, 1, 7));
	triangles.push_back(triangle_idx( 0, 7, 10));
	triangles.push_back(triangle_idx( 0, 10, 11));

	triangles.push_back(triangle_idx( 1, 5, 9));
	triangles.push_back(triangle_idx( 5, 11, 4));
	triangles.push_back(triangle_idx( 11, 10, 2));
	triangles.push_back(triangle_idx( 10, 7, 6));
	triangles.push_back(triangle_idx( 7, 1, 8));

	triangles.push_back(triangle_idx( 3, 9, 4));
	triangles.push_back(triangle_idx( 3, 4, 2));
	triangles.push_back(triangle_idx( 3, 2, 6));
	triangles.push_back(triangle_idx( 3, 6, 8));
	triangles.push_back(triangle_idx( 3, 8, 9));

	triangles.push_back(triangle_idx( 4, 9, 5));
	triangles.push_back(triangle_idx( 2, 4, 11));
	triangles.push_back(triangle_idx( 6, 2, 10));
	triangles.push_back(triangle_idx( 8, 6, 7));
	triangles.push_back(triangle_idx( 9, 8, 1));

	std::vector<GLfloat> ret;

	std::map<edge_key, int> m;

	for (int i = 0; i < reso; i++) {
		std::vector<triangle_idx> triangles2;
		for (std::vector<triangle_idx>::iterator iter = triangles.begin(); iter != triangles.end(); iter++) {

			int a = get_middle_point(m, verts, iter->idx[0], iter->idx[1]);
			int b = get_middle_point(m, verts, iter->idx[1], iter->idx[2]);
			int c = get_middle_point(m, verts, iter->idx[2], iter->idx[0]);

			triangles2.push_back(triangle_idx(iter->idx[0], a, c));
			triangles2.push_back(triangle_idx(iter->idx[1], b, a));
			triangles2.push_back(triangle_idx(iter->idx[2], c, b));
			triangles2.push_back(triangle_idx(a, b, c));
		}

		triangles = triangles2;
	}

	nverts = 0;
	for (std::vector<triangle_idx>::iterator iter = triangles.begin(); iter != triangles.end(); iter++) {
			ret.push_back(verts[iter->idx[0]].x);
			ret.push_back(verts[iter->idx[0]].y);
			ret.push_back(verts[iter->idx[0]].z);

			vec3 norm = triangleNormal(verts[iter->idx[0]], verts[iter->idx[1]], verts[iter->idx[2]]);
			std::vector<int> neighbors = find_neighbors(triangles, iter->idx[0]);
			for (std::vector<int>::iterator i = neighbors.begin(); i != neighbors.end(); i++) {
				norm += triangleNormal(
						verts[triangles[*i].idx[0]],
						verts[triangles[*i].idx[1]],
						verts[triangles[*i].idx[2]]);
			}
			norm = normalize(norm);
			ret.push_back(norm.x);
			ret.push_back(norm.y);
			ret.push_back(norm.z);

			if (verts[iter->idx[0]].x > 0) {
				ret.push_back(1);
				ret.push_back(0);
				ret.push_back(0);
			} else {
				ret.push_back(0);
				ret.push_back(1);
				ret.push_back(0);
			}

			ret.push_back(verts[iter->idx[1]].x);
			ret.push_back(verts[iter->idx[1]].y);
			ret.push_back(verts[iter->idx[1]].z);

			neighbors = find_neighbors(triangles, iter->idx[1]);
			norm = triangleNormal(verts[iter->idx[0]], verts[iter->idx[1]], verts[iter->idx[2]]);
			for (std::vector<int>::iterator i = neighbors.begin(); i != neighbors.end(); i++) {
				norm += triangleNormal(
						verts[triangles[*i].idx[0]],
						verts[triangles[*i].idx[1]],
						verts[triangles[*i].idx[2]]);
			}
			norm = normalize(norm);
			ret.push_back(norm.x);
			ret.push_back(norm.y);
			ret.push_back(norm.z);

			if (verts[iter->idx[1]].x > 0) {
				ret.push_back(1);
				ret.push_back(0);
				ret.push_back(0);
			} else {
				ret.push_back(0);
				ret.push_back(1);
				ret.push_back(0);
			}

			ret.push_back(verts[iter->idx[2]].x);
			ret.push_back(verts[iter->idx[2]].y);
			ret.push_back(verts[iter->idx[2]].z);
			neighbors = find_neighbors(triangles, iter->idx[2]);

			norm = triangleNormal(verts[iter->idx[0]], verts[iter->idx[1]], verts[iter->idx[2]]);
			for (std::vector<int>::iterator i = neighbors.begin(); i != neighbors.end(); i++) {
				norm += triangleNormal(
						verts[triangles[*i].idx[0]],
						verts[triangles[*i].idx[1]],
						verts[triangles[*i].idx[2]]);
			}
			norm = normalize(norm);
			ret.push_back(norm.x);
			ret.push_back(norm.y);
			ret.push_back(norm.z);

			if (verts[iter->idx[2]].x > 0) {
				ret.push_back(1);
				ret.push_back(0);
				ret.push_back(0);
			} else {
				ret.push_back(0);
				ret.push_back(1);
				ret.push_back(0);
			}

			/*
			std::cout << "Normal: "
					<< norm.x << ", "
					<< norm.y << ", "
					<< norm.z << ", "
					<< std::endl;
			*/

			nverts+=36;
	}


	std::cout << "Number of triangles: " << triangles.size() << std::endl;

	return ret;
}

IcoSphereData::IcoSphereData() {
	// TODO Auto-generated constructor stub

}

IcoSphereData::~IcoSphereData() {
	// TODO Auto-generated destructor stub
}


std::vector<GLfloat>
IcoSphereData::get_data() {

	int nverts = 0;
	int reso = 3;

	return data(nverts, reso);

}

} /* namespace framework */
} /* namespace domahony */
