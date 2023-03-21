#pragma once

#include "Texture.h"
#include "ShaderProgram.h"
#include "Sprite.h"

enum CursorType {
	PLAY, INSTRUCTIONS, CREDITS, EXIT
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

private:

	void initShaders();

	Texture backgroundTex;
	ShaderProgram texProgram;
	Sprite* background;
	glm::mat4 projection;

	int cursor;
	Texture cursorTexture;
	Sprite* cursorSprite;

	float currentTime;
};

