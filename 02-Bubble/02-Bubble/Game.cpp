#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	//menu.init();
	scene.init();
	currentScene = SceneType::SCENE_1;
}

bool Game::update(int deltaTime)
{
	switch (currentScene)
	{
	case SceneType::MENU:
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
	case SceneType::MENU:
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
	return keys[key];
}

bool Game::getSpecialKey(int key)
{
	return specialKeys[key];
}





