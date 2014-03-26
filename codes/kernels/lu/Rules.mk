sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

EXTRA := $(EXTRA) \
	$(d)/README.lu

dir:=$(d)/contiguous_blocks
include $(dir)/Rules.mk

dir:=$(d)/non_contiguous_blocks
include $(dir)/Rules.mk

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
