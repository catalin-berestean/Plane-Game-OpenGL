#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Objects2D.h"

using namespace std;

Tema1::Tema1()
{

}

Tema1::~Tema1()
{

}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	pos1 += 350;
	pos2 += 700;
	pos3 += 1050;
	pos4 += 1400;

	float squareSide = 34.f;
	ochiSide = 15.f - 0.8 * 15.f;
	float triagleSide = 13.f;
	rot = 0;
	translateOchiX = 5;

	up = false;
	down = false;
	straight = false;

	Mesh* corp = Objects2D::CreateSquare("corp", glm::vec3(0, 0, 0), squareSide, glm::vec3(2.f, 0.9200f, 0.4f), true);
	AddMeshToList(corp);

	Mesh* cap = Objects2D::CreateCircle("cap", glm::vec3(0, 0, 0), 15.f, squareSide, glm::vec3(1.f, 0.4706f, 0.2f), true);
	AddMeshToList(cap);

	Mesh* ochi = Objects2D::CreateCircle("ochi", glm::vec3(0, 0, 0), ochiSide, squareSide, glm::vec3(0.4706f, 0.2392f, 0), true);
	AddMeshToList(ochi);

	Mesh* cioc = Objects2D::CreateTriangle("cioc", glm::vec3(0, 0, 0), triagleSide, glm::vec3(0.7608f, 0.2314f, 0.1333f), true);
	AddMeshToList(cioc);

	Mesh* aripa = Objects2D::CreateTriangle("aripa", glm::vec3(0, 0, 0), triagleSide, glm::vec3(0.7608f, 0.2314f, 0.1333f), true);
	AddMeshToList(aripa);

	Mesh* pipe = Objects2D::CreateRectangle("pipe", glm::vec3(0, 0, 0), 100.f, 400.f, glm::vec3(0.4706f, 0.2392f, 0), true);
	AddMeshToList(pipe);

	Mesh* sol = Objects2D::CreateRectangle("sol", glm::vec3(0, 0, 0), 2000.f, 50.f, glm::vec3(0.3f, 0.7f, 0), true);
	AddMeshToList(sol);

	screen = 0;
	angularStep = 0;
	coef = 527;
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.5, 0.3, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

}


void Tema1::gameOver() {
	cout << "GAME OVER!";
}

void Tema1::Update(float deltaTimeSeconds)
{

	// Update steps for translation, rotation, scale, in order to create animations
	glm::ivec2 resolution = window->GetResolution();

	if (end == 0) {
		coef -= 0.15f * deltaTimeSeconds * resolution.y;

		pos1 -= 400 * deltaTimeSeconds;
		pos2 -= 400 * deltaTimeSeconds;
		pos3 -= 400 * deltaTimeSeconds;
		pos4 -= 400 * deltaTimeSeconds;

	}
	else {

	}

	if (pos1 <= 0) {
		pos1 = 1400;
	}
	if (pos2 <= 0) {
		pos2 = 1400;
	}
	if (pos3 <= 0) {
		pos3 = 1400;
	}
	if (pos4 <= 0) {
		pos4 = 1400;
	}

	modelMatrix = Transform2D::Translate(212, coef);
	modelMatrix *= Transform2D::Translate(-50, 28);
	modelMatrix *= Transform2D::Translate(6.5f, 6.5f);
	modelMatrix *= Transform2D::Rotate(rot);
	modelMatrix *= Transform2D::Translate(-6.5f, -6.5f);
	RenderMesh2D(meshes["aripa"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(0, 0);
	RenderMesh2D(meshes["sol"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(155, coef);
	modelMatrix *= Transform2D::Translate(-10, 15);
	modelMatrix *= Transform2D::Translate(17, 17);
	modelMatrix *= Transform2D::Rotate(rot);
	modelMatrix *= Transform2D::Translate(-17, -17);
	RenderMesh2D(meshes["corp"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(193, coef);
	modelMatrix *= Transform2D::Translate(-7+translateOchiX, 33+translateOchiY);
	RenderMesh2D(meshes["ochi"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(190, coef);
	modelMatrix *= Transform2D::Translate(-7, 33+translateCap);
	RenderMesh2D(meshes["cap"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(204, coef);
	modelMatrix *= Transform2D::Translate(-8, 30+translateOchiY+translateCioc);
	modelMatrix *= Transform2D::Translate(6.5f, 6.5f);
	modelMatrix *= Transform2D::Rotate(rotatieCioc);
	modelMatrix *= Transform2D::Translate(-6.5f, -6.5f);
	RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);



	modelMatrix = Transform2D::Translate(pos1, r1);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(pos2, r2);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(pos3, r3);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(pos4, r4);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(pos1, -r5);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(pos2, -r6);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(pos3, -r7);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	modelMatrix = Transform2D::Translate(pos4, -r8);
	RenderMesh2D(meshes["pipe"], shaders["VertexColor"], modelMatrix);

	if (pos1 > 130 && pos1 < 160 && end == 0) {
		if (coef > 720 - r5 - 30) {
			end = 1;
			cout << "GAME OVER";
		}
	}

}

void Tema1::FrameEnd()
{

}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		up = true;
		straight = false;
		down = false;
	}

	if (up) {
		coef += 90;
		nrSarituri++;
		jump = true;
		rot = RADIANS(30);
		rotatieCioc = RADIANS(35);
		translateCap = 10;
		translateOchiY = 10;
		translateCioc = 5;
		down = false;
		straight = false;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
	if (key == GLFW_KEY_SPACE) {
		if (nrSarituri > 0) {
			down = true;
		}
		else if (nrSarituri == 0) {
			straight = true;
		}

	}

	if (down) {
		rot = RADIANS(-30);
		rotatieCioc = RADIANS(-10);
		translateCap = -13;
		translateOchiY = -13;
		translateCioc = -5;
		up = false;
		straight = false;
	}
	if (straight) {
		rot = 0;
		translateCap = 0;
		translateOchiY = 0;
		translateCioc = 0;
		up = false;
		down = false;
	}
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}