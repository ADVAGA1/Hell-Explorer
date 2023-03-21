#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	menu.init();
	currentScene = SceneType::MENU_SCENE;
}

bool Game::update(int deltaTime)
{
	switch (currentScene)
	{
	case SceneType::MENU_SCENE:
		menu.update(deltaTime);
		break;
	case SceneType::SCENE_1:
		scene.update(deltaTime);
		break;
	default:
		break;
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentScene)
	{
	case SceneType::MENU_SCENE:
		menu.render();
		break;
	case SceneType::SCENE_1:
		scene.render();
		break;
	default:
		break;
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) 
{

	if (key == 32) { //tecla ENTER
		int cursor = menu.getCursor();
		switch (cursor) {
		case CursorType::PLAY:
			currentScene = SceneType::SCENE_1;
			break;
		case CursorType::INSTRUCTIONS:
			currentScene = SceneType::INSTRUCTIONS_SCENE;
			break;
		case CursorType::CREDITS:
			currentScene = SceneType::CREDITS_SCENE;
			break;
		case CursorType::EXIT:
			exit(0);
			break;
		}
	}

	return keys[key];
}

bool Game::getSpecialKey(int key)
{
	if (currentScene == MENU_SCENE) {
		int cursor = menu.getCursor();
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			--cursor;
			if (cursor < 0) cursor = -3 * cursor;
		}

		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			++cursor;
		}

		cursor = cursor % 4;
		menu.setCursor(cursor);
	}

	return specialKeys[key];
}





