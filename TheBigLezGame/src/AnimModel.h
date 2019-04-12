#ifndef ANIMMODEL
#define ANIMMODEL

#include "GL\glew.h"
#include "AnimMesh.h"
//GLFW
#include "GLFW/glfw3.h"

//std library
#include <vector>
#include <string>
#include <map>

//glm
#include "glm\gtc\quaternion.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//assimp
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

using namespace std;

class AnimModel
{
public:
	//constructor/destructor
	AnimModel();
	~AnimModel();

	//constant for all models (most have no more than 20)
	static const uint MAX_BONES = 100;


	void initShaders(GLuint shader_program);
	void loadModel(const string& path);
	void update();
	void draw(GLuint shaders_program, bool isAnimated);
	void showNodeName(aiNode* node);

	//load textures
	GLuint TextureFromFile(const char * path);

	//utility functions
	glm::mat4 aiToGlm(aiMatrix4x4 ai_matr);
	aiQuaternion nlerp(aiQuaternion a, aiQuaternion b, float blend); 

	//set start and end points of animation to be used (for collada files)
	void setAnimation(float s, float e);
	
	//utility functions to pause animations
	void setPaused(bool p);
	bool getPaused();

	//pause animation without explicitly setting the game to paused (for deaths)
	void setStill(bool s);
	void setPauseFrame(float p);

private:

	//assimp variables and objects
	Assimp::Importer import;
	const aiScene* scene;
	vector<AnimMesh> meshes;
	string directory;

	//bone variables
	map<string, uint> m_bone_mapping; 
	uint m_num_bones = 0;
	vector<BoneMatrix> m_bone_matrices;
	aiMatrix4x4 m_global_inverse_transform;

	GLuint m_bone_location[MAX_BONES];
	float ticks_per_second = 0.0f;

	//setup functions
	void processNode(aiNode* node, const aiScene* scene);
	AnimMesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<AnimTexture> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, string type_name);

	//update functions
	uint findPosition(float p_animation_time, const aiNodeAnim* p_node_anim);
	uint findRotation(float p_animation_time, const aiNodeAnim* p_node_anim);
	uint findScaling(float p_animation_time, const aiNodeAnim* p_node_anim);

	const aiNodeAnim* findNodeAnim(const aiAnimation* p_animation, const string p_node_name);

	// calculate transform matrix
	aiVector3D calcInterpolatedPosition(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiQuaternion calcInterpolatedRotation(float p_animation_time, const aiNodeAnim* p_node_anim);
	aiVector3D calcInterpolatedScaling(float p_animation_time, const aiNodeAnim* p_node_anim);

	//animation control and update functionality
	void readNodeHierarchy(float p_animation_time, const aiNode* p_node, const aiMatrix4x4 parent_transform);
	void boneTransform(double time_in_sec, vector<aiMatrix4x4>& transforms);

	//default animation frames run from start to finish
	float animStart = 0.0;
	float animEnd = 1.0;

	//pause variables
	bool paused = false;
	double pauseFrame;
	bool pauseFrameSet = false;
	float pauseAnim = 0.0f;

	//stillness variable
	bool still = false;
};

#endif