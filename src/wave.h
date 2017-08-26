#ifndef WAVE_H_
#define WAVE_H_
#include <windows.h>
#include <GL/glfw.h>
#include <stdbi.h>
#include <math.h>
// #include "FxMath.h"
#include "point.h"
#include "plane.h"
// using namespace FxMath;
#define XFIELD 128
#define ZFIELD 128

#define QUADSIZE 1
#define VTXSIZE 0.8
#define TEXDIVIDER 30
#define SPEED 2
#define WAVESIZE 0.003

class water
{
public:
	unsigned int tex;
	float func( float x, float z );//计算水纹高度函数
	void init();
	void draw();
};
#endif