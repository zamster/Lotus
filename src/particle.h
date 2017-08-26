#include <Gl/glfw.h>
#include <stdbi.h>
#include <cmath>
#include <vector>
#include <iostream>
#include "FxMath.h"
using namespace std;
using namespace FxMath;

#define RANGEX 30
#define RANGEY 30

class particle
{
public:
	vector3f position; //位置
	vector3f velocity; //速度
	int color;//颜色
	void generate( vector3f v0 );//生成粒子函数
};

class particlesystem
{
public:
	unsigned int texture;//纹理
	vector3f acceleration;//加速度
	vector<particle> particles;//粒子
	
	void init( int n, vector3f v0 );
	void seta( vector3f a );//设定加速度
	void update( float time );//更新粒子状态
	void render();//渲染
};