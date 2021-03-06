﻿#include "AnimModel.h"

//for texture loading
#include "SOIL2\SOIL2.h"

AnimModel::AnimModel()
{
	//initialise the scene pointer
	scene = nullptr;
}


AnimModel::~AnimModel()
{
	//release the memory containing the model
	import.FreeScene();
}

void AnimModel::initShaders(GLuint shader_program)
{
	//cycle through the bones and send their details to the shader
	for (uint i = 0; i < MAX_BONES; i++) 
	{
		string name = "bones[" + to_string(i) + "]";
		m_bone_location[i] = glGetUniformLocation(shader_program, name.c_str());
	}
}

void AnimModel::update()
{
	//empty, but can be used for moving individual bones
}

void AnimModel::setStill(bool s)
{
	still = s;
}

void AnimModel::setPauseFrame(float p)
{
	pauseAnim = p;
}

void AnimModel::draw(GLuint shaders_program, bool isAnimated)
{
	//create an empty vector of matrices to hold the transforms
	vector<aiMatrix4x4> transforms;

	//if the model is not paused or dead
	if (paused == false && still == false) {
		pauseFrame = false;
		//update normally using the timer
		boneTransform((double)glfwGetTime(), transforms);
	}
	else {
		//pause the model with a specific frame specified by the programmer
	if (pauseFrameSet == false)
		pauseFrame = (double)glfwGetTime();
		boneTransform(pauseAnim, transforms);
		pauseFrameSet = true;
	}

	// move all matrices for actual model position to shader
	for (uint i = 0; i < transforms.size(); i++) 
	{
		glUniformMatrix4fv(m_bone_location[i], 1, GL_TRUE, (const GLfloat*)&transforms[i]);
	}

	//cycle through and draw all the meshes
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shaders_program);
	}
}

void AnimModel::loadModel(const string& path)
{
	//import the file and load it into the scene pointer
	scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	//error check
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "error assimp : " << import.GetErrorString() << endl;
		return;
	}

	m_global_inverse_transform = scene->mRootNode->mTransformation;
	m_global_inverse_transform.Inverse();

	//if the file specifies its framerate
	if (scene->mAnimations[0]->mTicksPerSecond != 0.0)
	{
		ticks_per_second = scene->mAnimations[0]->mTicksPerSecond;
	}
	else
	{
		ticks_per_second = 24.0f;
	}

	// directory = container for model and textures and other files
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);

}

void AnimModel::showNodeName(aiNode* node)
{
	//utility function for finding nodes
	for (uint i = 0; i < node->mNumChildren; i++)
	{
		showNodeName(node->mChildren[i]);
	}
}

void AnimModel::processNode(aiNode* node, const aiScene* scene)
{
	//process the mesh
	AnimMesh mesh;
	for (uint i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* ai_mesh = scene->mMeshes[i];
		mesh = processMesh(ai_mesh, scene);
		mesh = processMesh(ai_mesh, scene);
		meshes.push_back(mesh); //accumulate all meshes in one vector
	}

}

