COLON:=:
ifeq ($(findstring $(COLON),$(lastword $(MAKEFILE_LIST))),)
BUILD_TOOLS_DIR:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))
else
BUILD_TOOLS_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
endif
include $(BUILD_TOOLS_DIR)Workspace.mk
include $(BUILD_TOOLS_DIR)Tools.mk
include $(BUILD_TOOLS_DIR)Commands.mk

# Controls the verbosity of the build output.
ifeq ($(VERBOSE),1)
export Q = # nil
else
export Q = @
endif

APP_DIR=$(subst \,/,$(WORKSPACE))/$(APP_NAME)
APP_SRC_DIR=$(subst \,/,$(WORKSPACE))/$(APP_NAME)/$(APP_SRC_DIR_NAME)
APP_BUILD_DIR=$(subst \,/,$(WORKSPACE))/$(APP_NAME)/$(APP_BUILD_CONFIG)

OBJECTS = $(subst .c,.o,$(APP_C_FILES))
OBJECTS += $(subst .cpp,.o,$(APP_CPP_FILES))
OBJ_FILES := $(addprefix $(APP_BUILD_CONFIG)/,$(OBJECTS))

IFLAGS=-I$(APP_SRC_DIR) $(foreach path,$(APP_USER_LIBS_INCLUDE), -I$(path))
LFLAGS=$(foreach path,$(APP_USER_LIBS), -l$(path))
LDFLAGS=$(foreach path,$(APP_USER_LIBS_DIR), -L$(path))
LD_LIB_PATH:=$(foreach path,$(APP_USER_LIBS_BIN),$(path)$(PATH_SEP))

# Setting the PATH environment variable
ifeq ($(OS),Windows_NT)
export PATH=C:/windows;C:/windows/system32;$(LD_LIB_PATH);$(GNU_TOOLS);$(MINGW_PATH)/bin;$(MINGW_PATH)/lib;
endif

build_pre_reqs:
	@echo Checking dependencies for building Application
################################################################################
ifeq ($(OS),Windows_NT)
#####################################################################
ifeq ($(wildcard $(MINGW_PATH)/bin/g++$(BINARY)),)
	$(error MinGW $(MINGW_PATH)/bin/g++$(BINARY)......................... not found)
else
	@echo MinGW found
endif
#####################################################################
else
#####################################################################
ifeq ($(shell which g++),)
	$(error g++ ......................... not found)
else
	@echo g++ found
endif
#####################################################################
endif
################################################################################


build: build_pre_reqs
	$(Q)$(call CHDIR, $(APP_DIR)) && \
	$(MAKE) -j$(NUMBER_OF_PROCESSORS) -f $(BUILD_TOOLS_DIR)App.mk $(APP_BUILD_CONFIG)/$(APP_NAME)$(BINARY)

$(APP_BUILD_CONFIG)/$(APP_NAME)$(BINARY): $(OBJ_FILES)
	@echo	LD	$@
	$(Q)$(call MKDIR, $(APP_BUILD_DIR))
	$(Q)$(call CHDIR, $(APP_DIR)) && g++ -o $@ $(OBJ_FILES) $(LFLAGS) $(LDFLAGS)

$(APP_BUILD_CONFIG)/%.o: $(APP_SRC_DIR)/%.c
	@echo	CC	$@
	$(Q)$(call MKDIR, $(APP_BUILD_DIR))
	$(Q)$(call MKDIR, $(dir $(APP_DIR)/$@))
	$(Q)$(call CHDIR, $(APP_DIR)) && gcc -c $< -o $@ $(IFLAGS)

$(APP_BUILD_CONFIG)/%.o: $(APP_SRC_DIR)/%.cpp
	@echo	CXX	$@
	$(Q)$(call MKDIR, $(APP_BUILD_DIR))
	$(Q)$(call MKDIR, $(dir $(APP_DIR)/$@))
	$(Q)$(call CHDIR, $(APP_DIR)) && g++ -c $< -o $@ $(IFLAGS)
	
clean:
	$(Q)$(call RMDIR,$(APP_BUILD_DIR))

run:
ifeq ($(OS),Windows_NT)
	$(Q)$(APP_BUILD_DIR)/$(APP_NAME)$(BINARY)
else
	$(Q)export LD_LIBRARY_PATH=$(LD_LIB_PATH) $(SEP) $(APP_BUILD_DIR)/$(APP_NAME)$(BINARY)
endif
	