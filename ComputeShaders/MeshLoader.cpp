#include "MeshLoader.h"

// Assimp
#include <Importer.hpp>
#include <postprocess.h>

#include <vector>

#include "Common.h"
#include "VertexFormat.h"
#include "Texture.h"

// ----------------------------------------------------------------------------

MeshLoader::MeshLoader(const std::string& file)
{
	m_sFileName = file;

	printf("Loading mesh: %s\n", file.c_str());

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file,
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace);
	if (scene == NULL)
	{
		printf("Failed to load mesh: %s\n", file.c_str());
	}
	else
	{
		loadScene(scene);
	}
}

// ----------------------------------------------------------------------------

MeshLoader::~MeshLoader()
{
}

// ----------------------------------------------------------------------------

void MeshLoader::loadScene(const aiScene* scene)
{
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
	{
		// Get current mesh
		const aiMesh* currentMesh = scene->mMeshes[i];

		std::vector<VertexPNTT> verticesList;
		std::vector<GLuint> indicesList;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);

		// Go through the vertices of the current mesh
		for (unsigned int vertexIndex = 0; vertexIndex < currentMesh->mNumVertices; ++vertexIndex)
		{
			// Retrieve the data from the model - position, normal, texture coordinates and tangent
			const aiVector3D* position = &currentMesh->mVertices[vertexIndex];
			const aiVector3D* normal = &currentMesh->mNormals[vertexIndex];
			const aiVector3D* texture = currentMesh->HasTextureCoords(0) ? &(currentMesh->mTextureCoords[0][vertexIndex]) : &aiZeroVector;
			const aiVector3D* tangent = currentMesh->HasTangentsAndBitangents() ? &(currentMesh->mTangents[vertexIndex]) : &aiZeroVector;

			// Create the vertex
			VertexPNTT newVertex(glm::vec3(position->x, position->y, position->z),
				glm::vec3(normal->x, normal->y, normal->z),
				glm::vec2(texture->x, texture->y),
				glm::vec3(tangent->x, tangent->y, tangent->z));

			// Add new vertex to the list of vertices
			verticesList.push_back(newVertex);
		}

		// Go through the indices of the current mesh
		for (unsigned int indexIndex = 0; indexIndex < currentMesh->mNumFaces; ++indexIndex)
		{
			// Get the current face
			const aiFace& currentFace = currentMesh->mFaces[indexIndex];

			// Add the indices to our list of indices
			indicesList.push_back(currentFace.mIndices[0]);
			indicesList.push_back(currentFace.mIndices[1]);
			indicesList.push_back(currentFace.mIndices[2]);
		}

		// Get the current matterial
		const aiMaterial* material = scene->mMaterials[currentMesh->mMaterialIndex];

		// Texture references
		Texture* diffuseTexture = NULL;
		Texture* normalTexture = NULL;
		Texture* specularTexture = NULL;
		Texture* displacementTexture = NULL;

		aiString texturePath;

		// Diffuse texture
		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				diffuseTexture = new Texture(texturePath.data, TextureType::Diffuse, true, true, GL_TEXTURE_2D, GL_LINEAR);
			}
		}

		// Normal texture
		if (material->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			if (material->GetTexture(aiTextureType_NORMALS, 0, &texturePath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				normalTexture = new Texture(texturePath.data, TextureType::Normal, true, true, GL_TEXTURE_2D, GL_LINEAR);
			}
		}

		// Specular texture
		if (material->GetTextureCount(aiTextureType_SPECULAR) > 0)
		{
			if (material->GetTexture(aiTextureType_SPECULAR, 0, &texturePath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				specularTexture = new Texture(texturePath.data, TextureType::Specular, true, true, GL_TEXTURE_2D, GL_LINEAR);
			}
		}

		// Displacement texture
		if (material->GetTextureCount(aiTextureType_DISPLACEMENT) > 0)
		{
			if (material->GetTexture(aiTextureType_DISPLACEMENT, 0, &texturePath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				displacementTexture = new Texture(texturePath.data, TextureType::Displacement, true, true, GL_TEXTURE_2D, GL_LINEAR);
			}
		}
	}
}

// ----------------------------------------------------------------------------