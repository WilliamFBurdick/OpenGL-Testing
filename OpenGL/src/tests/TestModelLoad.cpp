#include "TestLighting.h"

#include "Renderer.h"
#include "imgui/imgui.h"
#include <sstream>
#include "GLFW/glfw3.h"

namespace test {
	TestLighting::TestLighting()
	{
		m_ObjectShader = std::make_unique<Shader>("res/shaders/BasicLighting.shader");
		m_LightShader = std::make_unique<Shader>("res/shaders/BasicLightingSource.shader");
		m_DiffuseTexture = std::make_unique<Texture>("res/textures/container2.png");
		m_DiffuseTexture->Bind(0);
		m_SpecularTexture = std::make_unique<Texture>("res/textures/container2_specular.png");
		m_SpecularTexture->Bind(1);

		/* Positions: <x, y, z>	 Normal Direction: <x, y, z> Texture Coordinates: <s, t>  */
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VAO = std::make_unique<VertexArray>();

		m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_LightVAO = std::make_unique<VertexArray>();
		m_LightVAO->AddBuffer(*m_VBO, layout);
		m_LightVAO->Bind();
		m_VBO->Bind();
	}

	TestLighting::~TestLighting()
	{
	}

	bool mouseToggled = false;
	bool setup = false;
	void TestLighting::OnUpdate(float deltaTime, GLFWwindow* window)
	{
		if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED && !setup)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			setup = true;
		}
		float cameraSpeed = 2.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) m_CameraPos += cameraSpeed * m_CameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) m_CameraPos -= cameraSpeed * m_CameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * cameraSpeed;

		// toggle mouse visibility with F2
		bool currentToggleMouse = glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS;
		if (currentToggleMouse && !mouseToggled)
		{
			if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
			{
				GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
			}
			else
			{
				GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
			}
		}
		mouseToggled = currentToggleMouse;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		m_CameraFront = glm::normalize(direction);

		/*
		m_LightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		m_LightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
		
		m_ObjectShader->Bind();
		m_ObjectShader->SetUniformVec3("light.ambient", ambientColor);
		m_ObjectShader->SetUniformVec3("light.diffuse", diffuseColor);
		*/
	}

	void TestLighting::OnMouseMovement(float xOffset, float yOffset)
	{
		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		if (pitch > 89.0f) pitch = 89.0f;
		if (pitch < -89.0f) pitch = -89.0f;
	}


	void TestLighting::OnRender()
	{
		GLCall(glClearColor(0, 0, 0, 0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_DiffuseTexture->Bind(0);
		m_SpecularTexture->Bind(1);

		Renderer renderer;

		glm::mat4 view = glm::mat4(1.0f);

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		view = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);

		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), (float)960 / (float)540, 0.1f, 100.0f);


		//Render the cube
		m_ObjectShader->Bind();
		//m_ObjectShader->SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
		m_ObjectShader->SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);

		glm::mat4 model = glm::mat4(1.0f);

		m_ObjectShader->SetUniformMat4f("projection", projection);
		m_ObjectShader->SetUniformMat4f("view", view);
		m_ObjectShader->SetUniformMat4f("model", model);
		m_ObjectShader->SetUniformVec3("viewPos", m_CameraPos);

		m_ObjectShader->SetUniform1i("material.diffuse", 0);
		m_ObjectShader->SetUniform1i("material.specular", 1);
		m_ObjectShader->SetUniform1f("material.shininess", 32.0f);
		/*
		* Set up all of the various light sources
		*/
		// directional light
		m_ObjectShader->SetUniformVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		m_ObjectShader->SetUniformVec3("dirLight.ambient", glm::vec3(0.05f));
		m_ObjectShader->SetUniformVec3("dirLight.diffuse", glm::vec3(0.4f));
		m_ObjectShader->SetUniformVec3("dirLight.specular", glm::vec3(0.5f));

		//point light 1
		m_ObjectShader->SetUniformVec3("pointLights[0].position", m_PointLightPositions[0]);
		m_ObjectShader->SetUniformVec3("pointLights[0].ambient", glm::vec3(0.05f));
		m_ObjectShader->SetUniformVec3("pointLights[0].diffuse", glm::vec3(0.8f));
		m_ObjectShader->SetUniformVec3("pointLights[0].specular", glm::vec3(1.0f));
		m_ObjectShader->SetUniform1f("pointLights[0].constant", 1.0f);
		m_ObjectShader->SetUniform1f("pointLights[0].linear", 0.09f);
		m_ObjectShader->SetUniform1f("pointLights[0].quadratic", 0.032f);
		//point light 2
		m_ObjectShader->SetUniformVec3("pointLights[1].position", m_PointLightPositions[1]);
		m_ObjectShader->SetUniformVec3("pointLights[1].ambient", glm::vec3(0.05f));
		m_ObjectShader->SetUniformVec3("pointLights[1].diffuse", glm::vec3(0.8f));
		m_ObjectShader->SetUniformVec3("pointLights[1].specular", glm::vec3(1.0f));
		m_ObjectShader->SetUniform1f("pointLights[1].constant", 1.0f);
		m_ObjectShader->SetUniform1f("pointLights[1].linear", 0.09f);
		m_ObjectShader->SetUniform1f("pointLights[1].quadratic", 0.032f);
		//point light 3
		m_ObjectShader->SetUniformVec3("pointLights[2].position", m_PointLightPositions[2]);
		m_ObjectShader->SetUniformVec3("pointLights[2].ambient", glm::vec3(0.05f));
		m_ObjectShader->SetUniformVec3("pointLights[2].diffuse", glm::vec3(0.8f));
		m_ObjectShader->SetUniformVec3("pointLights[2].specular", glm::vec3(1.0f));
		m_ObjectShader->SetUniform1f("pointLights[2].constant", 1.0f);
		m_ObjectShader->SetUniform1f("pointLights[2].linear", 0.09f);
		m_ObjectShader->SetUniform1f("pointLights[2].quadratic", 0.032f);
		//point light 4
		m_ObjectShader->SetUniformVec3("pointLights[3].position", m_PointLightPositions[3]);
		m_ObjectShader->SetUniformVec3("pointLights[3].ambient", glm::vec3(0.05f));
		m_ObjectShader->SetUniformVec3("pointLights[3].diffuse", glm::vec3(0.8f));
		m_ObjectShader->SetUniformVec3("pointLights[3].specular", glm::vec3(1.0f));
		m_ObjectShader->SetUniform1f("pointLights[3].constant", 1.0f);
		m_ObjectShader->SetUniform1f("pointLights[3].linear", 0.09f);
		m_ObjectShader->SetUniform1f("pointLights[3].quadratic", 0.032f);
		//spotlight
		m_ObjectShader->SetUniformVec3("spotLight.position", m_CameraPos);
		m_ObjectShader->SetUniformVec3("spotLight.direction", m_CameraFront);
		m_ObjectShader->SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_ObjectShader->SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
		m_ObjectShader->SetUniformVec3("spotLight.ambient", glm::vec3(0.0f));
		m_ObjectShader->SetUniformVec3("spotLight.diffuse", glm::vec3(1.0f));
		m_ObjectShader->SetUniformVec3("spotLight.specular", glm::vec3(1.0f));
		m_ObjectShader->SetUniform1f("spotLight.constant", 1.0f);
		m_ObjectShader->SetUniform1f("spotLight.linear", 0.09f);
		m_ObjectShader->SetUniform1f("spotLight.quadratic", 0.032f);

		//Draw the cube
		m_VAO->Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

		//Render the light source
		for (int i = 0; i < 4; i++)
		{
			m_LightVAO->Bind();
			m_LightShader->Bind();
			m_LightShader->SetUniformMat4f("projection", projection);
			m_LightShader->SetUniformMat4f("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, m_PointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			m_LightShader->SetUniformMat4f("model", model);
			GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		}


	}

	void TestLighting::OnImGuiRender()
	{
		ImGui::SliderFloat3("Light Source Position", &m_LightPos.x, -1.0f, 1.0f);
	}


}