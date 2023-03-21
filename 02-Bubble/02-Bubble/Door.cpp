#include "Door.h"

#define HITBOX_X 8
#define HITBOX_Y 32
#define OFFSET 32

enum DoorAnims
{
	DOOR_CLOSED, DOOR_OPENING, DOOR_OPENED
};

void Door::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 64), glm::vec2(1.0f/4.0f, 1.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(DOOR_CLOSED, 8);
	sprite->addKeyframe(DOOR_CLOSED, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(DOOR_OPENING, 2);
	sprite->addKeyframe(DOOR_OPENING, glm::vec2(1.0f/4.0f, 0.f));
	sprite->addKeyframe(DOOR_OPENING, glm::vec2(2.0f/4.0f, 0.f));

	sprite->setAnimationSpeed(DOOR_OPENED, 8);
	sprite->addKeyframe(DOOR_OPENED, glm::vec2(3.f/4., 0.f));

	sprite->changeAnimation(DOOR_CLOSED);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));

}


glm::ivec2 Door::getBoundingBoxMax() {
	return posItem + glm::ivec2(OFFSET, 0) + glm::ivec2(HITBOX_X, HITBOX_Y);
}

glm::ivec2 Door::getBoundingBoxMin() {
	return posItem + glm::ivec2(OFFSET, 0) + glm::ivec2(-HITBOX_X, -HITBOX_Y);
}

void Door::openDoor() {
	sprite->changeAnimation(DOOR_OPENING);
}

void Door::openedDoor() {
	sprite->changeAnimation(DOOR_OPENED);
}