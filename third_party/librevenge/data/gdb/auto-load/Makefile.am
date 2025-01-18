## Process this file with automake to produce Makefile.in

autoloaddir = $(GDBDATADIR)/auto-load/$(libdir)

autoloaders = \
	librevenge-$(RVNG_MAJOR_VERSION).$(RVNG_MINOR_VERSION)-gdb.py \
	librevenge-stream-$(RVNG_MAJOR_VERSION).$(RVNG_MINOR_VERSION)-gdb.py

nodist_autoload_DATA = $(autoloaders)

EXTRA_DIST = \
	librevenge.py.in \
	librevenge-stream.py.in

all-local: $(autoloaders)

%-$(RVNG_MAJOR_VERSION).$(RVNG_MINOR_VERSION)-gdb.py: $(srcdir)/%.py.in
	$(AM_V_GEN) $(SED) -e "s|\@datadir\@|$(datadir)|" $< > $@

clean-local:
	-rm -f *.py[co]

distclean-local:
	-rm -f *.py

## vim: set shiftwidth=4 tabstop=4 noexpandtab:
