#include "Program.h"
#include <iostream>

void Program::Create(const char * pVertShader, const char * pFragShader)
{
	int success = GL_FALSE;
	unsigned int vertextShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertextShader, 1, (const char**)&pVertShader, 0);
	glCompileShader(vertextShader);
	glShaderSource(fragmentShader, 1, (const char**)&pFragShader, 0);
	glCompileShader(fragmentShader);

	program_ID = glCreateProgram();
	glAttachShader(program_ID, vertextShader);
	glAttachShader(program_ID, fragmentShader);
	glLinkProgram(program_ID);

	glGetProgramiv(program_ID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(program_ID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertextShader);
}

GLuint Program::GetProgramID()
{
	return GLuint();
}
