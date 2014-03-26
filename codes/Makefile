
# Installation prefix
PREFIX?=install

CC=gcc
LD=gcc
M4=m4
INSTALL=install

CFLAGS?=-O2 -pthread -Wno-deprecated-declarations -Wno-unused-result
LDFLAGS?=-pthread
LIBS=-lm

ANL_CFLAGS=-I$(abspath anl_macros)
CFLAGS:=$(CFLAGS) $(ANL_CFLAGS)

ANL_MACROS:=$(abspath anl_macros/c.m4.posix)
ANL_OBJS=anl_macros/anl_posix/libanl.a

# Benchmark-specfic configuration
LU_CFLAGS?=-DPAGE_SIZE=4096

# ANL generated files
ANL_CLEAN=

# Generated files
CLEAN=

# Binaries
ALL=

all: autoall

dir:=apps
include $(dir)/Rules.mk

dir:=kernels
include $(dir)/Rules.mk

dir:=anl_macros/anl_posix
include $(dir)/Rules.mk

autoall: $(ALL)

# Disable any C->o rules
%.o: %.C

%.c: %.C
	cd $(dir $<) && $(M4) $(ANL_MACROS) $(notdir $<) > $(notdir $@)

%.h: %.H
	cd $(dir $<) && $(M4) $(ANL_MACROS) $(notdir $<) > $(notdir $@)

install_extra: $(EXTRA)
	@echo "Installing extras..." 
	install -d $(addprefix $(PREFIX)/, $(dir $^))
	for F in $^; do \
		$(INSTALL) -m 0644 $$F $(PREFIX)/$$F; \
	done

install_data: $(INPUT)
	@echo "Installing input files..." 
	install -d $(addprefix $(PREFIX)/, $(dir $^))
	for F in $^; do \
		$(INSTALL) -m 0644 $$F $(PREFIX)/$$F; \
	done

install_bin: $(ALL)
	@echo "Installing binaries..." 
	install -d $(addprefix $(PREFIX)/, $(dir $^))
	for F in $^; do \
		$(INSTALL) -m 0755 $$F $(PREFIX)/$$F; \
	done

install: install_bin install_data install_extra

barnes: apps/barnes/barnes
fmm: apps/fmm/fmm
ocean: apps/ocean/contiguous_partitions/ocean \
	apps/ocean/non_contiguous_partitions/ocean
radiosity: apps/radiosity/radiosity
raytrace: apps/raytrace/raytrace
volrend: apps/volrend/volrend
water: apps/water-nsquared/water-nsquared \
	apps/water-spatial/water-spatial

apps: barnes fmm ocean radiosity raytrace volrend water

cholesky: kernels/cholesky/cholesky
fft: kernels/fft/fft
lu: kernels/lu/contiguous_blocks/lu kernels/lu/non_contiguous_blocks/lu
radix: kernels/radix/radix

kernels: cholesky fft lu radix

anlclean:
	$(RM) $(ANL_CLEAN)

clean:
	$(RM) $(CLEAN)

realclean: clean anlclean

.PHONY: all autoall anlclean clean realclean \
	install install_bin install_extra install_data \
	apps kernels \
	barnes fmm ocean radiosity raytrace volrend water \
	cholesky fft lu radix

.PRECIOUS: %.h %.c
