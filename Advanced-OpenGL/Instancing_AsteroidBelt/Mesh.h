#pragma once

#include "Utils.h"
#include "Shader.h"

using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	//Êý¾Ý
	vector<Vertex> vertices;
	vector<unsigned int >indices;
	vector<Texture> textures;
	//
	Mesh(vector<Vertex> vertices, vector<unsigned int >indices, vector<Texture> textures);
	void draw(Shader shader);
	unsigned int VAO, VBO, EBO;
private:
	//
	void setupMesh();

};

