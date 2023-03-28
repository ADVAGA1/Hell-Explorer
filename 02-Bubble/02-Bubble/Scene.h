#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Skeleton.h"
#include "Sprite.h"
#include "Texture.h"
#include "StaticSprite.h"
#include "Coin.h"
#include "Key.h"
#include "Door.h"
#include "Lava.h"
#include "Ghost.h"
#include "Vampire.h"
#include "Text.h"
#include "Chrono.h"
#include "Clock.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init(int level, int score);
	void update(int deltaTime);
	void render();
	
	bool collisionPlayerEnemy(Player* player, Enemy* enemy);
	bool collisionPlayerItem(Player* player, Item* item);

	void spawnKey();
	void changeGodMode();

	int getScore() { return score; };
	int getScene() { return scene; };
	bool hasWon() { return win; };
	bool hasLost() { return lose; };

private:
	void initShaders();
	void reset();

private:
	int scene;
	TileMap *map;
	Player *player;
	vector<Enemy*> enemies;
	Texture spritesheet;
	Texture backgroundTexture;
	Sprite* background;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Sprite* floorSprite;
	Coin* coin;
	Key* key;
	Chrono* chrono;
	Clock* clock;
	Door* door;
	bool openDoor, keyTaken, coinTaken, keySpawn, isStoped, chronoTaken, coinSpawn, chronoSpawn, clockSpawn, clockTaken;
	vector<Lava*> lavas;
	Sprite* heart;
	Texture heartTexture;
	int damageTimer;
	bool hasBeenDamaged, damaged;
	int timer, lastTime;
	Text text;
	int score;
	vector<pair<pair<int,int>, bool>> floorCheck;
	int chronoTimer;
	bool win, lose;

};


#endif

