#pragma once

#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"

enum CursorType {
	PLAY, INSTRUCTIONS, CREDITS
};

enum MenuType {
	MENU, INSTRUCTIONS_MENU, CONTROLS_MENU, CREDITS_MENU
};


class Menu
{
public:

	~Menu();

	void init();
	void update(int deltaTime);
	void render();

	int getCursor();
	void setCursor(int c);
	void setScene(int scene);

private:

	void initShaders();

	Texture menuTex;
	ShaderProgram texProgram;
	Sprite* menu;
	glm::mat4 projection;

	Texture instructionsTex;
	Sprite* instructions;

	Texture creditsTex;
	Sprite* credits;

	Texture controlsTex;
	Sprite* controls;

	int cursor;
	Texture cursorTexture;
	Sprite* cursorSprite;

	int currentScene;

	float currentTime;
};

