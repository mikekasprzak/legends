# - ------------------------------------------------------------------------ - #
__PROJECT_FILE__	:=	Config/.project
__SKU_FILE__		:=	Config/.sku
__TARGET_FILE__		:=	Config/.target
__REPOS_FILE__		:=	Config/.repos
# - ------------------------------------------------------------------------ - #
# NOTE: No colon here means that it will only overwrite if it did not exist. #
PROJECT_FILE		=	$(shell cat $(__PROJECT_FILE__))
SKU_FILE			=	$(shell cat $(__SKU_FILE__))
TARGET_FILE			=	$(shell cat $(__TARGET_FILE__))
REPOS_FILE			=	$(shell cat $(__REPOS_FILE__))
# - ------------------------------------------------------------------------ - #
TARGET_NAME			:=	$(basename $(notdir $(SKU_FILE)))-$(basename $(notdir $(TARGET_FILE)))
# - ------------------------------------------------------------------------ - #
ifdef NDEBUG
TARGET_NAME			:=	$(TARGET_NAME)-release
endif # NDEBUG #
# - ------------------------------------------------------------------------ - #
__SKU_CHECK__		:=	$(shell Tools/FileExists.sh $(__SKU_FILE__))
__TARGET_CHECK__	:=	$(shell Tools/FileExists.sh $(__TARGET_FILE__))
# - ------------------------------------------------------------------------ - #
ifneq ($(__TARGET_CHECK__),$(__TARGET_FILE__))
___default:
	@echo "*** ERROR: Makefile referenced in \".target\" not found! ***"
	@echo "Please run \"./setup.sh\" and specify a new target makefile"
else ifneq ($(__SKU_CHECK__),$(__SKU_FILE__))
___default:
	@echo "*** ERROR: Makefile referenced in \".sku\" not found! ***"
	@echo "Please run \"./sku.sh set\" and optionally pass a SKU name"
endif
# - ------------------------------------------------------------------------ - #
-include $(SKU_FILE)
-include $(TARGET_FILE)
# - ------------------------------------------------------------------------ - #
___default_missing:
	@echo "*** ERROR: Configuration Missing! ***"
	@echo "Please run \"./setup.sh\""
# - ------------------------------------------------------------------------ - #

# - ------------------------------------------------------------------------ - #
info:
	@echo '* TARGET_NAME * $(TARGET_NAME)'
	@echo '----------'
	@echo '* SRC_FOLDERS * $(SRC_FOLDERS)'
	@echo '* INCLUDE_FOLDERS * $(INCLUDE_FOLDERS)'
	@echo '* COPY_FILES * $(COPY_FILES)'
	@echo '* CFLAGS * $(CFLAGS)'
	@echo '* CPPFLAGS * $(CPPFLAGS)'
	@echo '* LDFLAGS * $(LDFLAGS)'
	@echo '----------'
	@echo '* INCLUDES * $(INCLUDES)'
	@echo '* LIBRARIES * $(LIBRARIES)'
	@echo '* DEFINES * $(DEFINES)'
# - ------------------------------------------------------------------------ - #
help:
	@echo "* The Following Options can be Combined *"
	@echo "TARGET_FILE=full_path_to/makefile_target   - Build a new target"
	@echo "SKU_FILE=Custom/sku_to_build   - Build a different SKU"
	@echo "NDEBUG=1   - Enable Release Mode (strip symbols, set NDEBUG)"
	@echo '----------'
	@echo "make           - Regular invocation"
	@echo "make run       - Run after building"
	@echo "make clean     - Clean Object files (next make rebuilds)"
	@echo "make cleanmain - Special Clean, just the Main.cpp.o file (quick)"
	@echo '----------'
	@echo "make upload  - (Where applicable) Upload binary to target device"
	@echo "./upload.sh  - (Where applicable) Upload content to target device"
	@echo "make package - (Where applicable) Package binary and data"
	@echo "make install - (Where applicable) Install package on target device"
# - ------------------------------------------------------------------------ - #
phony: info help ___default_missing ___default
# - ------------------------------------------------------------------------ - #
