#include "Laborator5.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}

void Laborator5::Init()
{
	renderCameraTarget = false;

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 4, 10.5f), glm::vec3(0, 2, 0), glm::vec3(0, 4, 0));
	camera->TranslateUpword(3);

	translateX = 0;
	translateY = 2;
	translateZ = -4;

	translateEliceX = 0.52;
	translateEliceY = 2.03;
	translateEliceZ = -4;
	
	time = 0;

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader* shader = new Shader("ShaderSea");
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator6/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderLab");
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Mesh* mesh = new Mesh("sea");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sea.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("heart");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "heart.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("fuel");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "fuel.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	{
		Mesh* mesh = new Mesh("clouds");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "clouds.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("elice2");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "elice2.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("obstacol5");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "obstacol5.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("obstacol4");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "obstacol4.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 500.0f);
	angularStep = 0;
}

void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.98f, 0.98f,0.46f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator5::Update(float deltaTimeSeconds)
{ 
	time += deltaTimeSeconds;
	
	angularStep += deltaTimeSeconds * 1.5;
	angularStep2 += deltaTimeSeconds * 5;
	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -4.5, 0));
		RenderSimpleMesh(meshes["sea"], shaders["ShaderSea"], modelMatrix,glm::vec3(0,0,1),time);
	}

	
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(translateX, translateY, translateZ));
		RenderSimpleMesh(meshes["plane"], shaders["ShaderLab"], modelMatrix, glm::vec3(0.9, 0, 0), time);
	

		glm::vec3 a = modelMatrix * glm::vec4(0, 0, 0, 1);


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(translateEliceX, translateEliceY, translateEliceZ));
		modelMatrix = glm::rotate(modelMatrix, angularStep2, glm::vec3(1, 0, 0));
		RenderSimpleMesh(meshes["elice2"], shaders["ShaderLab"], modelMatrix, glm::vec3(0, 0, 1),time);
	}

	stepClouds1 += 6 * deltaTimeSeconds;
	stepClouds2 += 6 * deltaTimeSeconds;

	
	if (stepClouds1 >= 35) {
		stepClouds1 = -10;
	}

	if (stepClouds2 >= 55) {
		stepClouds2 = 5;
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-17, 1.8, -6));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(stepClouds1, 1.8, -6));
		RenderSimpleMesh(meshes["clouds"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 1, 1),time);
	}
	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-11, 1.3, -6));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(stepClouds1, 1.8, -6));
		RenderSimpleMesh(meshes["clouds"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 1, 1),time);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 1.8, -6));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(stepClouds1, 1.8, -6));
		RenderSimpleMesh(meshes["clouds"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 1, 1), time);
	}

	angularStepObstacle1 -= 3 * deltaTimeSeconds;
	angularStepObstacle2 -= 3 * deltaTimeSeconds;


	if (angularStepObstacle1 <= -25) {
		angularStepObstacle1 = -2;
	}
	
	if (angularStepObstacle2 <= -38) {
		angularStepObstacle2 = -7;
	}

	
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(12 + angularStepObstacle1, 1, -4));
		RenderSimpleMesh(meshes["obstacol4"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 0, 0), time);

		glm::vec3 o1 = modelMatrix * glm::vec4(0, 0, 0, 1);
	
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(25 + angularStepObstacle2, 0.3, -4));
		RenderSimpleMesh(meshes["obstacol4"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 0, 0), time);
		
		glm::vec3 o2 = modelMatrix * glm::vec4(0, 0, 0, 1);
	
		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(20 + angularStepObstacle2, -0.2, -4));
		RenderSimpleMesh(meshes["obstacol4"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 0, 0), time);
	
		glm::vec3 o3 = modelMatrix * glm::vec4(0, 0, 0, 1);

		modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(18 + angularStepObstacle2, -0.2, -4));
		RenderSimpleMesh(meshes["obstacol4"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 0, 0), time);
		
		glm::vec3 o4 = modelMatrix * glm::vec4(0, 0, 0, 1);

	//colision
	if (glm::distance(a, o1) < 0.3){
		angularStepObstacle1 = -2;
	}

	if (glm::distance(a, o2) < 0.3){
		angularStepObstacle2 = -7;
	}

	if (glm::distance(a, o3) < 0.3) {
		angularStepObstacle2 = -7;
	}

	if (glm::distance(a, o4) < 0.3) {
		angularStepObstacle2 = -7;
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(14 + angularStepObstacle1, 0.5f, -3.8));
		RenderSimpleMesh(meshes["fuel"], shaders["ShaderLab"], modelMatrix, glm::vec3(0.8, 1, 0), time);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(22 + angularStepObstacle2, 0.5f, -3.8));
		RenderSimpleMesh(meshes["fuel"], shaders["ShaderLab"], modelMatrix, glm::vec3(0.8, 1, 0), time);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(29 + angularStepObstacle2, 0.6f, -3.8));
		RenderSimpleMesh(meshes["fuel"], shaders["ShaderLab"], modelMatrix, glm::vec3(0.8, 1, 0), time);
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-35, 1.8, -10));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(stepClouds2, 1.8, -6));
		RenderSimpleMesh(meshes["clouds"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 1, 1), time);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-30, 1.3, -10));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(stepClouds2, 1.8, -6));
		RenderSimpleMesh(meshes["clouds"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 1, 1), time);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-25, 1.8, -10));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(stepClouds2, 1.8, -6));
		RenderSimpleMesh(meshes["clouds"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 1, 1), time);
	}



	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-6, 2.5, -6));
		RenderSimpleMesh(meshes["heart"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 0, 0), time);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, 2.5, -6));
		RenderSimpleMesh(meshes["heart"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 0, 0), time);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 2.5, -6));
		RenderSimpleMesh(meshes["heart"], shaders["ShaderLab"], modelMatrix, glm::vec3(1, 0, 0), time);
	}

	// Render the camera target. Useful for understanding where is the rotation point in Third-person camera movement
	if (renderCameraTarget)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}

}

void Laborator5::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Laborator5::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, float time)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	GLint location = glGetUniformLocation(shader->program, "color");
	glUniform3fv(location, 1, glm::value_ptr(color));

	location = glGetUniformLocation(shader->program, "time");
	glUniform1f(location, time);


	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

float FoV = 60, width = 10, height = 10;

void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}
	}

}

void Laborator5::OnKeyPress(int key, int mods)
{
		
	//third-person camera
	if (key == GLFW_KEY_T)
	{
		camera->Set(glm::vec3(0, 4, 10.5f), glm::vec3(0, 2, 0), glm::vec3(0, 4, 0));
		camera->TranslateUpword(3);
	}

	//first-person camera
	if (key == GLFW_KEY_C) {
		camera->Set(glm::vec3(-10, -10, -3), glm::vec3(0, 0, -2.1), glm::vec3(0, 1, 0));
	}
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	
	if (mouseY < 540 ) {
		translateY += 0.005f * deltaY;
		translateEliceY += 0.005f * deltaY;
	}
	else if (mouseY >= 3){
		translateY -= 0.005f * deltaY;
		translateEliceY -= 0.005f * deltaY;
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(-deltaY * sensivityOX);
			camera->RotateThirdPerson_OY(-deltaX * sensivityOY);
		}

	}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height)
{
}
