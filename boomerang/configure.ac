dnl $Id: configure.ac,v 1.4 2008-03-29 23:04:28 thenihilist Exp $
dnl
dnl See the file "LICENSE.TERMS" for information on usage and
dnl redistribution of this file, and for a DISCLAIMER OF ALL
dnl WARRANTIES.
dnl
dnl File: configure.in
dnl autoconf uses this file to create the configure script, which generates
dnl the Makefiles and sets up various things.
dnl
dnl $Revision: 1.4 $
dnl
dnl 12 Apr 02 - Mike: Created
dnl 15 Oct 02 - Sebastian Apel: checks for libelf, libcppunit and AC_PREREQ(2.65) inserted
dnl 06 Mar 03 - Mike: Removed need for libelf
dnl 27 Jun 04 - Mike: Added XMLWF for eXpat XML parser
dnl 22 Aug 05 - Mike: Some improvements for OS X, and finding things like libexpat.a
dnl 12 Dec 05 - Mike: Apply Emmanuel Fleury's changes for auto "make remote"
dnl 16 Mar 08 - Markus Gothe: configure.ac for use with autotools.

AC_PREREQ(2.65)
AC_INIT([boomerang],[1.0],[nietzsche@lysator.liu.se])
AC_CONFIG_SRCDIR([LICENSE.TERMS])
AC_CONFIG_HEADER(include/config.h)
#AC_CONFIG_AUX_DIR([libltdl/config])
AC_CONFIG_MACRO_DIR([libltdl/m4])
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE

dnl check if the OPT variable is set
isset_OPT=${OPT+set}

AC_PROG_CXX
AC_PROG_CC
AC_PROG_CXXCPP
AC_PROG_CPP
AC_PROG_CC_C99
AC_PROG_CXX_C_O
AC_PROG_INSTALL
 
dnl Checks for programs.
LT_PREREQ([2.2.6])
LT_INIT([dlopen win32-dll])
LTDL_INIT([convenience recursive])

LT_INIT

AM_CONDITIONAL(CONVENIENCE_LTDL, test x"${enable_ltdl_convenience-no}" != xno)
AM_CONDITIONAL(INSTALL_LTDL, test x"${enable_ltdl_install-no}" != xno)

AC_C_BIGENDIAN
AC_C_CONST
AC_C_INLINE
AC_SUBST([LIBTOOL_DEPS])
LTDL_INIT([])

AM_CONDITIONAL(ENABLE_SHARED, [test x"${enable_shared}" = xyes])
AM_CONDITIONAL(ENABLE_STATIC, [test x"${enable_shared}" = xno])

if test "$GXX" = yes; then
	if test "$isset_OPT" == "set"; then
		CFLAGS="-g $OPT"
		CXXFLAGS="-g $OPT"
	fi
dnl	if test "$NOOPT" = yes; then
dnl		CFLAGS="-g -O0"
dnl		CXXFLAGS="-g -O0"
dnl	fi
	CFLAGS="$CFLAGS -Wall"
	CXXFLAGS="$CXXFLAGS -Wall"
fi

AC_PATH_PROG(MAKEDEPEND, makedepend)
AM_CONDITIONAL(MAKEDEPEND, test -n "$MAKEDEPEND")
if test -z "$MAKEDEPEND"; then
	AC_MSG_NOTICE()
	AC_MSG_NOTICE([You need the X11 makedepend utility to use automatic dependency generation (make depend)])
	AC_MSG_NOTICE()
fi

AC_SUBST(MAKEDEPEND)
AC_PATH_PROG(BISONPP, bison++)
AC_SUBST(BISONPP)
AC_PATH_PROG(FLEXPP, flex++)
AC_SUBST(FLEXPP)
AC_PATH_PROGS(M4, m4 gm4)
AM_CONDITIONAL(MAKEDEPEND, test -n "$M4")
AC_SUBST(M4)

dnl -------------------
dnl AC_MSG_CHECKING([if using GNU ld])
dnl HOST_GNU_LD=no
dnl if ${CC} -v 2>&1 </dev/null | egrep "gcc" 1>&5; then
dnl   HOST_GCC=yes
dnl   HOST_LD=`${CC} -print-prog-name=ld`
dnl else
dnl   HOST_LD=ld
dnl fi
dnl if ${HOST_LD} -v 2>&1 </dev/null | egrep '(GNU|with BFD)' 1>&5; then
dnl   HOST_GNU_LD=yes
dnl   AC_DEFINE(HOST_GNU_LD, 1, [Host uses GNU ld])
dnl fi
dnl AM_CONDITIONAL(HOST_GNU_LD, test "$HOST_GNU_LD" = "yes")
dnl AC_MSG_RESULT($HOST_GNU_LD)

