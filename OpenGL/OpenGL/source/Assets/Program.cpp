#include "gl_core_4_4.h"
#include "Program.h"
#include <iostream>
#include <string>

void Program::Create(const std::string& pVertShader, const std::string& pFragShader)
{
	Create(pVertShader.c_str(), pFragShader.c_str());
}

void Program::Create(const char * pVertShader, const char * pFragShader)
{
	int success = GL_FALSE;
	unsigned int vertextShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertextShader, 1, (const char**)&pVertShader, 0);
	glCompileShader(vertextShader);
	glShaderSource(fragmentShader, 1, (const char**)&pFragShader, 0);
	glCompileShader(fragmentShader);

	CheckCompileStatus(fragmentShader);
	CheckCompileStatus(vertextShader);

	program_ID = glCreateProgram();
	glAttachShader(program_ID, vertextShader);
	glAttachShader(program_ID, fragmentShader);
	glLinkProgram(program_ID);

	CheckLinkStatus();

	glDeleteShader(fragmentShader);
	glDeleteShader(vertextShader);
}

bool Program::CheckCompileStatus(unsigned int shaderId)
{
	GLint result = GL_FALSE;
	int logLength = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetShaderInfoLog(shaderId, logLength, NULL, logBuffer);
		std::cerr << "Compile Error: " << logBuffer << std::endl;
		delete[] logBuffer;
		return false;
	}
	return true;
}

bool Program::CheckLinkStatus()
{
	GLint result = GL_FALSE;
	int logLength = 0;
	glGetProgramiv(program_ID, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetProgramInfoLog(program_ID, logLength, NULL, logBuffer);
		std::cerr << "Link Error: " << logBuffer << std::endl;
		delete[] logBuffer;
		return false;
	}
	return true;
}

GLuint Program::GetProgramID()
{
	return program_ID;
}

void Program::CleanUp()
{
	glDeleteProgram(program_ID);
}
