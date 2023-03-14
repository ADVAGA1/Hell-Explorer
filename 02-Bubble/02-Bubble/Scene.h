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


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	
	bool collisionPlayerEnemy(Player* player, Enemy* enemy);

private:
	void initShaders();
	//void checkFloor(const glm::ivec2& playerPosition);
	//void printFloor(int x, int y);

private:
	TileMap *map;
	Player *player;
	Skeleton* enemy;
	Texture spritesheet;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Sprite* floorSprite;
	bool bprintFloor;

};


#endif // _SCENE_INCLUDE

