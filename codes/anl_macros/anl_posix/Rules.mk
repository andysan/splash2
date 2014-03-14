sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

CLEAN := $(CLEAN) \
	$(wildcard $(d)/*.o) \
	$(wildcard $(d)/*.a)

OBJS = $(addprefix $(d)/, \
	anl_posix.o \
	)

$(d)/libanl.a: $(OBJS)
	${AR} rc $@ $^

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
