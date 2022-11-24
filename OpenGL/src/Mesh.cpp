#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	:vertices(vertices), indices(indices), textures(textures)
{
	SetupMesh();
}

void Mesh::SetupMesh()
{
	VAO = std::make_unique<VertexArray>();
	VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	IBO = std::make_unique<IndexBuffer>();

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	VAO->AddBuffer(*VBO, layout);
	VAO->Bind();
}

void Mesh::Draw(std::unique_ptr<Shader> shader)
{
	unsigned int diffuseCount = 1;
	unsigned int specularCount = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + i));
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse") number = std::to_string(diffuseCount++);
		else if (name == "texture_specular") number = std::to_string(specularCount++);
		shader->SetUniform1i(("material." + name + number).c_str(), i);
	}
	GLCall(glActiveTexture(GL_TEXTURE0));

	VAO->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	VAO->Unbind();
}