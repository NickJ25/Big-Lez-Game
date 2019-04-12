#include "AnimMesh.h"

AnimMesh::AnimMesh(vector<AnimVertex> vertic, vector<GLuint> ind, vector<AnimTexture> textur, vector<VertexBoneData> bone_id_weights)
{
	//set up all the data in the mesh
	vertices = vertic;
	indices = ind;
	textures = textur;
	bones_id_weights_for_each_vertex = bone_id_weights;

	//set the vertex buffers and its attribute pointers.
	SetupMesh();
}


AnimMesh::~AnimMesh()
{
	//delete all the buffers passing information to the shaders
	glDeleteBuffers(1, &VBO_vertices);
	glDeleteBuffers(1, &VBO_bones);
	glDeleteBuffers(1, &EBO_indices);
	glDeleteVertexArrays(1, &VAO);
}

void VertexBoneData::addBoneData(uint bone_id, float weight)
{
	//cycle through the bones getting their ID's and weights
	for (uint i = 0; i < NUM_BONES_PER_VEREX; i++)
	{
		if (weights[i] == 0.0)
		{
			ids[i] = bone_id;
			weights[i] = weight;
			return;
		}
	}
}

void AnimMesh::Draw(GLuint shaders_program)
{
	//set to 1 for now
	int diffuse_nr = 1;
	int specular_nr = 1;

	//cycle through all the textures of the mesh
	for (int i = 0; i < textures.size(); i++)
	{
		//activate each mesh
		glActiveTexture(GL_TEXTURE0 + i);

		//assign the diffuse and specular textures if they are applicable
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
		{
			number = to_string(diffuse_nr++);
		}
		else if (name == "texture_specular")
		{
			number = to_string(specular_nr++);
		}

		//bind this texture and pass it to the shader
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
		glUniform1i(glGetUniformLocation(shaders_program, ("material." + name + number).c_str()), i);
	}

	//Draw the arrays of vertices via its indices
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	for (int i = 0; i < textures.size(); i++)
	{
		//unbind everything by attaching it to 0
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void AnimMesh::SetupMesh()
{
	//vertices data
	glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bones data
	glGenBuffers(1, &VBO_bones);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	glBufferData(GL_ARRAY_BUFFER, bones_id_weights_for_each_vertex.size() * sizeof(bones_id_weights_for_each_vertex[0]), &bones_id_weights_for_each_vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//numbers for sequence indices
	glGenBuffers(1, &EBO_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// create VAO and binding data from buffers to shaders
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);

	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (GLvoid*)0);
	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (GLvoid*)offsetof(AnimVertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (GLvoid*)offsetof(AnimVertex, text_coords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//bones
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (GLvoid*)0); // for INT Ipointer
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (GLvoid*)offsetof(VertexBoneData, weights));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_indices);
	glBindVertexArray(0);
}