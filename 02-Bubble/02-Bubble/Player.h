#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int nLives);
	void update(int deltaTime);
	void render();

	void updateSprite(int deltaTime);
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::ivec2 getPosition();

	glm::ivec2 getBoundingBoxMax();
	glm::ivec2 getBoundingBoxMin();

	int getLives();
	void setLives(int newLives);

	bool isGodMode();
	void setGodMode(bool b);

	void changeInvulnerable(bool inv);
	void end();
	
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int lives;
	bool godMode, invulnerable, goLeft;
	int runTimer;
	bool spawning, ending;
	int spawnTimer;

};


#endif // _PLAYER_INCLUDE


