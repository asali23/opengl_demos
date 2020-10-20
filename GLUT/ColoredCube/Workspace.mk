################################################################################
# Workspace Settings
################################################################################
WORKSPACE:=C:/workspace/learning/OpenGL

################################################################################
# Application Project Settings
################################################################################
APP_NAME:=ColoredCube
APP_BUILD_CONFIG:=Build
APP_SRC_DIR_NAME:=src

APP_USER_LIBS:=freeglut glew32 opengl32
APP_USER_LIBS_DIR:=$(WORKSPACE)/freeglut/lib $(WORKSPACE)/glew-1.11.0/lib
APP_USER_LIBS_INCLUDE:=$(WORKSPACE)/freeglut/include $(WORKSPACE)/glew-1.11.0/include $(WORKSPACE)/glm
APP_USER_LIBS_BIN:=$(WORKSPACE)/freeglut/bin $(WORKSPACE)/glew-1.11.0/lib

APP_C_FILES:=
APP_CPP_FILES:=main.cpp Model.cpp Object3D.cpp Camera.cpp
################################################################################
