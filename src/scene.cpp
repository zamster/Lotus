#include "scene.h"

ms3d::ms3d( const char *lpszFileName )
{
	entity = new CMS3DFile();
	entity -> LoadFromFile(lpszFileName);
}

void ms3d::render()
{
	entity -> Draw();
}
scene::scene()
{	
	SkyBox.init();
	obj.clear();
	srand( time(NULL) );
	ms3d *lotus = new ms3d("Data/lotus.ms3d");
	lotus -> x = 0;
	lotus -> y = -0.4;
	lotus -> z = 0;
	addnode( *lotus );

	ms3d *l1 = new ms3d("Data/1.ms3d");
	l1 -> x = rand() % 65535 / 10000;
	l1 -> y = 0;
	l1 -> z = rand() % 65535 / 10000;
	addnode( *l1 );
	
	ms3d *l2 = new ms3d("Data/2.ms3d");
	l2 -> x = rand() % 65535 / 10000;
	l2 -> y = -0.2;
	l2 -> z = rand() % 65535 / 10000;
	addnode( *l2 );
	
	ms3d *l3 = new ms3d("Data/3.ms3d");
	l3 -> x = rand() % 65535 / 10000;
	l3 -> y = 0.1;
	l3 -> z = rand() % 65535 / 10000;
	addnode( *l3 );
	
	ms3d *l4 = new ms3d("Data/4.ms3d");
	l4 -> x = rand() % 65535 / 10000;
	l4 -> y = 0;
	l4 -> z = rand() % 65535 / 10000;
	addnode( *l4 );
	
	ms3d *l5 = new ms3d("Data/3.ms3d");
	l5 -> x = rand() % 65535 / 10000;
	l5 -> y = 0;
	l5 -> z = rand() % 65535 / 10000;
	addnode( *l5 );
	
	ms3d *l6 = new ms3d("Data/6.ms3d");
	l6 -> x = rand() % 65535 / 10000;
	l6 -> y = -0.1;
	l6 -> z = rand() % 65535 / 10000;
	addnode( *l6 );
}

void scene::render()
{	
	SkyBox.Draw(0,128,0,512,256,512);
		
	for ( unsigned int i = 0 ; i < obj.size() ; i++ )
	{
		glPushMatrix();
		glScalef(10, 10, 10);
		glTranslatef( obj[i].x, obj[i].y, obj[i].z );
		obj[i].render();
		glPushAttrib(GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
		glLineWidth(5);
		glColor3f(0,0,0);	
		glEnable(GL_CULL_FACE);		
		glCullFace(GL_FRONT);	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		obj[i].render();
		glPopAttrib();
		glPopMatrix();
	}
}