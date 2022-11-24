#pragma once
#include <Mesh.h>
#include "assimp/scene.h"

class Model
{
public:
	Model(char* path)
	{
		loadModel(path);
	}
	void Draw(std::unique_ptr<Shader> shader);
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