dnl -------------------
AC_MSG_CHECKING([if host is Windows])
case $host in
 *-*-mingw32* | *-*-cygwin*)
   HOST_WINDOWS=yes
   ;;
 *)
   HOST_WINDOWS=no
   ;;
esac
AM_CONDITIONAL(HOST_WINDOWS, test "$HOST_WINDOWS" = "yes")
AC_MSG_RESULT($HOST_WINDOWS)

AC_MSG_CHECKING([if host is Cygwin])
case $host in
 *-*-cygwin*)
   HOST_CYGWIN=yes
   ;;
 *)
   HOST_CYGWIN=no
   ;;
esac
AM_CONDITIONAL(HOST_CYGWIN, test "$HOST_CYGWIN" = "yes")
AC_MSG_RESULT($HOST_CYGWIN)

AC_MSG_CHECKING([if host is OS X])
case $host in
 *-apple-darwin*)
   HOST_OSX=yes
   AC_DEFINE(HOST_OSX, 1, [Non zero if host machine is Mac OS X])
   ;;
 *)
   HOST_OSX=no
   AC_DEFINE(HOST_OSX, 0, [Non zero if host machine is Mac OS X])
   ;;
esac
AM_CONDITIONAL(HOST_OSX, test "$HOST_OSX" = "yes")
AC_MSG_RESULT($HOST_OSX)

dnl Checks for elf library (no longer needed)
dnl AC_CHECK_LIB(elf, elf_begin, , [AC_MSG_ERROR("library 'elf' not found")])

AC_CHECK_LIB(stdc++, main,, [AC_MSG_ERROR([library stdc++ is not found...])])

