#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void gameOver();
	void initMovementRight();
	void drawPipes();
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	GLfloat coef, rot;
	float angularStep, pos1 = 1280, pos2 = 1280, pos3 = 1280, pos4 = 1280;
	float translateX, rotireCap, ochiSide, translateCap;
	float translateOchiX, translateOchiY, translateCioc, rotatieCioc;
	bool jump = false, down, up, straight;
	int screen, end = 0, nrSarituri = 0;

	int r1 = rand() % 300 + 350;
	int r2 = rand() % 190 + 250;
	int r3 = rand() % 250 + 350;
	int r4 = rand() % 190 + 260;

	int r5 = rand() % 80 + 140;
	int r6 = rand() % 90 + 230;
	int r7 = rand() % 90 + 230;
	int r8 = rand() % 150 + 250;
};