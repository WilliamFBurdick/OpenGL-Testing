#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	class TestLighting : public Test {
	public:
		TestLighting();
		~TestLighting();

		void OnUpdate(float deltaTime, GLFWwindow* window = NULL) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void OnMouseMovement(float xOffset, float yOffset) override;
	private:

		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexArray> m_LightVAO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_ObjectShader;
		std::unique_ptr<Shader> m_LightShader;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Texture> m_DiffuseTexture;
		std::unique_ptr<Texture> m_SpecularTexture;


		glm::mat4 m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		std::vector<glm::vec3> m_Translations;
		float m_uColor[4] = { 0.8f, 0.3f, 0.8f, 1.0f };

		glm::vec3 m_CubePositions[10] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glm::vec3 m_PointLightPositions[4] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};

		// Camera members
		glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		float mouseSensitivity = 0.1f;

		// Camera rotation
		float pitch = 0.0f;
		float yaw = -90.0f;

		// Light source members
		glm::vec3 m_LightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	};
}