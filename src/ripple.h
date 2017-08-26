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
	vector3f position; //λ��
	vector3f cursize;//��ǰ��С
	int id;//���
	int color;//��ɫ
	float time;//ʣ����Ⱦʱ��
	ripple()//���캯��
	{
		this -> color = 0;
		this -> id = 0;
		this -> time = 0;

		this -> position = vector3f( 0, 0, 0 );
		this -> cursize = vector3f( 0, 0, 0 );
	}
	void generate( vector3f pos, int color );//��������
};

class ripplesystem
{
public:
	GLuint frames[4];//����
	vector< ripple > ripples;//����
	vector3f spread;//��ɢ�ٶ�
	
	void init( int n );
	void setspread( vector3f s );
	void update( float time );//����ÿ������״̬
	void render();//��Ⱦ
};