linux:
	$(MAKE) $(MFLAGS) linux-dep
	$(MAKE) $(MFLAGS) linux-all
	$(MAKE) $(MFLAGS) linux-install



linux-%:
	$(MAKE) $(MFLAGS) -f Makefile.linux $*

help:
	@cat README.md

.PHONY: linux win32 help
