#include "Camera.h"

extern CCamera objCamera;
void CCamera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
							  float view_x, float view_y, float view_z,
							  float up_x,   float up_y,   float up_z)
{
	mPos	= vector3f(pos_x,  pos_y,  pos_z );
	mView	= vector3f(view_x, view_y, view_z);
	mUp		= vector3f(up_x,   up_y,   up_z  );
}

void CCamera::Move_Camera(float speed)
{
	vector3f vVector = mView - mPos;
	
	mPos.x  = mPos.x  + vVector.x * speed;
	mPos.z  = mPos.z  + vVector.z * speed;
	mView.x = mView.x + vVector.x * speed;
	mView.z = mView.z + vVector.z * speed;
}


void CCamera::Rotate_View(float speed)
{
	vector3f vVector = mView - mPos;

	mView.z = (float)(mPos.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	mView.x = (float)(mPos.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}

void CCamera::Rotate_Position(float speed)
{	
	vector3f vVector = mPos - mView;

	mPos.z = (float)(mView.z + sin(speed)*vVector.x + cos(speed)*vVector.z);
	mPos.x = (float)(mView.x + cos(speed)*vVector.x - sin(speed)*vVector.z);
}

void CCamera::Strafe_Camera(float speed)
{
	vector3f vVector = mView - mPos;
	vector3f vOrthoVector;

	vOrthoVector.x = -vVector.z;
	vOrthoVector.z =  vVector.x;

	mPos.x  = mPos.x  + vOrthoVector.x * speed;
	mPos.z  = mPos.z  + vOrthoVector.z * speed;
	mView.x = mView.x + vOrthoVector.x * speed;
	mView.z = mView.z + vOrthoVector.z * speed;
}

void CCamera::Mouse_Move( int wndWidth, int wndHeight )
{
	int x, y;
	int mid_x = wndWidth  >> 1;	
	int mid_y = wndHeight >> 1;	
	float angle_y  = 0.0f;				
	float angle_z  = 0.0f;							
	
	glfwGetMousePos( &x, &y );
	
	if( ( x == mid_x ) && ( y == mid_y ) ) 
		return;

	glfwSetMousePos(mid_x, mid_y);

	angle_y = (float)( (mid_x - x) ) / 1000;		
	angle_z = (float)( (mid_y - y) ) / 1000;

	mView.y += angle_z * 2;

	if(mView.y > 3.5f)		mView.y = 3.5f;
	if(mView.y < 0.4f)		mView.y = 0.4f;
	
	Rotate_Position(-angle_y);
}

void GLFWCALL handle_key_down(int key, int action)
{
	if( action != GLFW_PRESS )
	{ 
		return;
	}
	switch(key) 
	{
	case 'A':
		objCamera.Rotate_View(-CAMERASPEED);
		break;
	case 'D':
		objCamera.Rotate_View( CAMERASPEED);
		break;
	case 'W':
		objCamera.Move_Camera( CAMERASPEED);
		break;
	case 'S':
		objCamera.Move_Camera(-CAMERASPEED);
		break;		
	default:
		break;
	}
}
