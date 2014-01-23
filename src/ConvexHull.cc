/*
 * ConvexHull.cc
 *
 *  Created on: 2013-12-18
 *      Author: domahony
 */

#include "ConvexHull.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3_to_polyhedron_3.h>
#include <CGAL/centroid.h>
#include <CGAL/Min_sphere_d.h>
#include <CGAL/Min_sphere_annulus_d_traits_3.h>
#include <CGAL/Cartesian_d.h>
//#include <CGAL/algorithm.h>
#include <list>
#include <CGAL/Min_sphere_annulus_d_traits_d.h>
#include <CGAL/Min_sphere_d.h>

typedef CGAL::Cartesian_d<double>              Kd;

typedef CGAL::Exact_predicates_inexact_constructions_kernel      K;
typedef K::Point_3                                              Point_3;
typedef K::Vector_3                                         	Vector_3;
typedef CGAL::Delaunay_triangulation_3<K>                       Delaunay;
typedef CGAL::Delaunay_triangulation_3<K>::Finite_vertices_iterator      Vertex_iterator;
typedef Delaunay::Vertex_handle                                 Vertex_handle;
typedef Delaunay::Edge                                 		Edge;
typedef Edge::first_type									FirstTypeEdge;
typedef CGAL::Polyhedron_3<K>                                   Polyhedron_3;

typedef CGAL::Min_sphere_annulus_d_traits_d<Kd> Traits;
typedef CGAL::Min_sphere_d<Traits>             Min_sphere;
typedef Kd::Point_d                             Point;

