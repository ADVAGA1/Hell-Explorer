#include "Menu.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Game.h"
#include <GL/glut.h>


Menu::~Menu() {
	if (menu != NULL) delete menu;
	if (instructions != NULL) delete instructions;
	if (credits != NULL) delete credits;
	if(cursorSprite != NULL) delete cursorSprite;
}

void Menu::init() {
	initShaders();
	menuTex.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menu = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1, 1), &menuTex, &texProgram);

	instructionsTex.loadFromFile("images/instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructions = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1, 1), &instructionsTex, &texProgram);

	controlsTex.loadFromFile("images/controls.png", TEXTURE_PIXEL_FORMAT_RGBA);
	controls = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1, 1), &controlsTex, &texProgram);

	creditsTex.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	credits = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1, 1), &creditsTex, &texProgram);

	cursorTexture.loadFromFile("images/cursor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cursorSprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(0.25f,1.f), &cursorTexture, &texProgram);
	cursorSprite->setNumberAnimations(1);
	cursorSprite->setAnimationSpeed(0, 4);
	cursorSprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	cursorSprite->addKeyframe(0, glm::vec2(0.25f, 0.f));
	cursorSprite->addKeyframe(0, glm::vec2(0.50f, 0.f));
	cursorSprite->addKeyframe(0, glm::vec2(0.75f, 0.f));
	cursorSprite->changeAnimation(0);

	cursorSprite->setPosition(glm::ivec2(90,198));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	cursor = CursorType::PLAY;
	currentScene = MENU;

	currentTime = 0.f;

	Game::instance().playTheme("sound/menu_theme.mp3");
}

void Menu::update(int deltaTime) {

	currentTime += deltaTime;

	if (currentScene == MENU) {

		switch (cursor)
		{
		case CursorType::PLAY:
			cursorSprite->setPosition(glm::vec2(80, 198));
			break;
		case CursorType::INSTRUCTIONS:
			cursorSprite->setPosition(glm::vec2(80, 270));
			break;
		case CursorType::CREDITS:
			cursorSprite->setPosition(glm::vec2(80, 358));
			break;
		default:
			break;
		}

		cursorSprite->update(deltaTime);
	}
}

void Menu::render() {

	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	switch (currentScene) {
	case MENU:
		menu->render();
		break;
	case INSTRUCTIONS_MENU :
		instructions->render();
		break;
	case CONTROLS_MENU:
		controls->render();
		break;
	case CREDITS_MENU:
		credits->render();
		break;
	}
	
	if(currentScene == MENU) cursorSprite->render();
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

int Menu::getCursor() {
	return cursor;
}

void Menu::setCursor(int c) {
	cursor = c;
	if (cursor < 0) cursor = -2 * cursor;
	cursor = cursor % 3;
}

void Menu::setScene(int scene) {
	currentScene = scene;
}