dnl Check for eXpat includes
dnl Want to check default-includes PLUS the Boomerang include/ directory, and some of the usual places it might already
dnl be installed
AC_CHECK_HEADER(expat.h,,
    [AC_CHECK_FILE(include/expat.h,,
		[AC_PATH_PROG(EXPAT_HDR_PATH, expat.h, :,
			[/usr/include:/usr/local/include:/opt/local/include:/usr/apache2/include:/opt/apache2/include:/sw/include])]
		if test "${EXPAT_HDR_PATH}" != :; then
			[AC_MSG_WARN(Found expat.h; linking to include/)]
			ln -s ${EXPAT_HDR_PATH} include
			dnl Sometimes, but not always, there is an expat_external.h as well
			[AC_PATH_PROG(EXPAT_HDR_PATH2, expat_external.h, :,
			[/usr/include:/usr/local/include:/opt/local/include:/usr/apache2/include:/opt/apache2/include:/sw/include])]
			if test "${EXPAT_HDR_PATH2}" != :; then
				[AC_MSG_WARN(Also found expat_eternal.h; linking to include/)]
				ln -s ${EXPAT_HDR_PATH2} include
			fi
        else
        	[AC_MSG_WARN()]
        	[AC_MSG_WARN(Header file expat.h not found: eXpat not installed...)]
        	[AC_MSG_WARN(or you need to copy expat.h to Boomerang's include/ dir)]
        	[AC_MSG_WARN()]
		fi
	)])

dnl Check for eXpat library itself
AC_CHECK_LIB(expat, XML_ExpatVersion, ,
    [AC_CHECK_FILE(lib/libexpat.a, ,
		[AC_PATH_PROG(EXPAT_PATH, libexpat.a, :,
			[/usr/lib:/usr/local/lib:/opt/local/lib:/usr/apache2/lib:/opt/apache2/lib:/sw/lib])]
		if test "${EXPAT_PATH}" != :; then
			[AC_MSG_WARN(Found libexpat.a; linking to lib/)]
			mkdir lib 2>/dev/null
			ln -s ${EXPAT_PATH} lib
        else
			[AC_MSG_WARN()]
			[AC_MSG_WARN(eXpat library not found: expat not installed... or you)]
			[AC_MSG_WARN(need to copy libexpat.a (etc) to Boomerang's lib/ dir)]
			[AC_MSG_WARN()]
		fi
	) ],)

dnl Check for gc (garbage collector) includes
dnl Want to check default-includes PLUS the Boomerang include/ directory, and some of the usual places it might already
dnl be installed
AC_CHECK_HEADERS(gc.h /usr/include/gc.h /usr/include/gc/gc.h /usr/local/include/gc.h /opt/local/include/gc.h /opt/local/include/gc/gc.h /sw/include/gc.h,
	CXXFLAGS="$CXXFLAGS -I`echo $ac_header | sed -e 's#/gc.h##g'`"
	CFLAGS="$CFLAGS -I`echo $ac_header | sed -e 's#/gc.h##g'`"
	break
	,
	,)
#AC_CHECK_HEADER(gc.h,,
#    [AC_CHECK_FILE(include/gc.h,,
#		[AC_PATH_TOOL(GC_HDR_PATH, gc.h, :, [/usr/include:/usr/include/gc:/usr/local/include:/opt/local/include:/opt/local/include/gc:/sw/include])]
#		if test "${GC_HDR_PATH}" != :; then
#			[AC_MSG_WARN(Found gc.h; linking to include/)]
#			ln -s ${GC_HDR_PATH} include
#			dnl Sometimes, not sure if always, there is a gc_config_macros.h as well
#			[AC_PATH_TOOL(GC_HDR_PATH2, gc_config_macros.h, :,
#			[/usr/include:/usr/include/gc:/usr/local/include:/opt/local/include:/opt/local/include/gc:/sw/include])]
#			if test "${GC_HDR_PATH2}" != :; then
#				[AC_MSG_WARN(Also found gc_config_macros.h; linking to include/)]
#				ln -s ${GC_HDR_PATH2} include
#			fi
#        else
#        	[AC_MSG_WARN()]
#        	[AC_MSG_WARN(Header file gc.h not found: Boehm garbage collector likely not installed...)]
#        	[AC_MSG_WARN(or you need to copy gc.h and gc_config_macros.h to Boomerang's include/ dir)]
#        	[AC_MSG_WARN()]
#		fi
#	)])

gcpaths="/usr/lib /usr/local/lib /opt/lib /opt/local/lib /sw/include/lib"
for x in $gcpaths; do
	save_libs="$LIBS"
	LIBS="$LIBS-L$x"
	unset ac_cv_lib_gc_GC_malloc
	AC_CHECK_LIB(gc, GC_malloc,
		LDFLAGS="$LDFLAGS $LIBS"
		break
		,
		,)
	LIBS="$save_LIBS"
done

dnl Check for gc library itself
#AC_CHECK_LIB(gc, GC_malloc, ,
#    [AC_CHECK_FILE(lib/libgc.a, ,
#		[AC_PATH_PROG(GC_PATH, libgc.a, :, [/usr/lib:/usr/local/lib:/opt/local/lib:/sw/lib])]
#		if test "${GC_PATH}" != :; then
#			[AC_MSG_WARN(Found libgc.a; linking to lib/)]
#			mkdir lib 2>/dev/null
#			ln -s ${GC_PATH} lib
#       else
#			[AC_MSG_WARN()]
#			[AC_MSG_WARN(Boehm garbage collector library not found: not installed...)]
#			[AC_MSG_WARN(or you need to copy libgc.a (etc) to Boomerang's lib/ dir)]
#			[AC_MSG_WARN()]
#		fi
#	) ],)

dnl Check for dlfcn.h (include for dlopen etc)
dnl Want to check default-includes PLUS the Boomerang include/ directory, and some of the usual places it might already
dnl be installed
AC_CHECK_HEADER(dlfcn.h,,
    [AC_CHECK_FILE(include/dlfcn.h,,
		[AC_PATH_PROG(DL_HDR_PATH, dlfcn.h, :, [/usr/include:/usr/local/include:/opt/local/include:/sw/include])]
		if test "${DL_HDR_PATH}" != :; then
			[AC_MSG_WARN(Found dlfcn.h; linking to include/)]
			ln -s ${DL_HDR_PATH} include
        else
        	[AC_MSG_WARN()]
        	[AC_MSG_WARN(Header file dlfcn.h not found; needed for dynamic library file access.)]
        	[AC_MSG_WARN(You probably need to copy dlfcn.h to Boomerang's include/ dir)]
        	[AC_MSG_WARN()]
		fi
	)])

dnl Check for libdl (dynamic linked library loading and calling) library
AC_CHECK_LIB(dl, dlopen, ,
    [AC_CHECK_FILE(lib/libdl.a, ,
		[AC_PATH_PROG(DL_PATH, libdl.a, :, [/usr/lib:/usr/local/lib:/opt/local/lib:/sw/lib])]
		if test "${DL_PATH}" != :; then
			[AC_MSG_WARN(Found libdl.a; linking to lib/)]
			mkdir lib 2>/dev/null
			ln -s ${DL_PATH} lib
        else
			[AC_MSG_WARN()]
        	[AC_MSG_WARN(dl (dynamically linked library loading and calling) library not found)]
        	[AC_MSG_WARN(you need to copy libdl.a (etc) to Boomerang's lib/ dir)]
			[AC_MSG_WARN()]
		fi
	) ],)

dnl Checks for optional cppunit library
AC_LANG_PUSH(C++)
CPPFLAGS="-I\$(top_srcdir)/include ${CPPFLAGS}"
AC_CHECK_HEADER(cppunit/TestSuite.h,,
    [AC_CHECK_FILE(include/cppunit/TestSuite.h,,
		[AC_PATH_PROG(CPPUNIT_HDR_PATH, cppunit/TestSuite.h, :,
			[/usr/include:/usr/local/include:/opt/local/include:/sw/include])]
		if test "${CPPUNIT_HDR_PATH}" != :; then
			[AC_MSG_WARN(Found cppunit include directory; linking to include/)]
			dnl Link the whole include directory
			dnl Note: I can't get AS_DIRNAME() to work...
			cpp_path=`dirname $CPPUNIT_HDR_PATH`
			ln -s ${cpp_path} include
        else
        	[AC_MSG_NOTICE()]
        	[AC_MSG_NOTICE(Header directories for cppunit not found; needed only for unit testing.)]
        	[AC_MSG_NOTICE()]
		fi
	)])

dnl Check for cppunut (C++ unit testing) library
AC_CHECK_LIB(cppunit, _ZN7CppUnit8TestCase3runEv, ,
    [AC_CHECK_FILE(lib/libcppunit.a, ,
		[AC_PATH_PROG(CPPUNIT_PATH, libcppunit.a, :, [/usr/lib:/usr/local/lib:/opt/local/lib:/sw/lib])]
		if test "${CPPUNIT_PATH}" != :; then
			[AC_MSG_WARN(Found libcppunit.a; linking to lib/)]
			mkdir lib 2>/dev/null
			ln -s ${CPPUNIT_PATH} lib
        else
			[AC_MSG_NOTICE()]
        	[AC_MSG_NOTICE(cppunit (C++ Unit Testing) library not found; needed only for testing)]
			[AC_MSG_NOTICE()]
		fi
	) ],)

AC_C_RESTRICT
AC_LANG_POP(C++)




dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(fcntl.h malloc.h sys/time.h unistd.h byteswap.h)
dnl AC_CHECK_HEADERS(libelf.h libelf/libelf.h, break)
dnl AC_CHECK_HEADERS(link.h sys/link.h, break)
dnl AC_CHECK_HEADERS(elf.h sys/elf_SPARC.h sys/auxv.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_BIGENDIAN

AC_CHECK_SIZEOF(char)
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(float)
AC_CHECK_SIZEOF(double)
AC_CHECK_SIZEOF(int *)
AC_CHECK_SIZEOF(long double)


dnl Checks for library functions.
AC_PROG_GCC_TRADITIONAL

dnl Now the options...
dnl AC_CHECK_FUNCS(mkdir rmdir)

dnl Actually we have "make remote" again now, so this is unused at present:
AC_ARG_ENABLE(remote, [  --enable-remote         don't try to regenerate source files],
              [ REMOTE=1 ], [ REMOTE=0 ])
AC_SUBST(REMOTE)

dnl Three paths for frontend/mltk.sh. No longer give a "value-if-not-found", so can avoid errors when not installed
AC_PATH_PROG(TKML, .run-sml, , [$PATH /usr/share/sml-nj/bin $HOME/install/smlnj/bin $HOME/sml-nj/bin])
dnl many more processors and platforms needed in this list
AC_SUBST(TKML)
AC_PATH_PROGS(HEAPPATH,
    [sml-toolkit.x86-linux sml-toolkit.sparc-solaris], ,
    [$HOME/install $PATH $HOME/install/mltk $HOME/sml-nj/install])
HEAP=\"@SMLload=$HEAPPATH\"
AC_SUBST(HEAP)

AC_PATH_PROG(UNGENERATE, ungenerate, , [$PATH:$HOME/install:$HOME/bin:/home/02/binary/u0.luna.tools/NJ/base:$HOME/sml-nj/install])

PREFIX=$srcdir
LIBDIR=$srcdir/lib

AC_SUBST(PREFIX)
AC_SUBST(LIBDIR)
AC_SUBST(HOST_GNU_LD)
AC_SUBST(HOST_WINDOWS)
AC_SUBST(HOST_OSX)
AC_SUBST(HOST_CYGWIN)


dnl only the makefile in the loader dir is currently used
AC_CONFIG_FILES(Makefile util/Makefile loader/Makefile db/Makefile frontend/Makefile transform/Makefile libltdl/Makefile)
AC_CONFIG_FILES(frontend/mltk.sh, [chmod +x frontend/mltk.sh])

AC_OUTPUT
