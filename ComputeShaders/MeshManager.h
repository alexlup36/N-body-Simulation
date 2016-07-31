#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <GL\glew.h>
#include <gl\GLU.h>

#include <map>
#include <vector>

#include "VertexFormat.h"
#include "IObject.h"

class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	void Draw(CameraEuler* camera);
	void Update(double dt);
	void DeleteMesh(const std::string& meshName);
	const IObject& GetMesh(const std::string& meshName) const;

private:
	static std::map<std::string, IObject*> m_MeshList;
};

#endif // MESHMANAGER_H