#ifndef A_GLSL_H
#define A_GLSL_H

#include <GL/glew.h>

//-----------------------------------------------------------------------------
#include <vector>
#include <iostream>
//-----------------------------------------------------------------------------

#define GLSLAPI  

class GLSLAPI glShaderObject
{
	friend class glShader;

public:
	glShaderObject();
	virtual ~glShaderObject();
	
	int load(char* filename); 
	void loadFromMemory(const char* program);
	
	bool compile(void); 
	char* getCompilerLog(void); 
	GLint getAttribLocation(char* attribName); 

protected:

	int                 program_type;

	GLuint              ShaderObject;
	GLubyte*            ShaderSource;
	
	GLcharARB*          compiler_log;
	
	bool                is_compiled; 
	bool                _memalloc;

	
};

//-----------------------------------------------------------------------------

class GLSLAPI aVertexShader : public glShaderObject
{
public:
	aVertexShader();
	~aVertexShader(); 
};

//-----------------------------------------------------------------------------

class GLSLAPI aFragmentShader : public glShaderObject
{
public:
	aFragmentShader();
	~aFragmentShader();

};

//-----------------------------------------------------------------------------

class GLSLAPI glShader
{
public:
	glShader();                  
	virtual ~glShader();
	void addShader(glShaderObject* ShaderProgram); 

	bool link(void); 
	char* getLinkerLog(void);

	void begin();
	void end();

	bool oglslEnabled(void);

	bool setUniform1f(char* varname, GLfloat v0);
	bool setUniform2f(char* varname, GLfloat v0, GLfloat v1); 
	bool setUniform3f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2); 
	bool setUniform4f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	bool setUniform1i(char* varname, GLint v0);
	bool setUniform2i(char* varname, GLint v0, GLint v1);
	bool setUniform3i(char* varname, GLint v0, GLint v1, GLint v2);
	bool setUniform4i(char* varname, GLint v0, GLint v1, GLint v2, GLint v3);

	bool setUniform1fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform2fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform3fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform4fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform1iv(char* varname, GLsizei count, GLint *value);
	bool setUniform2iv(char* varname, GLsizei count, GLint *value);
	bool setUniform3iv(char* varname, GLsizei count, GLint *value);
	bool setUniform4iv(char* varname, GLsizei count, GLint *value);

	bool setUniformMatrix2fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value);
	bool setUniformMatrix3fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value);
	bool setUniformMatrix4fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value);

	void GetUniformfv(char* name, GLfloat* values);
	void GetUniformiv(char* name, GLint* values); 

	bool setVertexAttrib1f(GLuint index, GLfloat v0);
	bool setVertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1);
	bool setVertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2);
	bool setVertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	void manageMemory(void){_mM = true;}

	void enable(void)
	{
		_noshader = true;
	}
	void disable(void)
	{
		_noshader = false;
	} 
	
private:
	GLint GetUniLoc(const GLcharARB *name);

	GLuint              ProgramObject;


	GLcharARB*          linker_log;
	bool                is_linked;
	std::vector<glShaderObject*> ShaderList; 

	bool                _mM;
	bool                _noshader;
	
};

class GLSLAPI glShaderManager
{
public:
	glShaderManager();
	virtual ~glShaderManager();

	glShader* loadfromFile(char* vertexFile, char* fragmentFile);    // load vertex/fragment shader from file
	glShader* loadfromMemory(const char* vertexMem, const char* fragmentMem);
	
	bool           free(glShader* o);

private:
	std::vector<glShader*>  _shaderObjectList;      
};

bool GLSLAPI initGLExtensions(void);
bool GLSLAPI checkGLSL(void);
bool GLSLAPI checkGL2(void);

#endif // A_GLSL_H
