AC_INIT(src/main.cc)

PACKAGE=prog
VERSION=0.1.0

AM_INIT_AUTOMAKE(${PACKAGE}, ${VERSION})

AC_PROG_CC
AC_PROG_CXX

AC_CHECK_PROG([sdl_config], [sdl2-config], [yes])

if test "x${sdl_config}" = x
then 
	echo "You must have SDL ${sdl2_config}"
	(exit 1); exit 1;
else
	AC_SUBST(SDL_CFLAGS, `sdl2-config --cflags`)
	AC_SUBST(SDL_LDFLAGS, `sdl2-config --libs`)
fi

AC_SUBST(GL_CFLAGS, "-I/usr/include/GL")
AC_SUBST(GL_LDFLAGS, "-lGL")

PKG_CHECK_MODULES([BULLET], [bullet > 0.26])

AC_OUTPUT(Makefile src/Makefile)