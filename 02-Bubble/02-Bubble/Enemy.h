#pragma once

#include "Sprite.h"
#include "TileMap.h"

#define OFFSET 16

class Enemy
{

public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	void render();

	void setTileMap(TileMap* tileMap);
	virtual void setPosition(const glm::vec2& pos);

	glm::ivec2 getPosition();

	virtual glm::ivec2 getBoundingBoxMax() = 0;
	virtual glm::ivec2 getBoundingBoxMin() = 0;

protected:
	glm::ivec2 tileMapDispl, posEnemy;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int startY;
};
