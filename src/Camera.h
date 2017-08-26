#include <GL/glfw.h>  
#include <cmath>

#include "FxMath.h"

#define CAMERASPEED	0.03f

using namespace FxMath;
void GLFWCALL handle_key_down(int key, int action);

class CCamera 
{
public:
	vector3f mPos;//�����λ��
	vector3f mView;	//����			
	vector3f mUp;//����������
	
	void Strafe_Camera(float speed);//�������������
	void Rotate_Position(float speed);//��ת�����
	void Move_Camera(float speed);//�ƶ������
	void Mouse_Move(int wndWidth, int wndHeight);//�����ת
	void Rotate_View(float speed);//��ת����
	void Position_Camera(float pos_x, float pos_y, float pos_z, float view_x, float view_y, float view_z, float up_x, float up_y, float up_z);//�趨�����λ��
};
