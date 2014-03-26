sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

EXTRA := $(EXTRA) \
	$(d)/README.ocean

dir:=$(d)/contiguous_partitions
include $(dir)/Rules.mk

dir:=$(d)/non_contiguous_partitions
include $(dir)/Rules.mk

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
