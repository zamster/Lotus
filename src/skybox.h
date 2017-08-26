#include <stdbi.h>
#include <GL/glfw.h>
#include <cstring>

#define SKYFRONT 0
#define SKYBACK  1
#define SKYLEFT  2
#define SKYRIGHT 3
#define SKYUP    4
#define SKYDOWN  5

class skybox
{
public:
	GLuint SkyboxTexture[6];
	void loadimg( GLuint textureArray[], char *str, int ID );	
	void init();
	void Draw( float x, float y, float z, float width, float height, float length );
};