bin_PROGRAMS = prog
AM_CXXFLAGS = $(SDL_CFLAGS) $(GL_CFLAGS) $(BULLET_CFLAGS)

prog_SOURCES = main.cc App.cc OpenGL.cc Shader.cc BlenderProgram.cc VBO.cc NoLight_Vert.cc OpenGLState2.cc \
Camera.cc App3.cc Light.cc Basic_Frag.cc Basic_Vert.cc Simple_Vert.cc Simple_Frag.cc Plane.cc Program.cc Light2.cc \
Physics2.cc Display.cc ObjParser.cc World.cc die4.obj.cc die4.mtl.cc RandomDiceBody.cc plane.obj.cc \
WorldImpl.cc Body3.cc Body4.cc Die3.cc OpenGLState.cc circle.obj.cc Circle.cc Crosshair.cc GroundPlane.cc \
mat_Gloss_Red_Frag.cc mat_Gloss_Red_Vert.cc 
prog_LDADD = $(SDL_LDFLAGS) $(GL_LDFLAGS) $(BULLET_LIBS) -lCGAL -lmpfr -lgmp -L/usr/local/lib -lboost_thread -lboost_random


CLEANFILES = *_Vert.cc *_Geom.cc *_Frag.cc *.obj.cc *.shader.cc

%.cc : %.glsl
	bin2c -n $* $^ > $@

%.obj.cc : %.obj
	bin2c -n $* $^ > $@

%.mtl.cc : %.mtl
	bin2c -n $*_mtl $^ > $@
