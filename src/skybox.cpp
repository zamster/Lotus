#include "skybox.h"

void skybox::loadimg( GLuint textureArray[], char *str, int ID )
{
	stbi_uc *buff;
	int comp, sizex, sizey;	
	char add[256] = "Data/";
	strcat( add, str );
	buff = stbi_load( add, &sizex, &sizey, &comp, 0 );
	glGenTextures(1, &textureArray[ID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, sizex, sizey, GL_RGB, GL_UNSIGNED_BYTE, buff);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void  skybox::init()
{
	loadimg(SkyboxTexture,"front.png",  SKYFRONT);
	loadimg(SkyboxTexture,"back.png",   SKYBACK);
	loadimg(SkyboxTexture,"left.png",   SKYLEFT);
	loadimg(SkyboxTexture,"right.png",  SKYRIGHT);
	// loadimg(SkyboxTexture,"up2.jpg",     SKYUP);
	// loadimg(SkyboxTexture,"down.jpg",   SKYDOWN);
}

void skybox::Draw( float x, float y, float z, float width, float height, float length )
{
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;


	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYFRONT]);
	glBegin(GL_QUADS);	
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height, z+length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYBACK]);
	glBegin(GL_QUADS);		
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYLEFT]);
	glBegin(GL_QUADS);		
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z);	
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z+length); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYRIGHT]);
	glBegin(GL_QUADS);		
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height,	z+length); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYUP]);
	// glBegin(GL_QUADS);		
	// glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z);
	// glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
	// glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z+length);
	// glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z);
	// glEnd();

	// glBindTexture(GL_TEXTURE_2D, SkyboxTexture[SKYDOWN]);
	// glBegin(GL_QUADS);		
	// glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z);
	// glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z+length);
	// glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length); 
	// glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
	// glEnd();

}