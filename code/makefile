# - ------------------------------------------------------------------------ - #
__SKU_FILE__		:=	Config/.sku
__TARGET_FILE__		:=	Config/.target
# - ------------------------------------------------------------------------ - #
-include $(shell cat $(__SKU_FILE__))
-include $(__TARGET_FILE__)
# - ------------------------------------------------------------------------ - #
__SKU_CHECK__		:=	$(shell Tools/FileExists.sh $(__SKU_FILE__))
__TARGET_CHECK__	:=	$(shell Tools/FileExists.sh $(__TARGET_FILE__))
# - ------------------------------------------------------------------------ - #
ifeq ($(__TARGET_CHECK__),$(__TARGET_FILE__))
___default:
	@echo "*** ERROR: Makefile referenced in \".target\" not found! ***"
	@echo "Please run \"./setup.sh\" and specify a new makefile"
else ifeq ($(__SKU_CHECK__),$(__SKU_FILE__))
___default:
	@echo "*** ERROR: Makefile referenced in \".sku\" not found! ***"
	@echo "Please run \"./sku.sh co\""
else
___default:
	@echo "*** ERROR: Either no \".target\" or \".sku\" file found! ***"
	@echo "Please run \"./setup.sh\""
endif
# - ------------------------------------------------------------------------ - #
