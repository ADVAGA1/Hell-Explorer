#include "Door.h"

#define HITBOX_X 32
#define HITBOX_Y 57
#define OFFSET_X 34
#define OFFSET_Y 7

enum DoorAnims
{
	DOOR_CLOSED, DOOR_OPEN
};

void Door::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 64), glm::vec2(1.0f/4.0f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(DOOR_CLOSED, 8);
	sprite->addKeyframe(DOOR_CLOSED, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(DOOR_OPEN, 4);
	sprite->addKeyframe(DOOR_OPEN, glm::vec2(1.0f/4.0f, 0.f));
	sprite->addKeyframe(DOOR_OPEN, glm::vec2(2.0f/4.0f, 0.f));
	sprite->addKeyframe(DOOR_OPEN, glm::vec2(3.f / 4., 0.f));

	sprite->changeAnimation(DOOR_CLOSED);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));

}


glm::ivec2 Door::getBoundingBoxMax() {
	return posItem + glm::ivec2(OFFSET_X, OFFSET_Y) + glm::ivec2(HITBOX_X, HITBOX_Y);
}

glm::ivec2 Door::getBoundingBoxMin() {
	return posItem + glm::ivec2(OFFSET_X, OFFSET_Y);
}

void Door::openDoor() {
	sprite->changeAnimation(DOOR_OPEN);
}

void Door::update(int deltaTime) {
	sprite->updateLoopless(deltaTime);
}