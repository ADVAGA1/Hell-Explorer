#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include <irrKlang.h>


#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480 

enum class SceneType {
	MENU, INSTRUCTIONS, CREDITS, LEVEL1, LEVEL2, LEVEL3
};


using namespace irrklang;

// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}

public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}

	~Game();
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key);
	bool getSpecialKey(int key) ;

	void playSound(const char* path);
	void playTheme(const char* path);

private:
	bool bPlay;                       // Continue to play game?
	Scene* scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	SceneType currentScene;
	Menu* menu;
	int globalScore;
	ISoundEngine* soundEngine;

};


#endif // _GAME_INCLUDE


