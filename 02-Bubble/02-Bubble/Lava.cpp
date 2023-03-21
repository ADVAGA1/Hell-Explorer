#include "Lava.h"

#define HITBOX_X 8
#define HITBOX_Y 17

void Lava::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

	spritesheet.loadFromFile("images/tileset.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f / 10.0f, 1.0f/10.f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 6);
	sprite->addKeyframe(0, glm::vec2(9.0 / 10.0, 1.f/10.f));
	sprite->addKeyframe(0, glm::vec2(9.0f / 10.f , 2.0f / 10.0f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Lava::update(int deltaTime)
{
	sprite->update(deltaTime);
}

glm::ivec2 Lava::getBoundingBoxMax() {
	return posEnemy + glm::ivec2(HITBOX_X, HITBOX_Y);
}
glm::ivec2 Lava::getBoundingBoxMin() {
	return posEnemy + glm::ivec2(-HITBOX_X, -HITBOX_Y);
}