bin_PROGRAMS = prog
AM_CXXFLAGS = $(SDL_CFLAGS) $(GL_CFLAGS)

prog_SOURCES = main.cc App.cc OpenGL.cc Shader.cc Program.cc VBO.cc \
Camera.cc App1.cc Drawable.cc fragment.shader.cc vertex.shader.cc \
NormalCalculator.cc IcoSphere.cc Light.cc Cube.cc redcube.obj.cc \
ObjShape.cc
prog_LDADD = $(SDL_LDFLAGS) $(GL_LDFLAGS)

CLEANFILES = *.shader.cc
CLEANFILES = *.obj.cc

%.shader.cc : %.glsl
	bin2c -n $* $^ > $@

%.obj.cc : %.obj
	bin2c -n $* $^ > $@
