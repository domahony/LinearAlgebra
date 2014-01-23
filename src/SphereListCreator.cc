/*
 * SphereListCreator.cc
 *
 *  Created on: 2013-12-15
 *      Author: domahony
 */

#include <CGAL/Random.h>
#include <CGAL/Gmpfr.h>
#include <CGAL/Cartesian_d.h>
#include <CGAL/Min_sphere_of_spheres_d.h>
#include "SphereListCreator.h"

//typedef CGAL::Gmpq FT;
typedef double FT;
typedef CGAL::Cartesian_d<FT>	K;
typedef CGAL::Min_sphere_of_spheres_d_traits_d<K, FT, 3> Traits;
typedef CGAL::Min_sphere_of_spheres_d<Traits> Min_sphere;
typedef CGAL::Min_sphere_of_spheres_d<Traits>::Cartesian_const_iterator CIter;
typedef K::Point_d	CGALPoint;
typedef Traits::Sphere	CGALSphere; 

namespace domahony {
namespace framework {

std::vector<SphereListCreator::Sphere> SphereListCreator::
getSphereList(const int&nSpheres, const int& maxRadius, 
	const glm::ivec3& low, const glm::ivec3& high)
{
	CGAL::Random r;
	std::vector<SphereListCreator::Sphere> ret;
	std::vector<CGALSphere> s;

	FT coord[3];	
	for (int i = 0; i < nSpheres; i++) {

		coord[0] = r.get_int(low.x, high.x);
		coord[1] = r.get_int(low.y, high.y);
		coord[2] = r.get_int(low.z, high.z);
		CGALPoint p(3, coord, coord+3);

		s.push_back(CGALSphere(p, r.get_int(1, maxRadius)));

		SphereListCreator::Sphere sphere;
		sphere.radius = s[s.size() - 1].second;
		sphere.center.x = s[s.size() - 1].first[0];
		sphere.center.y = s[s.size() - 1].first[1];
		sphere.center.z = s[s.size() - 1].first[2];

		ret.push_back(sphere);
	}

	Min_sphere ms(s.begin(), s.end());

	SphereListCreator::Sphere sphere;
	sphere.radius = ms.radius();

	CIter iter = ms.center_cartesian_begin();
	sphere.center.x = *iter;
	sphere.center.y = *(iter + 1);
	sphere.center.z = *(iter + 2);

	ret.push_back(sphere);

	return ret;
}

SphereListCreator::SphereListCreator() {
	// TODO Auto-generated constructor stub

}

SphereListCreator::~SphereListCreator() {
	// TODO Auto-generated destructor stub
}

} /* namespace framework */
} /* namespace domahony */
