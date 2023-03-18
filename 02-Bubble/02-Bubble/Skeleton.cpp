#include "Skeleton.h"

#define FALL_STEP 4
#define HITBOX_X 8
#define HITBOX_Y 16

enum EnemyAnims {
	MOVE_LEFT, MOVE_RIGHT
};

void Skeleton::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

	spritesheet.loadFromFile("images/skeleton.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0/4.0, 1.0/5.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 2.0/5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 3.0/5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 4.0/5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0/4.0, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 1.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 2.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 3.0 / 5.0));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0 / 4.0, 4.0 / 5.0));


	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0/4.0, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 1.0/5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 2.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 3.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0 / 4.0, 4.0 / 5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.0/4.0, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.0/4.0, 1.0/5.0));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3./4., 2.0/5.0));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Skeleton::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (goLeft) {
		if (!map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32),false)) {
			if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			posEnemy.x -= 1;
		}
		else goLeft = !goLeft;
	}
	else {
		if (!map->collisionMoveRight(posEnemy, glm::ivec2(32, 32),false)) {
			if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
			posEnemy.x += 1;
		}
		else goLeft = !goLeft;
	}

	posEnemy.y += FALL_STEP;

	glm::ivec2 posNext;
	if (goLeft) posNext = posEnemy + glm::ivec2(-20, 0);
	else posNext = posEnemy + glm::ivec2(32, 0);

	if (!map->collisionMoveDown(posNext, glm::ivec2(32, 32), &posEnemy.y, false))
	{
		posEnemy.y = startY;
		if (goLeft) {
			posEnemy.x += 2;
		}
		else {
			posEnemy.x -= 2;
		}
		goLeft = !goLeft;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}


glm::ivec2 Skeleton::getBoundingBoxMax() {
	return posEnemy + glm::ivec2(HITBOX_X, HITBOX_Y);
}
glm::ivec2 Skeleton::getBoundingBoxMin() {
	return posEnemy + glm::ivec2(-HITBOX_X, -HITBOX_Y);
}