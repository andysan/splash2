sp 		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

dir:=$(d)/barnes
include $(dir)/Rules.mk

dir:=$(d)/fmm
include $(dir)/Rules.mk

dir:=$(d)/ocean/contiguous_partitions
include $(dir)/Rules.mk

dir:=$(d)/ocean/non_contiguous_partitions
include $(dir)/Rules.mk

dir:=$(d)/radiosity
include $(dir)/Rules.mk

dir:=$(d)/raytrace
include $(dir)/Rules.mk

dir:=$(d)/volrend
include $(dir)/Rules.mk

dir:=$(d)/water-nsquared
include $(dir)/Rules.mk

dir:=$(d)/water-spatial
include $(dir)/Rules.mk

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))
