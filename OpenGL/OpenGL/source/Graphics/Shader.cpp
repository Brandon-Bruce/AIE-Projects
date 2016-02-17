#include "Shader.h"
#include "gl_core_4_4.h"
#include "glm\vec3.hpp"
#include "glm\ext.hpp"
#include "glfw\glfw3.h"
#include "GraphicsManager.h"
#include "Camera.h"

using glm::vec4;
using glm::vec3;


Shader::~Shader()
{

}

void Shader::LoadShader()
{
	//Create shader
	const char* vsSource =	"#version 410\n"
							"layout(location = 0) in vec4 Position;"
							"layout(location = 1) in vec4 Colour;"
							"out vec4 vColour;"
							"uniform mat4 ProjectionView;"
							"uniform float time;"
							"uniform float heightScale;"
							"void main()"
							"{"
								"vColour = Colour;"
								"vec4 P = Position;"
								"P.y += sin( time + Position.x ) * heightScale;"
								"gl_Position = ProjectionView * P;"
							"}";

	const char* fsSource =	"#version 410\n"
							"in vec4 vColour;"
							"out vec4 FragColor;"
							"void main() { FragColor = vColour; }";

	int success = GL_FALSE;
	unsigned int vertextShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertextShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertextShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertextShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertextShader);
}

void Shader::GenerateGrid(unsigned int rows, unsigned int cols)
{
	this->rows = rows; this->cols = cols;
	Vertex* aoVerticies = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVerticies[r*cols + c].position = vec4((float)c, 0, (float)r, 1);

			//create arbitrary colour based off something
			//that might not be related to tiling a texture
			vec3 colour = vec3(sinf((c / (float)(cols - 1)) *
									(r / (float)(rows - 1))));
			aoVerticies[r * cols + c].colour = vec4(colour, 1);
		}
	}

	//Defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);

			//triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	//Generate GL buffers
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//Generate VertexArrayObject
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	//Bind buffers to a vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex),
									aoVerticies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
											(void*)(sizeof(vec4)));

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 *
						sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

	//
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] aoVerticies;
}

void Shader::Draw(float deltatime, float time)
{
	glUseProgram(m_programID);
	//Set variables for shader
	unsigned int projectionViewUniform =
		glGetUniformLocation(m_programID, "ProjectionView");
	glUniformMatrix4fv(projectionViewUniform, 1, false,
		glm::value_ptr(GRAPHICSMANAGER.GetCamera()->GetProjectionView()));

	unsigned int timeUniform = glGetUniformLocation(m_programID, "time");
	glUniform1f(timeUniform, time);

	unsigned int heightScaleUniform =
		glGetUniformLocation(m_programID, "heightScale");
	glUniform1f(heightScaleUniform, 2.0f);

	glBindVertexArray(m_VAO);
	unsigned int indexCount = (rows - 1) * (cols - 1) * 6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
