AC_INIT(src/main.cc)

PACKAGE=prog
VERSION=0.1.0

AM_INIT_AUTOMAKE(${PACKAGE}, ${VERSION})

AC_PROG_CC
AC_PROG_CXX
AC_CHECK_PROG([sdl_config], [sdl-config], [yes])

if test "x${sdl_config}" = x 
then 
	echo "You must have SDL"
	(exit 1); exit 1;
else
	AC_SUBST(SDL_CFLAGS, `sdl-config --cflags`)
	AC_SUBST(SDL_LDFLAGS, `sdl-config --libs`)
fi

AC_OUTPUT(Makefile src/Makefile)
