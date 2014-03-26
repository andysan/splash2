sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

ANL_CLEAN := $(ANL_CLEAN) \
	$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o)


ALL := $(ALL) \
	$(d)/cholesky

INPUT := $(INPUT) \
	$(wildcard $(d)/inputs/*)

EXTRA := $(EXTRA) \
	$(d)/README.cholesky

OBJS = $(addprefix $(d)/, \
	amal.o assign.o bfac.o bksolve.o block2.o fo.o mf.o numLL.o \
	parts.o seg.o solve.o tree.o util.o malloc.o \
	)

HEADERS = $(patsubst %.H, %.h, $(wildcard $(d)/*.H))

$(d)/%.o: $(d)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(CHOLESKY_CFLAGS) -c -o $@ $<

$(d)/cholesky: $(OBJS) $(ANL_OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
