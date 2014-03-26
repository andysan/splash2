sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

ANL_CLEAN := $(ANL_CLEAN) \
	$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o)


ALL := $(ALL) \
	$(d)/fft

EXTRA := $(EXTRA) \
	$(d)/README.fft

OBJS = $(addprefix $(d)/, \
	fft.o)

HEADERS = $(patsubst %.H, %.h, $(wildcard $(d)/*.H))

$(d)/%.o: $(d)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(FFT_CFLAGS) -c -o $@ $<

$(d)/fft: $(OBJS) $(ANL_OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
