COLON:=:
ifeq ($(findstring $(COLON),$(lastword $(MAKEFILE_LIST))),)
BUILD_TOOLS_DIR:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
else
BUILD_TOOLS_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
endif

build_app:
	@$(MAKE) -f $(BUILD_TOOLS_DIR)App.mk build VERBOSE=$(VERBOSE)

clean_app:
	@$(MAKE) -f $(BUILD_TOOLS_DIR)App.mk clean VERBOSE=$(VERBOSE)

run_app:
	@$(MAKE) -f $(BUILD_TOOLS_DIR)App.mk run VERBOSE=$(VERBOSE)
