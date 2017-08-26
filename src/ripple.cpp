#include "ripple.h"
const float colors[][3] = 
{
	{0, 0, 0},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 0},
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
};

void ripple::generate( vector3f pos, int color )
{
	this -> color = color;
	this -> id = rand() % 4;
	this -> time = 2;
	this -> position = pos;
	this -> cursize = vector3f( 0, 0, 0 );
}

void ripplesystem::init( int n )
{
	for ( int i = 0 ; i < 4; i ++ )
	{
		stbi_uc *buff;
		int comp, sizex, sizey;	
		char add[256];
		memset(add, 0, sizeof(add));
		sprintf( add, "Data/cir/%d.png", i + 1 );
		buff = stbi_png_load( add, &sizex, &sizey, &comp, 4 );
		glGenTextures(1, &frames[i]);
		glBindTexture(GL_TEXTURE_2D, frames[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizex, sizey, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);
	}
	ripples.assign( n, ripple() );
}

void ripplesystem::setspread( vector3f s )
{
	spread = s;
}

void ripplesystem::update( float time )
{
	vector<ripple>::iterator iter;
	for ( iter = ripples.begin() ; iter != ripples.end() ; iter++ )
	{
		iter -> cursize = iter -> cursize + spread * time;
		iter -> time -= time;
	}
	
}

void ripplesystem::render()
{
	vector<ripple>::iterator iter;
	glPushMatrix();
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
	
	for ( iter = ripples.begin() ; iter != ripples.end() ; iter++ )
	{
		if ( iter -> time > 0 )
		{
			float tmpx = iter -> position.x;
			float tmpz = iter -> position.z;
			
			float sx = iter -> cursize.x;
			float sz = iter -> cursize.z;
			glBindTexture(GL_TEXTURE_2D, frames[iter -> id]);
			glBegin(GL_QUADS);
			glColor3fv( colors[iter->color] );	
			glTexCoord2f(0.0f, 1.0f); glVertex3f( tmpx - sx, 1, tmpz - sz );
			glTexCoord2f(1.0f, 1.0f); glVertex3f( tmpx - sx, 1, tmpz + sz );
			glTexCoord2f(1.0f, 0.0f); glVertex3f( tmpx + sx, 1, tmpz + sz ); 
			glTexCoord2f(0.0f, 0.0f); glVertex3f( tmpx + sx, 1, tmpz - sz );
			glEnd();
		}
	}
	glPopAttrib();
	glPopMatrix();
}