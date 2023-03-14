#include "Item.h"

void Item::render() {
	sprite->render();
}

void Item::update(int deltaTime) {
	sprite->update(deltaTime);
}

void Item::setTileMap(TileMap* tileMap) {
	map = tileMap;
}

void Item::setPosition(const glm::vec2& pos) {
	posItem = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));
}

glm::ivec2 Item::getPosition() {
	return posItem;
}