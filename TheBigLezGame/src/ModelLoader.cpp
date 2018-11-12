//#include "ModelLoader.h"
//
//void ModelLoader::loadModel(string path)
//{
//	// Read file via ASSIMP
//	Assimp::Importer importer;
//	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	// Check for errors
//	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
//	{
//		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
//		return;
//	}
//	// Retrieve the directory path of the filepath
//	this->directory = path.substr(0, path.find_last_of('/'));
//
//	// Process ASSIMP's root node recursively
//	this->processNode(scene->mRootNode, scene);
//}
//
//void ModelLoader::loadAnimatedModel(const string & path)
//{
//	scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		cout << "error assimp : " << import.GetErrorString() << endl;
//		return;
//	}
//	m_global_inverse_transform = scene->mRootNode->mTransformation;
//	m_global_inverse_transform.Inverse();
//
//	if (scene->mAnimations[0]->mTicksPerSecond != 0.0)
//	{
//		ticks_per_second = scene->mAnimations[0]->mTicksPerSecond;
//	}
//	else
//	{
//		ticks_per_second = 25.0f;
//	}
//
//	// directoru = container for model.obj and textures and other files
//	directory = path.substr(0, path.find_last_of('/'));
//
//	cout << "scene->HasAnimations() 1: " << scene->HasAnimations() << endl;
//	cout << "scene->mNumMeshes 1: " << scene->mNumMeshes << endl;
//	cout << "scene->mAnimations[0]->mNumChannels 1: " << scene->mAnimations[0]->mNumChannels << endl;
//	cout << "scene->mAnimations[0]->mDuration 1: " << scene->mAnimations[0]->mDuration << endl;
//	cout << "scene->mAnimations[0]->mTicksPerSecond 1: " << scene->mAnimations[0]->mTicksPerSecond << endl << endl;
//
//	cout << "		name nodes : " << endl;
//	showNodeName(scene->mRootNode);
//	cout << endl;
//
//	cout << "		name bones : " << endl;
//	processNode(scene->mRootNode, scene);
//
//	cout << "		name nodes animation : " << endl;
//	for (uint i = 0; i < scene->mAnimations[0]->mNumChannels; i++)
//	{
//		cout << scene->mAnimations[0]->mChannels[i]->mNodeName.C_Str() << endl;
//	}
//	cout << endl;
//}
