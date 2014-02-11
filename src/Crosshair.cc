/*
 * Crosshair.cc
 *
 *  Created on: 2014-02-09
 *      Author: domahony
 */

#include "Crosshair.h"
#include "Shader.h"
#include "VBO.h"

#ifdef __cplusplus
extern "C" {
#endif

extern char Simple_Frag[];
extern char Simple_Vert[];

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

Crosshair::Crosshair()
: vao(init_vao()), vbo(),
			gl_front_mode(GL_LINE),
			gl_back_mode(GL_LINE)
{

	Shader vshader2(GL_VERTEX_SHADER, Simple_Vert);
	program.attach_shader(vshader2);

	Shader fshader2(GL_FRAGMENT_SHADER, Simple_Frag);
	program.attach_shader(fshader2);

	program.link();

	//glUseProgram(program);

}

Crosshair::~Crosshair() {
	// TODO Auto-generated destructor stub
}

void Crosshair::
set_data(const std::vector<float>& data)
{
	glBindVertexArray(vao);

	vbo.bind();
	vbo.buffer_data(data);

	vbo.bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	vbo.unbind();
	glBindVertexArray(0);
}
void Crosshair::
render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	std::cout << "Render Die Impl " << std::endl;

	glPolygonMode(GL_FRONT, gl_front_mode);
	glPolygonMode(GL_BACK, gl_back_mode);
	//glLineWidth(line_width);

	glDrawArrays(GL_LINES, 0, vbo.size()/3);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

} /* namespace domahony */
