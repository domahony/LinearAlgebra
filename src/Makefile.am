bin_PROGRAMS = prog
AM_CXXFLAGS = $(SDL_CFLAGS) $(GL_CFLAGS) $(BULLET_CFLAGS)

prog_SOURCES = main.cc App.cc OpenGL.cc Shader.cc Program.cc VBO.cc \
Camera.cc App3.cc NormalCalculator.cc Light.cc redcube.obj.cc Basic_Frag.cc Basic_Vert.cc \
die2.obj.cc pyramid.obj.cc fox3.obj.cc Physics.cc Display.cc \
BodyCreator.cc ObjParser.cc AppObject.cc IcoSphereData.cc groundplane.obj.cc \
NewHead8.obj.cc die4.obj.cc die4.mtl.cc SphereListCreator.cc ConvexHull.cc World.cc \
WorldImpl.cc Die2.cc Body3.cc Body4.cc Die3.cc OpenGLState.cc
prog_LDADD = $(SDL_LDFLAGS) $(GL_LDFLAGS) $(BULLET_LIBS) -lCGAL -lmpfr -lgmp -L/usr/local/lib -lboost_thread


CLEANFILES = *_Vert.cc *_Geom.cc *_Frag.cc *.obj.cc *.shader.cc

%.cc : %.glsl
	bin2c -n $* $^ > $@

%.obj.cc : %.obj
	bin2c -n $* $^ > $@

%.mtl.cc : %.mtl
	bin2c -n $*_mtl $^ > $@
