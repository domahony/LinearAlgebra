/*
 * App2.cc
 *
 *  Created on: 2013-09-05
 *      Author: domahony
 */

#include <vector>
#include <iostream>
#include "App2.h"
#include "BodyCreator.h"
#include "AppObject.h"
#include "ObjParser.h"
#include "Shader.h"
#include "Program.h"
#include "IcoSphereData.h"

#ifdef __cplusplus
extern "C" {
#endif
extern char pyramid[];
extern char die2[];
extern char fragment[];
extern char vertex[];
extern char groundplane[];
extern char die4[];
extern char die4_mtl[];
extern char NewHead8[];
#ifdef __cplusplus
}
#endif

using domahony::opengl::Shader;
using domahony::opengl::Program;

namespace domahony {
namespace applications {



std::ostream& operator<< (std::ostream& os, const glm::vec4& v) {

	os << "("
	<< v.x << ","
	<< v.y << ","
	<< v.z << ","
	<< v.w <<
	")";

	return os;
}

std::ostream& operator<< (std::ostream& os, const glm::mat4& m) {

	os << "("
	<< m[0] << std::endl
	<< m[1] << std::endl
	<< m[2] << std::endl
	<< m[3]
	<<  ")";

	return os;
}

glm::vec3 get_rotationx(const domahony::framework::Camera& camera, const glm::vec4& dir)
{
				std::cout << "View: " << camera.view() << std::endl;
				std::cout << "Projection: " << camera.projection() << std::endl;

				glm::vec4 dir2(glm::inverse(camera.projection() * camera.view()) * dir);

				glm::vec3 rota(glm::normalize(glm::vec3(dir2)));

				return rota;
}

glm::vec3 get_rotation(const domahony::framework::Camera& camera, const glm::vec4& dir)
{
				std::cout << "View: " << camera.view() << std::endl;
				std::cout << "Projection: " << camera.projection() << std::endl;

				glm::mat4 inverse_projection(glm::inverse(camera.projection()));
				glm::vec4 v_cam(inverse_projection * dir); v_cam /= v_cam.w;

				glm::mat4 inverse_view(glm::inverse(camera.view()));
				glm::vec4 v_world(inverse_view * v_cam); v_world /= v_world.w;

				glm::vec3 rota(glm::normalize(glm::vec3(v_world)));

				//return rota;

				glm::vec3 ret(dir);
				return ret;


				//return rota;
}

App2::App2(const int& width, const int& height) : App(), display(width, height), physics(),
		//light(glm::normalize(glm::vec3(-1,3,15)), glm::vec3(1,1,1), 100), active(0)
		light(glm::normalize(glm::vec3(-1,-1,0)), glm::vec3(1,1,1), 0.1), active(0)
{
	// TODO Auto-generated constructor stub

}

int App2::
_init()
{
	Program program;

	Shader vshader(GL_VERTEX_SHADER, vertex);
	program.attach_shader(vshader);

	Shader fshader(GL_FRAGMENT_SHADER, fragment);
	program.attach_shader(fshader);

	program.link();

	std::vector<GLfloat> data;
	data = domahony::framework::IcoSphereData::get_data();

	std::vector<GLfloat> groundplane_data;
	domahony::opengl::ObjParser::get_data(groundplane, groundplane_data);

	std::vector<GLfloat> die4_data;
	domahony::opengl::ObjParser::get_data(die4, die4_mtl, die4_data);

	std::vector<GLfloat> head_data;
	domahony::opengl::ObjParser::get_data(NewHead8, head_data);

	std::cout << "Size: " << data.size() << std::endl;
	std::cout << "Size: " << groundplane_data.size() << std::endl;

	domahony::framework::Material m1(glm::vec3(.6), 1);

	boost::shared_ptr<AppObject> plane(new AppObject(glm::translate(glm::mat4(1.), glm::vec3(0, 0, 0)), program, groundplane_data, m1));
	//boost::shared_ptr<AppObject> obj2(new AppObject(glm::translate(glm::mat4(1.), glm::vec3(3, 3, 10)), program, data, m1));
	boost::shared_ptr<AppObject> obj(new AppObject(glm::translate(glm::mat4(1.), glm::vec3(0, 5, 0)), program, data, m1));
	boost::shared_ptr<AppObject> die4_obj(new AppObject(glm::translate(glm::mat4(1.), glm::vec3(2, 5, 0)), program, die4_data, m1));
	boost::shared_ptr<AppObject> die4_obj2(new AppObject(glm::translate(glm::mat4(1.), glm::vec3(0, 6, 5)), program, die4_data, m1));
	boost::shared_ptr<AppObject> die4_obj3(new AppObject(glm::translate(glm::mat4(1.), glm::vec3(3, 3, 3)), program, die4_data, m1));
	boost::shared_ptr<AppObject> head(new AppObject(glm::translate(glm::mat4(1.), glm::vec3(1.5, 0.1, 0)), program, head_data, m1));

	physics.add_body(*plane);
	physics.add_body(*obj);
	//physics.add_body(*obj2);
	physics.add_body(*die4_obj);
	physics.add_body(*die4_obj2);
	physics.add_body(*die4_obj3);
	physics.add_body(*head);

	object.push_back(die4_obj);
	object.push_back(die4_obj2);
	object.push_back(die4_obj3);
	object.push_back(head);

	object.push_back(plane);
	object.push_back(obj);
	//object.push_back(obj2);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.f);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.f, 1.f);

	return 1;
}

bool App2::
window(const SDL_WindowEvent& w)
{
	bool ret = false;
	switch (w.event) {

	case SDL_WINDOWEVENT_RESIZED :
		std::cout << "Hello!! " << w.data1 << "," << w.data2 << std::endl;
		display.resize(w.data1, w.data2);
		camera.update_perspective(w.data1, w.data2);
		ret = true;
		break;
	default:
		break;
	}

	return ret;
}

bool App2::
button(const SDL_MouseButtonEvent& b)
{

	if (b.state != SDL_PRESSED) {

		if (active) {
			return true;
		}

		return false;
	}

	if (b.button == SDL_BUTTON_RIGHT) {
		if (active) {
			active->set_active(false);
			active = 0;
			return true;
		}
	}

	if (b.button != SDL_BUTTON_LEFT) {
		return false;
	}


	int mouse_y = display.get_height() - b.y;

	std::cout << "x:" << b.x << ", y: " << mouse_y << std::endl;

	// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
	glm::vec4 lRayStart_NDC(
	    ((static_cast<GLfloat>(b.x)/static_cast<GLfloat>(display.get_width()))  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
	    ((static_cast<GLfloat>(mouse_y)/static_cast<GLfloat>(display.get_height())) - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
	    -1.0f, // The near plane maps to Z=-1 in Normalized Device Coordinates
	    1.0f
	);
	glm::vec4 lRayEnd_NDC(
	    ((static_cast<GLfloat>(b.x)/static_cast<GLfloat>(display.get_width()))  - 0.5f) * 2.0f,
	    ((static_cast<GLfloat>(mouse_y)/static_cast<GLfloat>(display.get_height())) - 0.5f) * 2.0f,
	    0.0f,
	    1.0f
	);

	std::cout
			<< "(" << lRayStart_NDC.x << ", "
			<< lRayStart_NDC.y << ", "
			<< lRayStart_NDC.z << ") -> "
			<< "(" << lRayEnd_NDC.x << ", "
			<< lRayEnd_NDC.y << ", "
			<< lRayEnd_NDC.z << ")"
			<< std::endl;

	// The Projection matrix goes from Camera Space to NDC.
	// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
	glm::mat4 InverseProjectionMatrix = glm::inverse((camera.projection()));

	// The View Matrix goes from World Space to Camera Space.
	// So inverse(ViewMatrix) goes from Camera Space to World Space.
	glm::mat4 InverseViewMatrix = glm::inverse((camera.view()));

	glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera/=lRayStart_camera.w;
	glm::vec4 lRayStart_world  = InverseViewMatrix       * lRayStart_camera; lRayStart_world /=lRayStart_world .w;
	glm::vec4 lRayEnd_camera   = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera  /=lRayEnd_camera  .w;
	glm::vec4 lRayEnd_world    = InverseViewMatrix       * lRayEnd_camera;   lRayEnd_world   /=lRayEnd_world   .w;

	// Faster way (just one inverse)
	//glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
	//glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
	//glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;

	std::cout
			<< "(" << lRayStart_world.x << ", "
			<< lRayStart_world.y << ", "
			<< lRayStart_world.z << ") -> "
			<< "(" << lRayEnd_world.x << ", "
			<< lRayEnd_world.y << ", "
			<< lRayEnd_world.z << ")"
			<< std::endl;

	glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
	lRayDir_world = glm::normalize(lRayDir_world);

	std::cout
			<< "Dir: (" << lRayDir_world.x << ", "
			<< lRayDir_world.y << ", "
			<< lRayDir_world.z << ")"
			<< std::endl;

	active = static_cast<AppObject*>(physics.get_click_object(lRayStart_world, lRayDir_world));

	if (active) {
		std::cout << "Yeah!!" << std::endl;
		active->set_active(true);
	} else {
		std::cout << "Boo!!" << std::endl;
	}

	return true;
}

bool App2::
motion(const SDL_MouseMotionEvent& m)
{

	if (active) {

		glm::vec4 origin(active->get_origin(), 1);

		glm::vec4 origin_ndc = camera.projection() * camera.view() * origin;
		origin_ndc /= origin_ndc.w;
		std::cout << "ORIGIN_NDC: " << origin_ndc.x << ", " << origin_ndc.y << ", " << origin_ndc.z << std::endl;
		std::cout << "ORIGIN: " << origin.x << ", " << origin.y << ", " << origin.z << std::endl;

		std::cout << "New: " << m.x << ", " << m.y << std::endl;

		int newY = display.get_height() - m.y;

		glm::vec4 ndc(
				((static_cast<GLfloat>(m.x)/static_cast<GLfloat>(display.get_width()))  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
				((static_cast<GLfloat>(newY)/static_cast<GLfloat>(display.get_height())) - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
				origin_ndc.z,
				1.0f
		);

		std::cout << "NDC: " << ndc.x << ", " << ndc.y << ", " << ndc.z << std::endl;

		glm::mat4 InverseProjectionMatrix = glm::inverse((camera.projection()));

		glm::vec4 cam = InverseProjectionMatrix * ndc;    cam/=cam.w;
		std::cout << "Camera: " << cam.x << ", " << cam.y << ", " << cam.z << std::endl;

		glm::mat4 InverseViewMatrix = glm::inverse((camera.view()));

		glm::vec4 world  = InverseViewMatrix       * cam; world /=world.w;

		std::cout << world.x << ", " << world.y << ", " << world.z << std::endl;

		active->set_location(glm::translate(glm::mat4(1.0f), glm::vec3(world)));

		if (physics.any_touches()) {

		}

		return true;

	} else {
		return false;
	}
}

bool App2::
key(const SDL_KeyboardEvent& e)
{
	bool ret = false;
	if (e.type == SDL_KEYUP) {
		return ret;
	}

	switch (e.keysym.sym) {
	case SDLK_a:

		if (e.keysym.mod & KMOD_SHIFT) {
			light.set_global(light.get_global() - 0.01);
		} else {
			light.set_global(light.get_global() + 0.01);
		}

		std::cout << "Light: " << light.get_global() << std::endl;

		ret = true;
		break;
	case SDLK_UP:

		if (e.keysym.mod & KMOD_SHIFT) {
			//camera.get_light().up();
		} else {

			if (active) {
				active->rotate(get_rotation(camera, glm::vec4(0,0,1,1)));
			} else {
				camera.up();
			}
		}

		ret = true;
		break;
	case SDLK_DOWN:

		if (e.keysym.mod & KMOD_SHIFT) {
			//camera.get_light().down();
		} else {
			if (active) {
				active->rotate(get_rotation(camera, glm::vec4(0,0,-1,1)));
			} else {
				camera.down();
			}
		}

		ret = true;
		break;
	case SDLK_LEFT:

		if (e.keysym.mod & KMOD_SHIFT) {
			//camera.get_light().left();
		} else {
			if (active) {
				active->rotate(get_rotation(camera, glm::vec4(0,-1,0,1)));
			} else {
				camera.left();
			}
		}

		ret = true;
		break;
	case SDLK_RIGHT:
		if (e.keysym.mod & KMOD_SHIFT) {
			//camera.get_light().right();
		} else {
			if (active) {
				active->rotate(get_rotation(camera, glm::vec4(0,1,0,1)));
			} else {
			camera.right();
			}
		}
		ret = true;
		break;
	case SDLK_i:
		if (e.keysym.mod & KMOD_SHIFT) {
			//camera.get_light().in();
		} else {
			if (active) {
				active->rotate(get_rotation(camera, glm::vec4(1,0,0,1)));
			} else {
				camera.in();
			}
		}
		ret = true;
		break;
	case SDLK_o:

		if (e.keysym.mod & KMOD_SHIFT) {
			//camera.get_light().out();
		} else {
			if (active) {
				active->rotate(get_rotation(camera, glm::vec4(-1,0,0,1)));
			} else {
				std::cout << "Out: " << std::endl;
				camera.out();
			}
		}
		ret = true;
		break;
	}

	return ret;
}

int App2::
_display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for (std::vector<boost::shared_ptr<AppObject> >::iterator iter=object.begin(); iter!=object.end(); iter++) {
		(*iter)->draw(camera, light);
	}

	SDL_GL_SwapWindow(display.get_window());

	return 1;
}

int App2::
_tick()
{
	return physics.tick();
}

App2::~App2() {
	// TODO Auto-generated destructor stub
}

} /* namespace applications */
} /* namespace domahony */
