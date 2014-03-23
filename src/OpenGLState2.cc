/*
 * OpenGLState.cc
 *
 *  Created on: 2014-01-30
 *      Author: domahony
 */

#include "OpenGLState2.h"
#include "Shader.h"
#include "VBO.h"

#ifdef __cplusplus
extern "C" {
#endif

extern char Basic_Frag[];
extern char NoLight_Vert[];

#ifdef __cplusplus
}
#endif

namespace domahony {

static GLuint
init_vao()
{
	GLuint ret;
	glGenVertexArrays(1, &ret);

	return ret;
}

using domahony::opengl::Shader;
using domahony::opengl::Program;

OpenGLState2::
OpenGLState2() : vao(init_vao()), vbo(),
			gl_front_mode(GL_FILL),
			gl_back_mode(GL_LINE)
{

	Shader vshader2(GL_VERTEX_SHADER, NoLight_Vert);
	program.attach_shader(vshader2);

	Shader fshader2(GL_FRAGMENT_SHADER, Basic_Frag);
	program.attach_shader(fshader2);

	program.link();

	//glUseProgram(program);

}

OpenGLState2::
~OpenGLState2() {
	// TODO Auto-generated destructor stub
}

void OpenGLState2::
set_data(const std::vector<float>& data)
{
	glBindVertexArray(vao);

	vbo.bind();
	vbo.buffer_data(data);

	vbo.bind();
	glVertexAttribPointer(+ 0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);
	glVertexAttribPointer(+ 1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glVertexAttribPointer(+ 2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));

	vbo.unbind();
	glBindVertexArray(0);
}

void OpenGLState2::
render() const {
	glFrontFace(GL_CW);
	render2();
	glFrontFace(GL_CCW);
	render2();
}

void OpenGLState2::
render2() const {

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	std::cout << "Render Wall Impl " << std::endl;

	glPolygonMode(GL_FRONT, gl_front_mode);
	glPolygonMode(GL_BACK, gl_back_mode);
	//glLineWidth(line_width);

	//glDisable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	glDrawArrays(GL_TRIANGLES, 0, vbo.size()/9);
	//glFrontFace(GL_CCW);
	//glDrawArrays(GL_TRIANGLES, 0, vbo.size()/9);
	//glEnable(GL_CULL_FACE);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

} /* namespace domahony */
