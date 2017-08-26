# Compiler settings
CC     = cl
CFLAGS = /MT /EHs /Ox /D "GLEW_STATIC"
#Target
BIN  = main.exe
OBJ  = main.obj glsl.obj FxMath.obj MS3DFile.obj Camera.obj skybox.obj scene.obj wave.obj point.obj plane.obj particle.obj ripple.obj
# Linker settings
LIBS = glew_static.lib glfw.lib opengl32.lib glu32.lib  stdbi.lib user32.lib winmm.lib irrKlang.lib

# Subsystem settings
WINDOWS = -mwindows
CONSOLE = -mconsole

# Default: Build all tests
all: main.exe

# main
$(BIN): $(OBJ)
	$(CC) $(OBJ) $(LIBS) $(CFLAGS)

main.obj: main.cpp
	$(CC) main.cpp /c $(CFLAGS)

glsl.obj: glsl.cpp
	$(CC) glsl.cpp /c $(CFLAGS)

FxMath.obj: FxMath.cpp
	$(CC) FxMath.cpp /c $(CFLAGS)

MS3DFile.obj: MS3DFile.cpp
	$(CC) MS3DFile.cpp /c $(CFLAGS)

Camera.obj: Camera.cpp
	$(CC) Camera.cpp /c $(CFLAGS)

skybox.obj: skybox.cpp
	$(CC) skybox.cpp /c $(CFLAGS)

wave.obj: wave.cpp
	$(CC) wave.cpp /c $(CFLAGS)

scene.obj: scene.cpp
	$(CC) scene.cpp /c $(CFLAGS)

point.obj: point.cpp
	$(CC) point.cpp /c $(CFLAGS)

plane.obj: plane.cpp
	$(CC) plane.cpp /c $(CFLAGS)

particle.obj: particle.cpp
	$(CC) particle.cpp /c $(CFLAGS)

ripple.obj: ripple.cpp
	$(CC) ripple.cpp /c $(CFLAGS)
