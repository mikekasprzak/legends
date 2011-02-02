# - ------------------------------------------------------------------------ - #
__TARGET_FILE__		:=	Config/.target
# - ------------------------------------------------------------------------ - #
-include $(__TARGET_FILE__)
# - ------------------------------------------------------------------------ - #
__TARGET_CHECK__	:=	$(shell Tools/FileExists.sh $(__TARGET_FILE__))
# - ------------------------------------------------------------------------ - #
ifeq ($(__TARGET_CHECK__),$(__TARGET_FILE__))
___default:
	@echo "*** ERROR: Makefile referenced in \".target\" not found! ***"
	@echo "Please run \"./setup.sh\" and specify a new makefile"
else
___default:
	@echo "*** ERROR: No \".target\" file found! ***"
	@echo "Please run \"./setup.sh\""
endif
# - ------------------------------------------------------------------------ - #
	