sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

ANL_CLEAN := $(ANL_CLEAN) \
	$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o) \
	$(wildcard $(d)/glibps/*.o) \
	$(wildcard $(d)/glibps/*.a) \
	$(wildcard $(d)/glibdumb/*.o) \
	$(wildcard $(d)/glibdumb/*.a)

ALL := $(ALL) \
	$(d)/radiosity

OBJS = $(addprefix $(d)/, \
	rad_main.o patchman.o elemman.o taskman.o modelman.o smallobj.o\
	display.o visible.o rad_tools.o room_model.o)

HEADERS = $(patsubst %.H, %.h, $(wildcard $(d)/*.H))

RADIOSITY_CFLAGS := $(RADIOSITY_CFLAGS) -I$(d)/glibps -I$(d)/glibdumb

$(d)/radiosity.h: $(d)/radiosity.H $(d)/patch.h $(d)/model.h $(d)/parallel.h $(d)/task.h

$(d)/rad_main.c: $(d)/rad_main.C $(HEADERS)
$(d)/patchman.c: $(d)/patchman.C $(HEADERS)
$(d)/elemman.c: $(d)/elemman.C $(HEADERS)
$(d)/taskman.c: $(d)/taskman.C $(HEADERS)
$(d)/modelman.c: $(d)/modelman.C $(HEADERS)
$(d)/smallobj.c: $(d)/smallobj.C $(HEADERS)
$(d)/display.c: $(d)/display.C $(HEADERS)
$(d)/visible.c: $(d)/visible.C $(HEADERS)
$(d)/rad_tools.c: $(d)/rad_tools.C $(HEADERS)
$(d)/room_model.c: $(d)/room_model.C $(HEADERS)

$(d)/%.o: $(d)/%.c
	$(CC) $(CFLAGS) $(RADIOSITY_CFLAGS) -c -o $@ $<

$(d)/glibps/libglibps.a: $(d)/glibps/glibps.o
	${AR} rc $@ $^

$(d)/glibdumb/libglib.a: $(d)/glibdumb/glib.o
	${AR} rc $@ $^

$(d)/radiosity: $(OBJS) $(d)/glibdumb/libglib.a $(d)/glibps/libglibps.a \
	$(ANL_OBJS)

	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
