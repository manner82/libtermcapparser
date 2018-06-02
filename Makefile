linux:
	$(MAKE) $(MFLAGS) linux-dep
	$(MAKE) $(MFLAGS) linux-install

win32:
	$(MAKE) $(MFLAGS) win32-dep
	$(MAKE) $(MFLAGS) win32-install

win32-%:
	$(MAKE) $(MFLAGS) -f Makefile.win32 $*

linux-%:
	$(MAKE) $(MFLAGS) -f Makefile.linux $*

darwin-%:
	$(MAKE) $(MFLAGS) -f Makefile.darwin $*

clean: linux-clean win32-clean

distclean: linux-distclean win32-distclean

help:
	@cat README.md

.PHONY: linux win32 help
