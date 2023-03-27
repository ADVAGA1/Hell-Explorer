#include "Chrono.h"


#define HITBOX_X 16
#define HITBOX_Y 16

void Chrono::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/chrono.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));

}


glm::ivec2 Chrono::getBoundingBoxMax() {
	return posItem + glm::ivec2(HITBOX_X, HITBOX_Y);
}

glm::ivec2 Chrono::getBoundingBoxMin() {
	return posItem;
}