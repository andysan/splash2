sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

dir:=$(d)/cholesky
include $(dir)/Rules.mk

dir:=$(d)/fft
include $(dir)/Rules.mk

dir:=$(d)/lu/contiguous_blocks
include $(dir)/Rules.mk

dir:=$(d)/lu/non_contiguous_blocks
include $(dir)/Rules.mk

dir:=$(d)/radix
include $(dir)/Rules.mk

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
