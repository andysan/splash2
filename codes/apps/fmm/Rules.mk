sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

ANL_CLEAN := $(ANL_CLEAN) \
	$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o)


ALL := $(ALL) \
	$(d)/fmm

INPUT := $(INPUT) \
	$(wildcard $(d)/inputs/*)

EXTRA := $(EXTRA) \
	$(d)/README.fmm

OBJS = $(addprefix $(d)/, \
	defs.o memory.o particle.o box.o partition_grid.o \
	cost_zones.o construct_grid.o interactions.o fmm.o)

HEADERS = $(patsubst %.H, %.h, $(wildcard $(d)/*.H))

$(d)/%.o: $(d)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(FMM_CFLAGS) -c -o $@ $<

$(d)/fmm: $(OBJS) $(ANL_OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
