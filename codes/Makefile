
CC=gcc
LD=gcc
M4=m4

CFLAGS=-O2 -pthread -Wno-deprecated-declarations -Wno-unused-result
LDFLAGS=-pthread
LIBS=-lm

ANL_MACROS:=$(abspath null_macros/c.m4.null)

all: autoall

LU_CFLAGS=-DPAGE_SIZE=4096

# ANL generated files
ANL_CLEAN=

# Generated files
CLEAN=

# Binaries
ALL=

dir:=apps
include $(dir)/Rules.mk

dir:=kernels
include $(dir)/Rules.mk

autoall: $(ALL)

# Disable any C->o rules
%.o: %.C

%.c: %.C
	cd $(dir $<) && $(M4) $(ANL_MACROS) $(notdir $<) > $(notdir $@)

%.h: %.H
	cd $(dir $<) && $(M4) $(ANL_MACROS) $(notdir $<) > $(notdir $@)

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
	apps kernels \
	barnes fmm ocean radiosity raytrace volrend water \
	cholesky fft lu radix

.PRECIOUS: %.h %.c
