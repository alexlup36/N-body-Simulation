#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
	// Deleted inside the Model
}

void Triangle::Create()
{
	GLuint vao;
	GLuint vbo;

	// Create and bind vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Define vertices
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.25f, -0.25f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25f, -0.25f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(0.25f, 0.25f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));

	// Setup vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);

	glBindVertexArray(0);

	// Store the vertex array object and the vertex buffer object
	this->m_uiVao = vao;
	this->m_uiVbo = vbo;

	// Get references to the uniform variables
	m_uiModelMatrixUniform			= glGetUniformLocation(m_uiProgram, "model");
	m_uiViewMatrixUniform			= glGetUniformLocation(m_uiProgram, "view");
	m_uiProjectionMatrixUniform		= glGetUniformLocation(m_uiProgram, "projection");
}

void Triangle::Update(double dt)
{
}

void Triangle::Draw(CameraEuler* camera)
{
	glUseProgram(m_uiProgram);

	// Set uniforms
	glUniformMatrix4fv(m_uiModelMatrixUniform, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
	glUniformMatrix4fv(m_uiViewMatrixUniform, 1, GL_FALSE, &camera->ViewMatrix()[0][0]);
	glUniformMatrix4fv(m_uiProjectionMatrixUniform, 1, GL_FALSE, &camera->ProjectionMatrix()[0][0]);

	glBindVertexArray(m_uiVao);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
