#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdbi.h>

#include "glsl.h"
#include "Camera.h"
#include "scene.h"
#include "wave.h"
#include "particle.h"
#include "ripple.h"
#include <GL/glfw.h>
#include <irrKlang/irrKlang.h>

using namespace std;
using namespace irrklang;

CCamera objCamera;
ripplesystem *rs;

void initOpenGL()
{	
	initGLExtensions();
	glfwSetKeyCallback( handle_key_down );
	glfwEnable( GLFW_KEY_REPEAT );
	glfwEnable( GLFW_STICKY_MOUSE_BUTTONS );
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable( GL_TEXTURE_2D );
	glDepthFunc(GL_LEQUAL);	
	objCamera.Position_Camera(0, 4.0f, 5,	0, 2.5f, 0,   0, 1, 0);
}


int main( void )
{
	int     width, height, running, frames, x, y;
	double  t, t0, fps;
	char    titlestr[ 200 ];

	glfwInit();

	if( !glfwOpenWindow( 1024, 576, 0,0,0,0, 0,0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		return 0;
	}

	glfwEnable( GLFW_STICKY_KEYS );

	glfwSwapInterval( 0 );
	
	running = true;
	frames = 0;
	t0 = glfwGetTime();
	
	initOpenGL();	
	
	scene Scene;	
	water *aWave = new water();
	aWave -> init();
	
	particlesystem* ps = new particlesystem();
	
	ps -> init( 2500, vector3f(0,0,0) );
	ps -> seta( vector3f(0.f,-0.3,0.f) );
	
	rs = new ripplesystem();
	rs -> init( 2500 );
	rs -> setspread( vector3f( 0.6, 0.0, 0.6 ) );
	ISoundEngine* sound = createIrrKlangDevice();
	sound->play2D( "data/bgm.mp3", true);
	
	while( running )
	{
		t = glfwGetTime();
		glfwGetMousePos( &x, &y );
		objCamera.Mouse_Move(1024, 576);
		
		glfwGetWindowSize( &width, &height );
		height = height > 0 ? height : 1;
		
		glViewport( 0, 0, width, height );
		
		glClearColor( 0.75f, 0.75f, 0.75f, 0.75f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f );
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z, objCamera.mView.x, objCamera.mView.y, objCamera.mView.z, objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);
		
		Scene.render();
		aWave -> draw();

		ps -> update( 0.1 );	
		ps -> render();
		
		rs -> update( 0.1 );
		rs -> render();
		
		if( (t-t0) > 1.0 || frames == 0 )
		{
			fps = (double)frames / (t-t0);
			sprintf( titlestr, "Lutos Pool in a Colorful Rain (%.1f FPS)", fps );
			glfwSetWindowTitle( titlestr );
			t0 = t;
			frames = 0;
		}
		frames ++;
		glfwSwapBuffers();
		running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
		
	}
	glfwTerminate();
	sound->drop(); 
	return 0;
}
