#ifndef ANIMMESH
#define ANIMMESH

//std library
#include <iostream>
#include <vector>
#include <string>

//glew
#include "GL\glew.h"
//glm
#include "glm\glm.hpp"
//assimp
#include "assimp\Importer.hpp"

using namespace std;
typedef unsigned int uint;
#define NUM_BONES_PER_VEREX 4

//struct for containing vertex information to pass to the shader
struct AnimVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 text_coords;
};
//similar struct containing information for the texture co-ordinates
struct AnimTexture
{
	GLuint id;
	string type;
	aiString path;
};

//bone information for use during updates in the shader
struct BoneMatrix
{
	aiMatrix4x4 offset_matrix;
	aiMatrix4x4 final_world_transform;
};

//struct to contain bone data
struct VertexBoneData
{
	uint ids[NUM_BONES_PER_VEREX];
	float weights[NUM_BONES_PER_VEREX];

	VertexBoneData()
	{
		memset(ids, 0, sizeof(ids)); 
		memset(weights, 0, sizeof(weights));
	}

	void addBoneData(uint bone_id, float weight);
};

class AnimMesh
{
public:
	//constructors/destructor
	AnimMesh(vector<AnimVertex> vertic, vector<GLuint> ind, vector<AnimTexture> textur, vector<VertexBoneData> bone_id_weights);
	AnimMesh() {};
	~AnimMesh();

	// Render mesh
	void Draw(GLuint shaders_program);

private:
	//Mesh data
	vector<AnimVertex> vertices;
	vector<GLuint> indices;
	vector<AnimTexture> textures;
	vector<VertexBoneData> bones_id_weights_for_each_vertex;

	//buffers
	GLuint VAO;
	GLuint VBO_vertices;
	GLuint VBO_bones;
	GLuint EBO_indices;

	//inititalize buffers
	void SetupMesh();
};

#endif // !MESH