#define STB_IMAGE_IMPLEMENTATION
#include"vendor/stbimage/stb_image.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm/glm.hpp>

#include"Buffers/IndexBuffer.hpp"
#include"Buffers/VertexBufferObject.hpp"
#include"Shaders/Shader.hpp"

#include"vendor/imgui/imgui.h"
#include"vendor/imgui/imgui_impl_glfw.h"
#include"vendor/imgui/imgui_impl_opengl3.h"

#include"Geometry/2 Dimensional/Rectangle.hpp"
#include"Geometry//2 Dimensional/Triangle.hpp"

void callback(GLFWwindow* window, int width, int height);


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_REFRESH_RATE, 144);

	GLFWwindow* window = glfwCreateWindow(2000, 1000, "openGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "\nFailed to create window";
		return -1;
	}

	glfwMakeContextCurrent(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	ImGuiStyle* style = &ImGui::GetStyle();

	style->Colors[ImGuiCol_Text] = ImVec4(1.0, 1.0, 1.0, 1.0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glfwSwapInterval(1);
	glViewport(0, 0, 2000, 1000);
	glfwSetFramebufferSizeCallback(window, callback);

	float u_resolution[] =
	{
		2000, 1000
	};

	float vertices[] =
	{
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int index[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	Shader sshader("res/shader/vertex.vert", "res/shader/fragment.frag");
	Shader circle_sshader("res/shader/circle/circle.vert", "res/shader/circle/circle.frag");
	
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nr_channels;
	unsigned char* data = stbi_load("res/textures/simly.JPG", &width, &height, &nr_channels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "\nFailed to load the texture";
	}
	stbi_image_free(data);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	Vertex_Buffer VBO(vertices, sizeof(vertices));
	Index_Buffer EBO(index, sizeof(index));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glm::vec3 center(0.0f, 0.0f, 0.0f);

	Rectangle rect(center, 1.0f, 1.0f);
	Triangle trig(center, 0.5f, 0.0f, 100.0f);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Demo window");
		static float scale = 1.0f;
		static float rotate = 1.0f;
		ImGui::SliderFloat("Scaling", &scale, 0.0f, 100.0f);
		ImGui::SliderFloat("Rotation", &rotate, -glm::radians(360.0f), glm::radians(360.0f));
		ImGui::End();

		sshader.use();
		trig.render();

		glm::mat4 trans(1.0f);
		trans = glm::rotate(trans, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(0.2f, 0.2f, 0.0f));

		sshader.set_matrix4("transform", trans);


		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}