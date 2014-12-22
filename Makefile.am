

ACLOCAL_AMFLAGS = -I m4

DISTCLEANFILES = @DOLT_CLEANFILES@

EXTRA_DIST =

# what flags you want to pass to the C compiler & linker
CFLAGS = --pedantic -Wall -std=c99 -O2
LDFLAGS =

################################################################################
#  libcsv library                                                              #
################################################################################

csvincludedir = $(includedir)/
csvinclude_HEADERS = \
	src/csv.h 

lib_LTLIBRARIES = libcsv.la

libcsv_la_SOURCES = \
	src/csv.c


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libcsv.pc

libcsv_la_LDFLAGS = -no-undefined -version-info @CSV_LIBTOOL_VERSION@
#libcsv_la_CFLAGS = -DNN_EXPORTS


################################################################################
#  documentation                                                               #
################################################################################

#  Source files.


################################################################################
#  performance tests                                                           #
################################################################################



################################################################################
#  automated tests                                                             #
################################################################################

TESTS_INTERNAL = \
	tests/internal

TESTS_FORMATS = \
	tests/formats

EXTRA_DIST += tests/testutil.h

check_PROGRAMS = \
    $(TESTS_INTERNAL) \
    $(TESTS_FORMATS) 

TESTS = $(check_PROGRAMS)


################################################################################
#  tools                                                                       #
################################################################################

bin_PROGRAMS =




