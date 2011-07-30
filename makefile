# - ------------------------------------------------------------------------ - #
__PROJECT_FILE__	:=	Config/.project
__SKU_FILE__		:=	Config/.sku
__TARGET_FILE__		:=	Config/.target
__REPOS_FILE__		:=	Config/.repos
# - ------------------------------------------------------------------------ - #
PROJECT_FILE		:=	$(shell cat $(__PROJECT_FILE__))
SKU_FILE			:=	$(shell cat $(__SKU_FILE__))
TARGET_FILE			:=	$(shell cat $(__TARGET_FILE__))
REPOS_FILE			:=	$(shell cat $(__REPOS_FILE__))
# - ------------------------------------------------------------------------ - #
TARGET_NAME			:=	$(PROJECT_FILE)-$(SKU_FILE)-$(basename $(notdir $(TARGET_FILE)))
# - ------------------------------------------------------------------------ - #
__SKU_CHECK__		:=	$(shell Tools/FileExists.sh $(__SKU_FILE__))
__TARGET_CHECK__	:=	$(shell Tools/FileExists.sh $(__TARGET_FILE__))
# - ------------------------------------------------------------------------ - #
ifneq ($(__TARGET_CHECK__),$(__TARGET_FILE__))
___default:
	@echo "*** ERROR: Makefile referenced in \".target\" not found! ***"
	@echo "Please run \"./setup.sh\" and specify a new makefile"
else ifneq ($(__SKU_CHECK__),$(__SKU_FILE__))
___default:
	@echo "*** ERROR: Makefile referenced in \".sku\" not found! ***"
	@echo "Please run \"./sku.sh co\""
endif
# - ------------------------------------------------------------------------ - #
-include $(SKU_FILE)
-include $(TARGET_FILE)
# - ------------------------------------------------------------------------ - #
___default_missing:
	@echo "*** ERROR: Configuration Missing! ***"
	@echo "Please run \"./setup.sh\""
# - ------------------------------------------------------------------------ - #
