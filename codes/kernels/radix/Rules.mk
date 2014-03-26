sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

ANL_CLEAN := $(ANL_CLEAN) \
	$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o)


ALL := $(ALL) \
	$(d)/radix

EXTRA := $(EXTRA) \
	$(d)/README.radix

OBJS = $(addprefix $(d)/, \
	radix.o)

HEADERS = $(patsubst %.H, %.h, $(wildcard $(d)/*.H))

$(d)/%.o: $(d)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(RADIX_CFLAGS) -c -o $@ $<

$(d)/radix: $(OBJS) $(ANL_OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
