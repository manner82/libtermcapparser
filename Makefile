# Makefile for putty puttyparser parser for ADP

include Makefile.config

libdir=$(prefix)/lib
incdir=$(prefix)/include

CFLAGS = -O2 -Wall -g -I. -I./ -I./charset/ -I./unix -I$(incdir) -fPIC -DNO_GSSAPI
CCFLAGS = $(CFLAGS)
INSTALL = install

TARGET=libtermcapparser.so
HEADER_DIR=putty
HEADERS=$(HEADER_DIR)/termcapparser.hh $(HEADER_DIR)/state.hh $(HEADER_DIR)/row.hh $(HEADER_DIR)/cell.hh $(HEADER_DIR)/palette.hh $(HEADER_DIR)/exception.hh
LDFLAGS+=-shared

CXX_OBJS = puttyparser.cc termcapparser.cc state.cc cell.cc row.cc palette.cc exception.cc

C_OBJS = charset/fromucs.c ldisc.c ldiscucs.c charset/localenc.c charset/mimeenc.c minibidi.c misc.c charset/sbcs.c charset/sbcsdat.c charset/slookup.c terminal.c time.c fake_timing.c charset/toucs.c tree234.c charset/utf8.c unix/uxmisc.c unix/uxucs.c wcwidth.c charset/xenc.c

OBJECTS = $(notdir $(CXX_OBJS:.cc=.o) $(C_OBJS:.c=.o))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -fPIC $(LDFLAGS) -o $@ $(OBJECTS)

$(CXX_OBJS:.cc=.o):
	$(CXX) $(COMPAT) $(CCFLAGS) -c $<

$(notdir $(C_OBJS:.c=.o)):
	$(CC) $(COMPAT) $(CFLAGS) $(XFLAGS) -c $<


install: $(TARGET)
	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(incdir)/$(HEADER_DIR)
	$(INSTALL) -m 755 $(TARGET) $(DESTDIR)$(libdir)/$(TARGET)
	$(INSTALL) -m 644 $(HEADERS) -t $(DESTDIR)$(incdir)/$(HEADER_DIR)

uninstall:
	rm -f $(DESTDIR)$(libdir)/$(TARGET)
	rm -f $(DESTDIR)$(incdir)/$(HEADERS)
	rmdir $(DESTDIR)$(incdir)/$(HEADER_DIR) 2>/dev/null || true
	rmdir $(DESTDIR)$(libdir) 2>/dev/null || true

install-strip:
	$(MAKE) install INSTALL="$(INSTALL) -s"

clean:
	rm -f $(OBJECTS) $(TARGET)
	$(MAKE) -C tests clean

distclean: clean
	rm -f Makefile.*

check: install
	$(MAKE) -C tests

NODEP_TARGETS =

dep: $(C_OBJS) $(CXX_OBJS)
	$(CC) -MM $(COMPAT) $(CFLAGS) $(XFLAGS) $^ > Makefile.dep
ifeq ($(filter $(MAKECMDGOALS),$(NODEP_TARGETS)),)
-include Makefile.dep
endif
