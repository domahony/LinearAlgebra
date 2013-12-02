bin_PROGRAMS = prog
AM_CXXFLAGS = $(SDL_CFLAGS) $(GL_CFLAGS) $(BULLET_CFLAGS)

prog_SOURCES = main.cc App.cc OpenGL.cc Shader.cc Program.cc VBO.cc \
Camera.cc App2.cc fragment.shader.cc vertex.shader.cc \
NormalCalculator.cc Light.cc redcube.obj.cc \
die2.obj.cc pyramid.obj.cc fox3.obj.cc Physics.cc Display.cc \
BodyCreator.cc ObjParser.cc AppObject.cc IcoSphereData.cc groundplane.obj.cc \
NewHead8.obj.cc die4.obj.cc die4.mtl.cc
prog_LDADD = $(SDL_LDFLAGS) $(GL_LDFLAGS) $(BULLET_LIBS) -lCGAL

CLEANFILES = *.shader.cc
CLEANFILES = *.obj.cc

%.shader.cc : %.glsl
	bin2c -n $* $^ > $@

%.obj.cc : %.obj
	bin2c -n $* $^ > $@

%.mtl.cc : %.mtl
	bin2c -n $*_mtl $^ > $@