AnimMesh AnimModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
	//create an anim mesh for the anim model

	//temporary storage
	vector<AnimVertex> vertices;
	vector<GLuint> indices;
	vector<AnimTexture> textures;
	vector<VertexBoneData> bones_id_weights_for_each_vertex;

	vertices.reserve(mesh->mNumVertices); 
	indices.reserve(mesh->mNumVertices); 

	bones_id_weights_for_each_vertex.resize(mesh->mNumVertices);

	//vertices
	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		AnimVertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = vector;

		if (mesh->mNormals != NULL)
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
		}
		else
		{
			vertex.normal = glm::vec3();
		}


		// in assimp model can have 8 different texture coordinates
		// we only care about the first set of texture coordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.text_coords = vec;
		}
		else
		{
			vertex.text_coords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	//indices
	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i]; 
		indices.push_back(face.mIndices[0]); 
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	//material
	if (mesh->mMaterialIndex >= 0)
	{
		//all pointers created in assimp will be deleted automaticaly when we call import.FreeScene();
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		vector<AnimTexture> diffuse_maps = LoadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		bool exist = false;
		for (int i = 0; (i < textures.size()) && (diffuse_maps.size() != 0); i++)
		{
			if (textures[i].path == diffuse_maps[0].path)
			{
				exist = true;
			}
		}
		if (!exist && diffuse_maps.size() != 0) textures.push_back(diffuse_maps[0]);

		vector<AnimTexture> specular_maps = LoadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
		exist = false;
		for (int i = 0; (i < textures.size()) && (specular_maps.size() != 0); i++)
		{
			if (textures[i].path == specular_maps[0].path)
			{
				exist = true;
			}
		}
		if (!exist  && specular_maps.size() != 0) textures.push_back(specular_maps[0]);

	}

	// load bones
	for (uint i = 0; i < mesh->mNumBones; i++)
	{
		uint bone_index = 0;
		string bone_name(mesh->mBones[i]->mName.data);


		if (m_bone_mapping.find(bone_name) == m_bone_mapping.end())
		{
			// Allocate an index for a new bone
			bone_index = m_num_bones;
			m_num_bones++;
			BoneMatrix bi;
			m_bone_matrices.push_back(bi);
			m_bone_matrices[bone_index].offset_matrix = mesh->mBones[i]->mOffsetMatrix;
			m_bone_mapping[bone_name] = bone_index;

		}
		else
		{
			bone_index = m_bone_mapping[bone_name];
		}

		for (uint j = 0; j < mesh->mBones[i]->mNumWeights; j++)
		{
			uint vertex_id = mesh->mBones[i]->mWeights[j].mVertexId;
			float weight = mesh->mBones[i]->mWeights[j].mWeight;
			bones_id_weights_for_each_vertex[vertex_id].addBoneData(bone_index, weight);
		}
	}

	return AnimMesh(vertices, indices, textures, bones_id_weights_for_each_vertex);
}

vector<AnimTexture> AnimModel::LoadMaterialTexture(aiMaterial* mat, aiTextureType type, string type_name)
{
	//load the textures using assimp and add them to the textures vector
	vector<AnimTexture> textures;
	for (uint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString ai_str;
		mat->GetTexture(type, i, &ai_str);

		string filename = string(ai_str.C_Str());
		filename = directory + '/' + filename;

		AnimTexture texture;
		texture.id = TextureFromFile(filename.c_str()); // return prepaired openGL texture
		texture.type = type_name;
		texture.path = ai_str;
		textures.push_back(texture);
	}
	return textures;
}

uint AnimModel::findPosition(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	//cycle through each node for its position
	for (uint i = 0; i < p_node_anim->mNumPositionKeys - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->mPositionKeys[i + 1].mTime)
		{
			return i;
		}
	}
	//make sure the model has a frame 0 animation
	assert(0);
	return 0;
}

uint AnimModel::findRotation(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	//the same for rotation....
	for (uint i = 0; i < p_node_anim->mNumRotationKeys - 1; i++)
	{
		if (p_animation_time < (float)p_node_anim->mRotationKeys[i + 1].mTime)
		{
			return i;
		}
	}
	//make sure the model has a frame 0 animation
	assert(0);
	return 0;
}

uint AnimModel::findScaling(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	//and finally scaling
	for (uint i = 0; i < p_node_anim->mNumScalingKeys - 1; i++)
	{
		if ( p_animation_time < (float)p_node_anim->mScalingKeys[i + 1].mTime)
		{
			return i;
		}
	}
	//make sure the model has a frame 0 animation
	assert(0);
	return 0;
}

