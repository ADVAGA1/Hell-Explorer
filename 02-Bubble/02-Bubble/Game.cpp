#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	globalScore = 0;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	menu = new Menu();
	menu->init();
	scene = new Scene();
	currentScene = SceneType::MENU;
}

bool Game::update(int deltaTime)
{
	switch (currentScene)
	{
	case SceneType::MENU:
		menu->update(deltaTime);
		break;
	default:
		scene->update(deltaTime);
		break;
	}

	if (scene->hasLost()) {
		currentScene = SceneType::MENU;
	}

	if (scene->hasWon()) {
		globalScore += scene->getScore() - globalScore;
		if (currentScene == SceneType::LEVEL1) {
			currentScene = SceneType::LEVEL2;
			scene->init(2,globalScore);
		}
		else if (currentScene == SceneType::LEVEL2) {
			currentScene = SceneType::LEVEL3;
			scene->init(3, globalScore);
		}
		else {
			currentScene = SceneType::MENU;
		}
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentScene)
	{
	case SceneType::MENU:
		menu->render();
		break;
	default:
		scene->render();
		break;
	}
}

void Game::keyPressed(int key)
{
	if(key == 27) bPlay = false; // Escape code

	if(currentScene == SceneType::MENU){
		if (key == 13) {  // Enter code
			int cursor = menu->getCursor();
			
			if (cursor == 0) {
				currentScene = SceneType::LEVEL1;
				scene->init(1, 0);
			}
			else if (cursor == 1) {}
			else {}
		}
	}
	else if (currentScene == SceneType::INSTRUCTIONS) {
	}
	else if(currentScene == SceneType::CREDITS){}
	else {
		if (key == 'r' || key == 'R') {
			if (currentScene == SceneType::LEVEL1) scene->init(1, globalScore);
			if (currentScene == SceneType::LEVEL2) scene->init(2, globalScore);
			if (currentScene == SceneType::LEVEL3) scene->init(3, globalScore);
		}
		if (key == 'k' || key == 'K') scene->spawnKey();
		if (key == 'g' || key == 'G') scene->changeGodMode();
	}

	if (key == '1') {
		currentScene = SceneType::LEVEL1;
		delete scene;
		scene = new Scene();
		scene->init(1,globalScore);
	}
	if (key == '2') {
		currentScene = SceneType::LEVEL2;
		delete scene;
		scene = new Scene();
		scene->init(2, globalScore);
	}
	if (key == '3') {
		currentScene = SceneType::LEVEL3;
		delete scene;
		scene = new Scene();
		scene->init(3, globalScore);
	}
	
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{

	if (currentScene == SceneType::MENU) {
		if (key == GLUT_KEY_UP) {
			menu->setCursor(menu->getCursor() - 1);
		}
		else if (key == GLUT_KEY_DOWN) {
			menu->setCursor(menu->getCursor() + 1);
		}
	}

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





