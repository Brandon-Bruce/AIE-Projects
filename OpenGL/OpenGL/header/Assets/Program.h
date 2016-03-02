#ifndef PROGRAM_H
#define PROGRAM_H

#include "gl_core_4_4.h"

class Program
{
public:
	void Create(const char* pVertShader, const char* pFragShader);
	GLuint GetProgramID();
	void CleanUp();

protected:
	GLuint program_ID;

private:
	bool CheckCompileStatus(GLuint shaderId);
	bool CheckLinkStatus();
};

#endif