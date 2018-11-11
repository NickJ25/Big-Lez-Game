#include "RenderComponent.h"

// Load Standard Object
void RenderComponent::loadObject(const char* mesh_filename)
{
	string path = mesh_filename;
	// Read file via ASSIMP
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(mesh_filename, aiProcess_Triangulate | aiProcess_FlipUVs);

	// Check for errors
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}
	// Retrieve the directory path of the filepath
	this->directory = path.substr(0, path.find_last_of('/'));

	// Process ASSIMP's root node recursively
	//this->processNode(scene->mRootNode, scene);

}

// Load Animated Object
void RenderComponent::loadAnimObject(const char* mesh_filename)
{

}


void RenderComponent::depthMask(GLboolean mode)
{
	m_depthMask = mode;
}

void RenderComponent::cullFace(GLenum mode)
{
	m_cullMode = mode;
}

void RenderComponent::changeShader(Shader* newShader)
{
	m_currentShader = newShader;
}

void RenderComponent::Draw()
{
	// Select Modes
	glCullFace(m_cullMode);
	glDepthMask(m_depthMask);
	glUseProgram(m_currentShader->getID());

	// Do Transformations

	// DRAW

	// Repeat
}
