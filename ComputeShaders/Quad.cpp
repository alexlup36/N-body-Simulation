#include "Quad.h"

Quad::Quad()
{
}

Quad::~Quad()
{
	// Deleted inside the Model
}

void Quad::Create()
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	
	// Create and bind vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Define vertices
	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	vertices.push_back(VertexFormat(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
	
	// IBO data
	GLuint indexData[] = { 0, 1, 2, 2, 3, 0 };
	
	// Create VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);
	
	// Create IBO
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

	glBindVertexArray(0);
	
	// Setup mesh
	this->m_uiVao = vao;
	this->m_uiVbo = vbo;
	this->m_uiIbo = ibo;

	// Get references to the uniform variables
	m_uiModelMatrixUniform = glGetUniformLocation(m_uiProgram, "model");
	m_uiViewMatrixUniform = glGetUniformLocation(m_uiProgram, "view");
	m_uiProjectionMatrixUniform = glGetUniformLocation(m_uiProgram, "projection");
}

void Quad::CreateScreenPercentage(float percentage)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	// Create and bind vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Define vertices
	std::vector<VertexPT> vertices;
	vertices.push_back(VertexPT(glm::vec3(-percentage, -percentage, 0.0f), glm::vec2(0.0f, 0.0f)));
	vertices.push_back(VertexPT(glm::vec3(percentage, -percentage, 0.0f), glm::vec2(1.0f, 0.0f)));
	vertices.push_back(VertexPT(glm::vec3(percentage, percentage, 0.0f), glm::vec2(1.0f, 1.0f)));
	vertices.push_back(VertexPT(glm::vec3(-percentage, percentage, 0.0f), glm::vec2(0.0f, 1.0f)));

	// IBO data
	GLuint indexData[] = { 0, 1, 2, 2, 3, 0 };

	// Create VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexPT), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPT), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPT), (void*)12);

	// Create IBO
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

	glBindVertexArray(0);

	// Setup mesh
	this->m_uiVao = vao;
	this->m_uiVbo = vbo;
	this->m_uiIbo = ibo;

	// Get references to the uniform variables
	m_uiModelMatrixUniform = glGetUniformLocation(m_uiProgram, "model");
	m_uiViewMatrixUniform = glGetUniformLocation(m_uiProgram, "view");
	m_uiProjectionMatrixUniform = glGetUniformLocation(m_uiProgram, "projection");
}

void Quad::Update(double dt)
{
}

void Quad::Draw(CameraEuler* camera)
{
	// Bind program
	glUseProgram(m_uiProgram);

	// Set model, view, projection matrices
	glUniformMatrix4fv(m_uiModelMatrixUniform, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
	glUniformMatrix4fv(m_uiViewMatrixUniform, 1, GL_FALSE, &camera->ViewMatrix()[0][0]);
	glUniformMatrix4fv(m_uiProjectionMatrixUniform, 1, GL_FALSE, &camera->ProjectionMatrix()[0][0]);

	// Bind vertex array object
	glBindVertexArray(m_uiVao);

	// Draw command
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}