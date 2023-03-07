#pragma once

#include "Sprite.h"
#include "TileMap.h"


class Enemy
{

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	glm::ivec2 getPosition();

protected:
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int startY;
};
