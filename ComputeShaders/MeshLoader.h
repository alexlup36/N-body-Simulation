#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <string>

// Assimp
#include <scene.h>

class MeshLoader
{
public:
	MeshLoader(const std::string& file);
	~MeshLoader();

private:
	void loadScene(const aiScene* scene);

	std::string m_sFileName;
};

#endif // MESHLOADER_H