#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>

Game::~Game() {
	if (soundEngine != NULL) soundEngine->drop();
	if (scene != NULL) delete scene;
	if (menu != NULL) delete menu;
}

void Game::init()
{
	bPlay = true;
	globalScore = 0;
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	soundEngine = createIrrKlangDevice();

	if (!soundEngine) cout << "Error: Sound engine not created." << endl;

	soundEngine->setSoundVolume(0.25f);

	scene = nullptr;
	menu = new Menu();
	menu->init();
	currentScene = SceneType::MENU;
}

bool Game::update(int deltaTime)
{
	if (currentScene == SceneType::MENU || currentScene == SceneType::INSTRUCTIONS || currentScene == SceneType::CREDITS) menu->update(deltaTime);
	else scene->update(deltaTime);

	if (currentScene == SceneType::LEVEL1 || currentScene == SceneType::LEVEL2 || currentScene == SceneType::LEVEL3) {
		if (scene->hasLost()) {
			delete scene;
			scene = nullptr;
			menu = new Menu();
			menu->init();
			currentScene = SceneType::MENU;
		}
		else if (scene->hasWon()) {
			globalScore += scene->getScore() - globalScore;
			if (currentScene == SceneType::LEVEL1) {
				currentScene = SceneType::LEVEL2;
				scene->init(2, globalScore);
			}
			else if (currentScene == SceneType::LEVEL2) {
				currentScene = SceneType::LEVEL3;
				scene->init(3, globalScore);
			}
			else {
				delete scene;
				scene = nullptr;
				menu = new Menu();
				menu->init();
				currentScene = SceneType::MENU;
			}
		}
	}

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (currentScene == SceneType::MENU || currentScene == SceneType::INSTRUCTIONS || currentScene == SceneType::CREDITS) menu->render();
	else scene->render();
}

void Game::keyPressed(int key)
{
	if (key == 27) bPlay = false; // Escape code

	if (currentScene == SceneType::MENU) {
		if (key == 13) {  // Enter code
			int cursor = menu->getCursor();

			if (cursor == 0) {
				currentScene = SceneType::LEVEL1;
				scene = new Scene();
				scene->init(1, 0);
				delete menu;
				menu = nullptr;
			}
			else if (cursor == 1) {
				currentScene = SceneType::INSTRUCTIONS;
				menu->setScene(1);
			}
			else {
				currentScene = SceneType::CREDITS;
				menu->setScene(3);
			}
		}
	}
	else if (currentScene == SceneType::INSTRUCTIONS) {
		if (key == 'm' || key == 'M') {
			currentScene = SceneType::MENU;
			menu->setScene(0);
		}

		if (key == 'c' || key == 'C') {
			menu->setScene(2);
		}
	}
	else if (currentScene == SceneType::CREDITS) {
		if (key == 'm' || key == 'M') {
			currentScene = SceneType::MENU;
			menu->setScene(0);
		}
	}
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
		if (scene == nullptr) scene = new Scene();
		scene->init(1, globalScore);
	}
	if (key == '2') {
		currentScene = SceneType::LEVEL2;
		if (scene == nullptr) scene = new Scene();
		scene->init(2, globalScore);
	}
	if (key == '3') {
		currentScene = SceneType::LEVEL3;
		if (scene == nullptr) scene = new Scene();
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

void Game::playSound(const char* path) {
	soundEngine->setSoundVolume(0.4f);
	soundEngine->play2D(path);
	soundEngine->setSoundVolume(0.25f);
}

void Game::playTheme(const char* path) {
	soundEngine->stopAllSounds();
	soundEngine->play2D(path, true);
	//soundEngine->setSoundVolume(0.25f);
}



