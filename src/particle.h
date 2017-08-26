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
	vector3f position; //λ��
	vector3f velocity; //�ٶ�
	int color;//��ɫ
	void generate( vector3f v0 );//�������Ӻ���
};

class particlesystem
{
public:
	unsigned int texture;//����
	vector3f acceleration;//���ٶ�
	vector<particle> particles;//����
	
	void init( int n, vector3f v0 );
	void seta( vector3f a );//�趨���ٶ�
	void update( float time );//��������״̬
	void render();//��Ⱦ
};