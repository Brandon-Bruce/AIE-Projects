#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>

class Program
{
public:
	void Create(const std::string& pVertShader, const std::string& pFragShader);
	void Create(const char* pVertShader, const char* pFragShader);
	unsigned int GetProgramID();
	void CleanUp();

private:
	bool CheckCompileStatus(unsigned int shaderId);
	bool CheckLinkStatus();

	unsigned int program_ID;
};

#endif