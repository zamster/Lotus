#include "particle.h"
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

extern ripplesystem* rs;

void particle::generate( vector3f v0 )
{
	this->velocity = v0;
	
	float x = float(((rand()%(RANGEX*20))-RANGEY*10.0f)/10.0f);
	float y = float(((rand()%(50*20))-50*10.0f)/10.0f) + 60;
	float z = float(((rand()%(RANGEX*20))-RANGEY*10.0f)/10.0f);
	
	this->position = vector3f( x, y, z );
	this->color = rand() % 8;

}

void particlesystem::init( int n, vector3f v0 )
{
	stbi_uc *buff;
	int comp, sizex, sizey;	
	buff = stbi_png_load( "Data/rain.png", &sizex, &sizey, &comp, 4 );
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizex, sizey, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);
	
	for ( int i = 0 ; i < n ; i++ )
	{
		particle *tmp = new particle;
		
		tmp -> generate( v0 );
		particles.push_back( *tmp );
		
		delete tmp;
	}
	
}

void particlesystem::seta( vector3f a )
{
	acceleration = a;
}

void particlesystem::update( float time )
{
	vector<particle>::iterator iter;
	for ( iter = particles.begin() ; iter < particles.end() ; iter++ )
	{
		iter -> velocity = iter -> velocity + acceleration * time;
		iter -> position = iter -> position + iter -> velocity * time;
	}
}

void particlesystem::render()
{
	vector<particle>::iterator iter;
	
	glPushMatrix();
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
	
	glBindTexture(GL_TEXTURE_2D, texture);		
	glBegin(GL_QUADS);
	for ( int i = 0; i < particles.size() ; i++ )
	{
		float tmpx = particles[i].position.x;
		float tmpy = particles[i].position.y;
		float tmpz = particles[i].position.z;
		glColor3fv( colors[particles[i].color] );
		glTexCoord2f(0.0f, 1.0f); glVertex3f( tmpx - 0.03f, tmpy - 6.4f, tmpz );
		glTexCoord2f(1.0f, 1.0f); glVertex3f( tmpx - 0.03f, tmpy + 6.4f, tmpz );
		glTexCoord2f(1.0f, 0.0f); glVertex3f( tmpx + 0.03f, tmpy + 6.4f, tmpz ); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f( tmpx + 0.03f, tmpy - 6.4f, tmpz );
		
		if ( tmpy - 1 < 0 )
		{
			rs -> ripples[i].generate( vector3f( tmpx, 0, tmpz ), particles[i].color );
			particles[i].generate( vector3f(0, 0, 0) );
		}
	}
	glEnd();
		
	glPopAttrib();
	glPopMatrix();
}


