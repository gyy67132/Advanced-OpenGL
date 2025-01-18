#pragma once

#include "Mesh.h"

#include "Assimp/Importer.hpp"
#include "Assimp/scene.h"
#include "Assimp/postprocess.h"
#include "Utils.h"

class Model
{
public:
	Model(const char *path)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	vector<Mesh> meshes;
	std::string directory;
	vector<Texture> textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode*node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
};