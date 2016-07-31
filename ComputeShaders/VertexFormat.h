#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include <glm.hpp>

// ----------------------------------------------------------------------------

struct VertexFormat
{
	glm::vec3 position;
	glm::vec4 color;

	VertexFormat(const glm::vec3& pos, const glm::vec4& col)
	{
		position = pos;
		color = col;
	}
};

// ----------------------------------------------------------------------------

struct VertexPT
{
	glm::vec3 position;
	glm::vec2 texture;

	VertexPT(const glm::vec3& pos, const glm::vec2& tex)
	{
		position = pos;
		texture = tex;
	}
};

// ----------------------------------------------------------------------------

struct VertexPNTT
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
	glm::vec3 tangent;

	VertexPNTT(const glm::vec3& pos,
		const glm::vec3& norm,
		const glm::vec2& text,
		const glm::vec3& tan)
	{
		position = pos;
		normal = norm;
		texture = text;
		tangent = tan;
	}
};

// ----------------------------------------------------------------------------

#endif // VERTEXFORMAT_H

