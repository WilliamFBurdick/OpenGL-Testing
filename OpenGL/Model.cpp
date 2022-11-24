#include "Model.h"
#include <memory>

void Model::Draw(std::unique_ptr<Shader> shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++) meshes[i].Draw(shader);
}