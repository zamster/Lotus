#include <vector>
#include <cmath>
#include <time.h>

#include "MS3DFile.h"
#include "skybox.h"
using namespace std;

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

class ms3d
{
public:
	float x, y, z;
	float rx, ry, rz;
	CMS3DFile *entity;
	
	ms3d()
	{
		x = y = z = 0.f;
		rx = ry = rz = 0.f;
	}
	ms3d( const char *lpszFileName );
	void render();
};

class scene
{
public:
	skybox SkyBox;
	vector <ms3d> obj;
	
	scene();
	
	void addnode( ms3d node )
	{
		obj.push_back( node );
	}
	
	void render();
};
