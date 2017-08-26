#include <Gl/glfw.h>
#include <stdbi.h>
#include <cmath>
#include <vector>
#include <cmath>
#include "FxMath.h"
#include <iostream>
using namespace std;
using namespace FxMath;

class ripple
{
public:
	vector3f position; //位置
	vector3f cursize;//当前大小
	int id;//编号
	int color;//颜色
	float time;//剩余渲染时间
	ripple()//构造函数
	{
		this -> color = 0;
		this -> id = 0;
		this -> time = 0;

		this -> position = vector3f( 0, 0, 0 );
		this -> cursize = vector3f( 0, 0, 0 );
	}
	void generate( vector3f pos, int color );//生成涟漪
};

class ripplesystem
{
public:
	GLuint frames[4];//纹理
	vector< ripple > ripples;//涟漪
	vector3f spread;//扩散速度
	
	void init( int n );
	void setspread( vector3f s );
	void update( float time );//更新每个涟漪状态
	void render();//渲染
};