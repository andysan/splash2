sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o) \
	$(wildcard $(d)/*.a) \
	$(d)/g3states.h

CONF_LIBTIFF=\
	-DPACKBITS_SUPPORT \
	-DLZW_SUPPORT \
	-DCCITT_SUPPORT \
	-DTHUNDER_SUPPORT  \
	-DNEXT_SUPPORT  \
	\
	-DUSE_VARARGS=0 \
	-DUSE_PROTOTYPES=1 \
	-DHAVE_IEEEFP=1 \
	-DCOLORIMETRY_SUPPORT \
	-DJPEG_SUPPORT \
	-DYCBCR_SUPPORT \
	-DCMYK_SUPPORT \
	-DMMAP_SUPPORT

VOLREND_LIBTIFF_CFLAGS := $(VOLREND_LIBTIFF_CFLAGS) $(CONF_LIBTIFF)

OBJS = $(addprefix $(d)/, \
	tif_fax3.o \
	tif_fax4.o \
	tif_aux.o \
	tif_ccittrle.o \
	tif_close.o \
	tif_compat.o \
	tif_compress.o \
	tif_dir.o \
	tif_dirinfo.o \
	tif_dirread.o \
	tif_dirwrite.o \
	tif_dumpmode.o \
	tif_error.o \
	tif_getimage.o \
	tif_jpeg.o \
	tif_flush.o \
	tif_lzw.o \
	tif_next.o \
	tif_open.o \
	tif_packbits.o \
	tif_print.o \
	tif_read.o \
	tif_swab.o \
	tif_strip.o \
	tif_thunder.o \
	tif_tile.o \
	tif_version.o \
	tif_warning.o \
	tif_write.o \
	)

$(d)/%.o: $(d)/%.c  $(d)/g3states.h
	$(CC) $(CFLAGS) $(VOLREND_LIBTIFF_CFLAGS) -c -o $@ $<

$(d)/libtiff.a: $(OBJS)
	${AR} rc $@ $^

$(d)/mkg3states: $(d)/mkg3states.c
	$(CC) $(CFLAGS) $(VOLREND_LIBTIFF_CFLAGS) -o $@ $<

$(d)/g3states.h: $(d)/mkg3states
	$< -c > $@


d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
