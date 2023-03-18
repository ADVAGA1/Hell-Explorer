#include "Coin.h"

#define HITBOX_X 8
#define HITBOX_Y 8

void Coin::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f / 14.0f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(0, glm::vec2(1.0f/14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(2.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(3.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(4.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(5.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(6.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(7.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(8.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(9.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(10.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(11.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(12.0f / 14.0f, 0.f));
	sprite->addKeyframe(0, glm::vec2(13.0f / 14.0f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));

}


glm::ivec2 Coin::getBoundingBoxMax() {
	return posItem + glm::ivec2(HITBOX_X, HITBOX_Y);
}

glm::ivec2 Coin::getBoundingBoxMin() {
	return posItem + glm::ivec2(-HITBOX_X, -HITBOX_Y);
}
