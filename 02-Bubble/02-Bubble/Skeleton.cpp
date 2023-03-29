#include "Skeleton.h"

#define FALL_STEP 4
#define HITBOX_X 17
#define HITBOX_Y 28

enum EnemyAnims {
	MOVE_LEFT, MOVE_RIGHT
};

Skeleton::Skeleton(bool left) {
	goLeft = left;
}

void Skeleton::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {

	spritesheet.loadFromFile("images/skeleton.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0/8.0, 1.0/2.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.f/8.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.f/8.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3.0f/8.0f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.0f / 8.0f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5.0f / 8.0f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(6.0f / 8.0f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(7.0f / 8.0f, 0.f));


	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f/8.0f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(1.f / 8.0f, 1.0f/2.0f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.f / 8.0f, 1.0f / 2.0f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.f / 8.0f, 1.0f / 2.0f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(4.f / 8.0f, 1.0f / 2.0f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(5.0f/8.0f, 0.5f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(6.0f/8.0f, 1.0f/2.0f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(7.f/8.f, 1.0f/2.0f));

	if (goLeft) sprite->changeAnimation(MOVE_LEFT);
	else sprite->changeAnimation(MOVE_RIGHT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Skeleton::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (goLeft) {
		if (!map->collisionMoveLeft(posEnemy, glm::ivec2(HITBOX_X, HITBOX_Y),false)) {
			if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			posEnemy.x -= 1;
		}
		else goLeft = !goLeft;
	}
	else {
		if (!map->collisionMoveRight(posEnemy, glm::ivec2(HITBOX_X, HITBOX_Y),false)) {
			if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
			posEnemy.x += 1;
		}
		else goLeft = !goLeft;
	}

	glm::ivec2 posNext;
	if (goLeft) posNext = posEnemy + glm::ivec2(0, HITBOX_Y);
	else posNext = posEnemy + glm::ivec2(HITBOX_X, HITBOX_Y);

	int nextTile = map->checkTile(posNext.x / map->getTileSize(), posNext.y / map->getTileSize());

	if (!map->collidable(nextTile, false))
	{
		goLeft = !goLeft;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}


glm::ivec2 Skeleton::getBoundingBoxMax() {
	return posEnemy + glm::ivec2(HITBOX_X, HITBOX_Y);
}
glm::ivec2 Skeleton::getBoundingBoxMin() {
	return posEnemy;
}

void Skeleton::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	posEnemy += glm::ivec2(0, 32 - HITBOX_Y);
	startY = int(posEnemy.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}