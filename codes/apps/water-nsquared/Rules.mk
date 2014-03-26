sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

ANL_CLEAN := $(ANL_CLEAN) \
	$(wildcard $(d)/*.c) $(wildcard $(d)/*.h)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o)


ALL := $(ALL) \
	$(d)/water-nsquared

INPUT := $(INPUT) \
	$(d)/input

EXTRA := $(EXTRA) \
	$(d)/README.water-nsquared

OBJS = $(addprefix $(d)/, \
	water.o mdmain.o syscons.o kineti.o bndry.o cnstnt.o initia.o \
	interf.o intraf.o cshift.o poteng.o predcor.o\
	)

HEADERS = $(patsubst %.H, %.h, $(wildcard $(d)/*.H))

$(d)/%.o: $(d)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(WATER_NSQUARED_CFLAGS) -c -o $@ $<

$(d)/water-nsquared: $(OBJS) $(ANL_OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
