sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

dir:=$(d)/libtiff
include $(dir)/Rules.mk

ANL_CLEAN := $(ANL_CLEAN) \
	$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o)


ALL := $(ALL) \
	$(d)/volrend

INPUT := $(INPUT) \
	$(wildcard $(d)/inputs/*)

EXTRA := $(EXTRA) \
	$(d)/README.volrend

OBJS = $(addprefix $(d)/, \
	main.o file.o option.o map.o normal.o opacity.o octree.o view.o \
	render.o adaptive.o raytrace.o)

HEADERS = $(patsubst %.H, %.h, $(wildcard $(d)/*.H))

VOLREND_CFLAGS:=$(VOLREND_CFLAGS) -I$(d)/libtiff

$(d)/%.o: $(d)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(VOLREND_CFLAGS) -c -o $@ $<

$(d)/volrend: $(OBJS) $(d)/libtiff/libtiff.a $(ANL_OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
