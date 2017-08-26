#include "wave.h"

void water::init()
{
	stbi_uc *buff;
	int comp, sizex, sizey;	
	buff = stbi_load( "Data/down.jpg", &sizex, &sizey, &comp, 0 );
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, sizex, sizey, GL_RGB, GL_UNSIGNED_BYTE, buff);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

float water::func( float x, float z )
{
	float timer=(float)timeGetTime()/1000;
	float y = 0;
	float factor = 1;
	float d = sqrt( x * x + z * z );
	d = d / 40;
	if ( d > 1.5 ) 
	d = 1.5;
	if ( d < 0 ) 
	d = 0;
	for ( int i = 0; i < 5; i++ )
	{
		y -= (factor) * VTXSIZE * d * cos(((float)timer*SPEED) + (1/factor) * x * z * WAVESIZE)
		   + (factor) * VTXSIZE * d * cos(((float)timer*SPEED) + (1/factor) * x * z * WAVESIZE) ;
		
		factor = factor/2;
	}
	return y;
}

void water::draw()
{
	glPushMatrix();
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_LINE_BIT | GL_CURRENT_BIT);

	for ( int xi =-25; xi < XFIELD / 2; xi++ )
	{

		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_TRIANGLE_STRIP);

		for ( int zi = -25 ; zi < ZFIELD / 2; zi++ )
		{
			point p(xi*QUADSIZE,0,zi*QUADSIZE);
			p.y=func(xi,zi);
			point q((xi+1)*QUADSIZE,0,zi*QUADSIZE);
			q.y=func(xi+1,zi);
			point r((xi)*QUADSIZE,0,(zi+1)*QUADSIZE);
			r.y=func(xi,zi+1);


			point e1=q-p;
			point e2=r-p;
			point e3;
			e3=e1^e2;

			plane pl(0,-1,0,10);
			point res;
			pl.testline(p,e3,res);
			float col=p.y*0.1+0.8;
			glColor4f(col,col,col,0.8);
			glTexCoord2f(res.x/TEXDIVIDER,res.z/TEXDIVIDER);
			glVertex3f(p.x * 10,p.y,p.z* 10);

			point pold=p;
			p=q;
			q.create((xi+2)*QUADSIZE,0,zi*QUADSIZE);q.y=func(xi+2,zi);
			r.create((xi+1)*QUADSIZE,0,(zi+1)*QUADSIZE);r.y=func(xi+1,zi+1);

			e1=q-p;
			e2=r-p;
			e3=e1^e2;

			pl.testline(p,e3,res);
			col=p.y*0.1+0.8;
			glColor4f(col,col,col,0.8);

			glTexCoord2f(res.x/TEXDIVIDER,res.z/TEXDIVIDER);
			glVertex3f(p.x* 10,p.y,p.z* 10);
		}
		glEnd();
	}
	glPopAttrib();
	glPopMatrix();
}