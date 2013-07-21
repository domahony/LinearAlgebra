bin_PROGRAMS = prog
AM_CXXFLAGS = $(SDL_CFLAGS) $(GL_CFLAGS)

prog_SOURCES = main.cc App.cc OpenGL.cc Shader.cc Program.cc Triangles.cc VBO.cc \
Camera.cc App1.cc Drawable.cc Axis.cc fragment.shader.cc vertex.shader.cc Cube.cc Sphere.cc \
NormalCalculator.cc IcoSphere.cc
prog_LDADD = $(SDL_LDFLAGS) $(GL_LDFLAGS)

CLEANFILES = *.shader.cc

%.shader.cc : %.glsl
	bin2c -n $* $^ > $@
