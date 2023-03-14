#pragma once

#include "Sprite.h"
#include "TileMap.h"

class Item
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::ivec2 getPosition();

	virtual glm::ivec2 getBoundingBoxMax() = 0;
	virtual glm::ivec2 getBoundingBoxMin() = 0;

protected:
	glm::ivec2 tileMapDispl, posItem;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};

