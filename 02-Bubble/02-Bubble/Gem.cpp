#include "Gem.h"

#define HITBOX_X 8
#define HITBOX_Y 8

void Gem::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	/*spritesheet.loadFromFile("images/skeleton.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0 / 4.0, 1.0 / 5.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 2.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 4.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 1.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 2.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 3.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 4.0 / 5.0));


	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 1.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 2.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 3.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 4.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.0 / 4.0, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.0 / 4.0, 1.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3. / 4., 2.0 / 5.0));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posItem.x), float(tileMapDispl.y + posItem.y)));
*/
}


glm::ivec2 Gem::getBoundingBoxMax() {
	return posItem + glm::ivec2(HITBOX_X, HITBOX_Y);
}

glm::ivec2 Gem::getBoundingBoxMin() {
	return posItem + glm::ivec2(-HITBOX_X, -HITBOX_Y);
}
