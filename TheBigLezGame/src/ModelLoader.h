//#pragma once
//#include <string>
//#include <iostream>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <vector>
//#include <map>
//#include "glm\gtc\quaternion.hpp"
//
//using namespace std;
//
//class ModelLoader
//{
//private:
//	// Model Data
//	vector<Mesh> meshes;
//	string directory;
//	vector<Texture> textures_loaded;
//
//	// Animated Model Data
//	static const uint MAX_BONES = 100;
//
//	map<string, uint> m_bone_mapping; // maps a bone name and their index
//	uint m_num_bones = 0;
//	vector<BoneMatrix> m_bone_matrices;
//	aiMatrix4x4 m_global_inverse_transform;
//
//	GLuint m_bone_location[MAX_BONES];
//	float ticks_per_second = 0.0f;
//
//public:
//	// Standard Model Class
//	void loadModel(string path);
//	void processNode(aiNode* node, const aiScene* scene);
//	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
//	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
//	GLint TextureFromFile(const char *path, string directory);
//
//	// Animated Model Classes
//	void ModelLoader::loadAnimatedModel(const string & path);
//
//};