aiVector3D AnimModel::calcInterpolatedPosition(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	if (p_node_anim->mNumPositionKeys == 1)
	{
		return p_node_anim->mPositionKeys[0].mValue;
	}
	//get the frame to find the position for
	double time_in_ticks = (double)glfwGetTime() * ticks_per_second;
	uint position_index;
	//find the position
	position_index = findPosition(p_animation_time, p_node_anim);
	//set the next position to find
	uint next_position_index = position_index + 1;
	//make sure the next index to check isn't out of bounds
	assert(next_position_index < p_node_anim->mNumPositionKeys);
	float delta_time = (float)(p_node_anim->mPositionKeys[next_position_index].mTime - p_node_anim->mPositionKeys[position_index].mTime);

	float  factor = ((p_animation_time)-(float)p_node_anim->mPositionKeys[position_index].mTime) / delta_time;
	assert(factor >= 0.0f && factor <= 1.0f);
	//find the delta
	aiVector3D start = p_node_anim->mPositionKeys[position_index].mValue;
	aiVector3D end = p_node_anim->mPositionKeys[next_position_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

aiQuaternion AnimModel::calcInterpolatedRotation(float p_animation_time, const aiNodeAnim* p_node_anim)
{
	if (p_node_anim->mNumRotationKeys == 1)
	{
		return p_node_anim->mRotationKeys[0].mValue;
	}
	uint rotation_index;
	//find the current roation
	rotation_index = findRotation(p_animation_time, p_node_anim);

	//check the next index isn't out of bounds
	uint next_rotation_index = rotation_index + 1;
	assert(next_rotation_index < p_node_anim->mNumRotationKeys);

	float delta_time = (float)(p_node_anim->mRotationKeys[next_rotation_index].mTime - p_node_anim->mRotationKeys[rotation_index].mTime);

	float  factor = ((p_animation_time)-(float)p_node_anim->mRotationKeys[rotation_index].mTime) / delta_time;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiQuaternion start_quat = p_node_anim->mRotationKeys[rotation_index].mValue;
	aiQuaternion end_quat = p_node_anim->mRotationKeys[next_rotation_index].mValue;

	return nlerp(start_quat, end_quat, factor);
}

aiVector3D AnimModel::calcInterpolatedScaling(float p_animation_time, const aiNodeAnim* p_node_anim)
{

	if (p_node_anim->mNumScalingKeys == 1)
	{
		return p_node_anim->mScalingKeys[0].mValue;
	}

	uint scaling_index;
	//find the scaling
	scaling_index = findScaling(p_animation_time, p_node_anim);
	//find and check the next scaling index
	uint next_scaling_index = scaling_index + 1; 
	assert(next_scaling_index < p_node_anim->mNumScalingKeys);
	float delta_time = (float)(p_node_anim->mScalingKeys[next_scaling_index].mTime - p_node_anim->mScalingKeys[scaling_index].mTime);
	float  factor = ((p_animation_time) - (float)p_node_anim->mScalingKeys[scaling_index].mTime) / delta_time;
	assert(factor >= 0.0f && factor <= 1.0f);
	//find the delta
	aiVector3D start = p_node_anim->mScalingKeys[scaling_index].mValue;
	aiVector3D end = p_node_anim->mScalingKeys[next_scaling_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

const aiNodeAnim * AnimModel::findNodeAnim(const aiAnimation * p_animation, const string p_node_name)
{
	// channel in animation contains aiNodeAnim (aiNodeAnim its transformation for bones)
	for (uint i = 0; i < p_animation->mNumChannels; i++)
	{
		const aiNodeAnim* node_anim = p_animation->mChannels[i];
		if (string(node_anim->mNodeName.data) == p_node_name)
		{
			return node_anim;
		}
	}

	return nullptr;
}

// start from RootNode, animation controller
void AnimModel::readNodeHierarchy(float p_animation_time, const aiNode* p_node, const aiMatrix4x4 parent_transform)
{

	string node_name(p_node->mName.data);

	const aiAnimation* animation = scene->mAnimations[0];
	aiMatrix4x4 node_transform = p_node->mTransformation;

	const aiNodeAnim* node_anim = findNodeAnim(animation, node_name);

	if (node_anim)
	{

		//scaling
		aiVector3D scaling_vector = calcInterpolatedScaling(p_animation_time, node_anim);
		aiMatrix4x4 scaling_matr;
		aiMatrix4x4::Scaling(scaling_vector, scaling_matr);

		//rotation
		aiQuaternion rotate_quat = calcInterpolatedRotation(p_animation_time, node_anim);
		aiMatrix4x4 rotate_matr = aiMatrix4x4(rotate_quat.GetMatrix());

		//translation
		aiVector3D translate_vector = calcInterpolatedPosition(p_animation_time, node_anim);
		aiMatrix4x4 translate_matr;
		aiMatrix4x4::Translation(translate_vector, translate_matr);

		node_transform = translate_matr * rotate_matr * scaling_matr;

	}

	aiMatrix4x4 global_transform = parent_transform * node_transform;

	if (m_bone_mapping.find(node_name) != m_bone_mapping.end()) // true if node_name exist in bone_mapping
	{
		uint bone_index = m_bone_mapping[node_name];
		m_bone_matrices[bone_index].final_world_transform = m_global_inverse_transform * global_transform * m_bone_matrices[bone_index].offset_matrix;
	}

	for (uint i = 0; i < p_node->mNumChildren; i++)
	{
		readNodeHierarchy(p_animation_time, p_node->mChildren[i], global_transform);
	}

}

void AnimModel::setAnimation(float s, float e)
{
	animStart = s;
	animEnd = e;

}

void AnimModel::boneTransform(double time_in_sec, vector<aiMatrix4x4>& transforms)
{

		aiMatrix4x4 identity_matrix;
		//get the time in ticks
		double time_in_ticks = time_in_sec * ticks_per_second;
		//get the floating point modulus of the current time and the size of the animation as specified by the end point
		float animation_time = fmod(time_in_ticks, scene->mAnimations[0]->mDuration / animEnd);
		//compensate for the starting frame by removing animStart
		float animation_size = (scene->mAnimations[0]->mDuration / animEnd) - animStart;

		//loop to keep playing the same selected section of animation
		if (animation_time < animStart)
			animation_time += animStart;
		while (animation_time > animation_size + animStart) {
			float difference = animation_time - (animation_size + animStart);
			animation_time = animStart + difference;
		}
		//read the nodes
		readNodeHierarchy(animation_time, scene->mRootNode, identity_matrix);
		transforms.resize(m_num_bones);
		//apply the transformations
		for (uint i = 0; i < m_num_bones; i++)
		{
			transforms[i] = m_bone_matrices[i].final_world_transform;
		}
}

glm::mat4 AnimModel::aiToGlm(aiMatrix4x4 ai_matr)
{
	//simple function to set ai matrices to glm ones
	glm::mat4 result;
	result[0].x = ai_matr.a1; result[0].y = ai_matr.b1; result[0].z = ai_matr.c1; result[0].w = ai_matr.d1;
	result[1].x = ai_matr.a2; result[1].y = ai_matr.b2; result[1].z = ai_matr.c2; result[1].w = ai_matr.d2;
	result[2].x = ai_matr.a3; result[2].y = ai_matr.b3; result[2].z = ai_matr.c3; result[2].w = ai_matr.d3;
	result[3].x = ai_matr.a4; result[3].y = ai_matr.b4; result[3].z = ai_matr.c4; result[3].w = ai_matr.d4;


	return result;
}

aiQuaternion AnimModel::nlerp(aiQuaternion a, aiQuaternion b, float blend)
{
	//create an interpolated quaternion to describe the rotatation at any given point
	a.Normalize();
	b.Normalize();

	aiQuaternion result;
	float dot_product = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	float one_minus_blend = 1.0f - blend;

	if (dot_product < 0.0f)
	{
		result.x = a.x * one_minus_blend + blend * -b.x;
		result.y = a.y * one_minus_blend + blend * -b.y;
		result.z = a.z * one_minus_blend + blend * -b.z;
		result.w = a.w * one_minus_blend + blend * -b.w;
	}
	else
	{
		result.x = a.x * one_minus_blend + blend * b.x;
		result.y = a.y * one_minus_blend + blend * b.y;
		result.z = a.z * one_minus_blend + blend * b.z;
		result.w = a.w * one_minus_blend + blend * b.w;
	}

	return result.Normalize();
}


GLuint AnimModel::TextureFromFile(const char *path)
{
	//Generate texture ID and load texture data
	string filename = string(path);
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;

	unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return textureID;
}

void AnimModel::setPaused(bool p)
{
	paused = p;
}

bool AnimModel::getPaused()
{
	return paused;
}

