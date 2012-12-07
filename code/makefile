# - ------------------------------------------------------------------------ - #
BUILD_MAKEFILE		:=	Tools/makefile
# - ------------------------------------------------------------------------ - #
__PROJECT_FILE__	:=	Config/.project
__SKU_ALL_FILE__	:=	Config/.sku_all
# - ------------------------------------------------------------------------ - #
PROJECT_FILE		=	$(shell cat $(__PROJECT_FILE__))
SKU_ALL_FILE		=	$(shell cat $(__SKU_ALL_FILE__))
# - ------------------------------------------------------------------------ - #
ifdef NUMBER_OF_PROCESSORS
NUM_PROCESSORS		:=	$(NUMBER_OF_PROCESSORS)
else # NUMBER_OF_PROCESSORS #
NUM_PROCESSORS		:=	$(shell nproc)
endif # NUMBER_OF_PROCESSORS #
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
.phony: default run clean cleanmain info all
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
default:
	$(MAKE) -f $(BUILD_MAKEFILE) -j $(NUM_PROCESSORS)
run clean cleanmain info upload package install:
	$(MAKE) -f $(BUILD_MAKEFILE) -j $(NUM_PROCESSORS) $@
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
all: $(addprefix obj/,$(SKU_ALL_FILE))
# - ------------------------------------------------------------------------ - #
obj/%:
	$(MAKE) -f $(BUILD_MAKEFILE) -j $(NUM_PROCESSORS) SKU_FILE=SKU/$(PROJECT_FILE)/$*
# - ------------------------------------------------------------------------ - #
