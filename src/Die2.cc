/*
 * Die2.cc
 *
 *  Created on: 2014-01-29
 *      Author: domahony
 */

#include "Die2.h"
#include "OpenGL.h"
#include "ObjParser.h"
#include "Program.h"
#include "Shader.h"
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

extern const char die4[];
extern const char die4_mtl[];
extern char Basic_Frag[];
extern char Basic_Vert[];

#ifdef __cplusplus
}
#endif

using domahony::opengl::Shader;
using domahony::opengl::Program;

namespace domahony {

void Die2::
init() {
	std::vector<GLfloat> data;
	domahony::opengl::ObjParser::get_data(die4, die4_mtl, data);

	Shader vshader2(GL_VERTEX_SHADER, Basic_Vert);
	program.attach_shader(vshader2);

	Shader fshader2(GL_FRAGMENT_SHADER, Basic_Frag);
	program.attach_shader(fshader2);

	program.link();
}

void Die2::
render() const
{
	/*
	program.set_eye_location();
	program.set_global_light();
	program.set_mvp_matrix();
	program.set_normal_matrix();
	program.set_view_matrix();
	*/

	glUseProgram(program);

	//glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	std::cout << "Render Die Impl " << std::endl;

	/*
	glPolygonMode(GL_FRONT, gl_front_mode);
	glPolygonMode(GL_BACK, gl_back_mode);
	glLineWidth(line_width);
	glDrawArrays(GL_TRIANGLES, 0, vbo.size()/9);
	*/

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

} /* namespace domahony */
