#include "MeshManager.h"

#include "Triangle.h"
#include "Quad.h"
#include "ShaderMan.h"
#include "CameraEuler.h"

// ----------------------------------------------------------------------------

std::map<std::string, IObject*> MeshManager::m_MeshList;

// ----------------------------------------------------------------------------

MeshManager::MeshManager()
{
	// Create quad mesh
	Quad* quad = new Quad();
	quad->SetProgram(ShaderMan::GetShader("SolidColorQuadShader"));
	quad->Create();
	m_MeshList["quad1"] = quad;

	// Create triangle mesh
	Triangle* triangle = new Triangle();
	triangle->SetProgram(ShaderMan::GetShader("SolidColorTriangleShader"));
	triangle->Create();
	m_MeshList["triangle1"] = triangle;
}

// ----------------------------------------------------------------------------

MeshManager::~MeshManager()
{
	for (auto& mesh : m_MeshList)
	{
		delete mesh.second;
	}

	// Clear the map
	m_MeshList.clear();
}

// ----------------------------------------------------------------------------

void MeshManager::Draw(CameraEuler* camera)
{
	for (auto& mesh : m_MeshList)
	{
		mesh.second->Draw(camera);
	}
}

// ----------------------------------------------------------------------------

void MeshManager::Update(double dt)
{
	for (auto& mesh : m_MeshList)
	{
		mesh.second->Update(dt);
	}
}

// ----------------------------------------------------------------------------

void MeshManager::DeleteMesh(const std::string& meshName)
{
	// Get a reference to the mesh that is going to be deleted
	IObject* mesh = m_MeshList[meshName];
	
	// Destroy mesh
	mesh->Destroy();
	
	// Remove entry from map
	m_MeshList.erase(meshName);
}

// ----------------------------------------------------------------------------

const IObject& MeshManager::GetMesh(const std::string& meshName) const
{
	return *m_MeshList[meshName];
}

// ----------------------------------------------------------------------------
