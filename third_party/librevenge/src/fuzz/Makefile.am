noinst_PROGRAMS = olefuzzer zipfuzzer

AM_CXXFLAGS = \
	-I$(top_srcdir)/inc \
	-I$(top_srcdir)/src/lib \
	$(DEBUG_CXXFLAGS)

commonfuzzer_ldadd = \
	$(top_builddir)/src/lib/librevenge-stream-@RVNG_MAJOR_VERSION@.@RVNG_MINOR_VERSION@.la \
	libcommonfuzzer.la \
	-lFuzzingEngine

noinst_LTLIBRARIES = libcommonfuzzer.la

libcommonfuzzer_la_SOURCES = \
	commonfuzzer.cpp \
	commonfuzzer.h

olefuzzer_LDADD = $(commonfuzzer_ldadd)

olefuzzer_SOURCES = \
	olefuzzer.cpp

zipfuzzer_LDADD = $(commonfuzzer_ldadd)

zipfuzzer_SOURCES = \
	zipfuzzer.cpp