namespace domahony {
namespace opengl {

ConvexHull::ConvexHull() {
	// TODO Auto-generated constructor stub

}

ConvexHull::~ConvexHull() {
	// TODO Auto-generated destructor stub
}

static void func(const Delaunay& T, const std::list<Polyhedron_3::Point_3>& points, std::vector<GLfloat>& data, glm::vec3& centroid);

/*
void ConvexHull::
get_data(
			std::vector<domahony::framework::SphereListCreator::Sphere>::iterator begin,
			std::vector<domahony::framework::SphereListCreator::Sphere>::iterator end,
			std::vector<GLfloat>& data,
			glm::vec3& centroid)
{
	Delaunay T;

	std::list<Polyhedron_3::Point_3>   points;

	for (std::vector<domahony::framework::SphereListCreator::Sphere>::iterator iter = begin; iter != end; iter++) {
		  points.push_back(Point_3(iter->center.x, iter->center.y, iter->center.z));
	}

	std::cout << "Points Size: " << points.size() << std::endl;

	T.insert(points.begin(), points.end());

	 func(T, points, data, centroid);
}
*/

void ConvexHull::
get_data(
	std::vector<domahony::framework::SphereListCreator::Sphere>::iterator begin,
	std::vector<domahony::framework::SphereListCreator::Sphere>::iterator end,
		std::vector<GLfloat>& data,
		glm::vec3& centroid)
{
	  Delaunay T;

	  std::list<Polyhedron_3::Point_3>   points;

	  for (; begin != end - 0; begin++) {
		  points.push_back(Point_3(begin->center.x, begin->center.y, begin->center.z));
	  }

	  T.insert(points.begin(), points.end());

	  func(T, points, data, centroid);
}

void ConvexHull::
get_data(
		std::vector<domahony::physics::Physics::ContactInfoItem>::iterator begin,
		std::vector<domahony::physics::Physics::ContactInfoItem>::iterator end,
		std::vector<GLfloat>& data,
		glm::vec3& centroid)
{
	  Delaunay T;

	  std::list<Polyhedron_3::Point_3>   points;

	  for (std::vector<domahony::physics::Physics::ContactInfoItem>::iterator iter = begin; iter != end; iter++) {
		  points.push_back(Point_3(iter->pt.x, iter->pt.y, iter->pt.z));
	  }

	  T.insert(points.begin(), points.end());

	  func(T, points, data, centroid);
}

static void func(const Delaunay& T, const std::list<Point_3>& points, std::vector<GLfloat>& data, glm::vec3& centroid)
{
	  std::list<Vertex_handle>  vertices;
	  T.incident_vertices(T.infinite_vertex(), std::back_inserter(vertices));
	  std::cout << "This convex hull of the " << points.size() << " points has "
	            << vertices.size() << " points on it." << std::endl;

	 std::list<Edge>  edges;

	 T.incident_edges(T.infinite_vertex(), std::back_inserter(edges));

	  int diff = 0;
	  for (Vertex_iterator iter = T.finite_vertices_begin(); iter != T.finite_vertices_end(); iter++) {
		  diff++;
	  }

	  std::cout << "This convex hull of the " << points.size() << " points has "
	            << diff << " points on it." << std::endl;

	  std::cout << "This convex hull of the " << points.size() << " points has "
	            << edges.size() << " edges." << std::endl;

	  for (std::list<Edge>::iterator iter = edges.begin(); iter != edges.end(); iter++) {

		  bool isvalid = false;
		  if (iter->first->is_valid(isvalid, iter->second)) {
		  std::cout << "Edge V1: " <<
			 iter->first->vertex(iter->second)->point().x() << " " <<
			 iter->first->vertex(iter->second)->point().y() << " " <<
			 iter->first->vertex(iter->second)->point().z() << std::endl;
		  }

		  if (iter->first->is_valid(isvalid, iter->third)) {
		  std::cout << "Edge V2: " <<
			 iter->first->vertex(iter->third)->point().x() << " " <<
			 iter->first->vertex(iter->third)->point().y() << " " <<
			 iter->first->vertex(iter->third)->point().z() << std::endl;
		  }
	  }

	  Polyhedron_3 chull;
	  CGAL::convex_hull_3_to_polyhedron_3(T,chull);

	  for (Polyhedron_3::Plane_iterator iter = chull.planes_begin(); iter != chull.planes_end(); iter++) {

		  std::cout
		  	  	  << iter->a() << ","
		  	  	  << iter->b() << ","
		  	  	  << iter->c() << ","
		  	  	  << iter->d()
				  << std::endl;
	  }

	  std::vector<Polyhedron_3::Point_3> vpoints;

	  for (Polyhedron_3::Facet_iterator iter = chull.facets_begin(); iter != chull.facets_end(); iter++) {

		  std::cout << "Is Triangle: " << iter->is_triangle() << std::endl;
		  std::cout << "Is Quad: " << iter->is_quad() << std::endl;
		  std::cout << "Degree: " << iter->facet_degree() << std::endl;

		  Polyhedron_3::Halfedge_around_facet_circulator iter2 = iter->facet_begin();

		  Polyhedron_3::Point_3 norm[3];
		  for (int i = 0; i < iter->facet_degree(); i++) {

			  Polyhedron_3::Vertex_handle vh = iter2->vertex();
			  Polyhedron_3::Point_3 p = vh->point();
			  vpoints.push_back(p);
			  norm[i] = p;

			  std::cout
			  	  << p.x() << ", "
			  	  << p.y() << ", "
			  	  << p.z()
			  	  << std::endl;

			  data.push_back(p.x());
			  data.push_back(p.y());
			  data.push_back(p.z());

			  data.push_back(0);
			  data.push_back(0);
			  data.push_back(0);

			  data.push_back(0);
			  data.push_back(0);
			  data.push_back(1);
			  iter2++;
		  }

		  Vector_3 n = CGAL::normal(norm[0], norm[1], norm[2]);

		  data[data.size() - 6] = n.x();
		  data[data.size() - 5] = n.y();
		  data[data.size() - 4] = n.z();

		  data[data.size() - 15] = n.x();
		  data[data.size() - 14] = n.y();
		  data[data.size() - 13] = n.z();

		  data[data.size() - 24] = n.x();
		  data[data.size() - 23] = n.y();
		  data[data.size() - 22] = n.z();
	  }

	  Polyhedron_3::Point_3 c = CGAL::centroid(vpoints.begin(), vpoints.end());
	  centroid.x = c.x();
	  centroid.y = c.y();
	  centroid.z = c.z();

	  std::vector<Point> mspoints;
	  //for (std::vector<Polyhedron_3::Point_3>::iterator piter = vpoints.begin(); piter != vpoints.end(); piter++) {
	  for (std::list<Polyhedron_3::Point_3>::const_iterator piter = points.begin(); piter != points.end(); piter++) {
		  mspoints.push_back(Point(piter->x(), piter->y(), piter->z(), 1.f));
	  }

	  Min_sphere ms(mspoints.begin(), mspoints.end());
	  centroid.x = ms.center().x();
	  centroid.y = ms.center().y();
	  centroid.z = ms.center().z();

}

} /* namespace opengl */
} /* namespace domahony */
