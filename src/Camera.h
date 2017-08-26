#include <GL/glfw.h>  
#include <cmath>

#include "FxMath.h"

#define CAMERASPEED	0.03f

using namespace FxMath;
void GLFWCALL handle_key_down(int key, int action);

class CCamera 
{
public:
	vector3f mPos;//摄像机位置
	vector3f mView;	//视向			
	vector3f mUp;//正方向向量
	
	void Strafe_Camera(float speed);//控制摄像机反馈
	void Rotate_Position(float speed);//旋转摄像机
	void Move_Camera(float speed);//移动摄像机
	void Mouse_Move(int wndWidth, int wndHeight);//鼠标旋转
	void Rotate_View(float speed);//旋转视向
	void Position_Camera(float pos_x, float pos_y, float pos_z, float view_x, float view_y, float view_z, float up_x, float up_y, float up_z);//设定摄像机位置
};
