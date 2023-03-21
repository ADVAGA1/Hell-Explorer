#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 80
#define FALL_STEP 4

#define HITBOX_X 16
#define HITBOX_Y 16


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMPING_UP_R, JUMPING_DOWN_R, JUMPING_UP_L, JUMPING_DOWN_L
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	lives = 5;
	bJumping = false;
	godMode = false;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0/8.0, 0.20), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	
		sprite->setAnimationSpeed(STAND_LEFT, 6);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.2f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(1.0f/8.0f, 0.2f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(2.0f / 8.0f, 0.2f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(3.0f / 8.0f, 0.2f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(4.0f / 8.0f, 0.2f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(5.0f / 8.0f, 0.2f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 6);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(1.0f / 8.0f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(2.0f / 8.0f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(3.0f / 8.0f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(4.0f / 8.0f, 0.f));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(5.0f / 8.0f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 6);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.6f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(1.0f / 8.0f, 0.6f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0f / 8.0f, 0.6f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.0f / 8.0f, 0.6f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(4.0f / 8.0f, 0.6f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(5.0f / 8.0f, 0.6f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 6);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.4f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0f / 8.0f, 0.4f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.0f / 8.0f, 0.4f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3.0f / 8.0f, 0.4f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.0f / 8.0f, 0.4f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(5.0f / 8.0f, 0.4f));

		sprite->setAnimationSpeed(JUMPING_UP_R, 6);
		sprite->addKeyframe(JUMPING_UP_R, glm::vec2(6.0f/8.0f, 0.f));

		sprite->setAnimationSpeed(JUMPING_DOWN_R, 6);
		sprite->addKeyframe(JUMPING_DOWN_R, glm::vec2(7.0f/8.0f, 0.f));

		sprite->setAnimationSpeed(JUMPING_UP_L, 6);
		sprite->addKeyframe(JUMPING_UP_R, glm::vec2(6.0f / 8.0f, 0.2f));

		sprite->setAnimationSpeed(JUMPING_DOWN_L, 6);
		sprite->addKeyframe(JUMPING_DOWN_R, glm::vec2(7.0f / 8.0f, 0.2f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32),bJumping))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32),bJumping))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32),bJumping)) {
			bJumping = false;
			posPlayer.y = startY;
		}

		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, true);
			}
		}

	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, true))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition(){
	return posPlayer;
}

glm::ivec2 Player::getBoundingBoxMax() {
	return posPlayer + glm::ivec2(HITBOX_X, HITBOX_Y);
}

glm::ivec2 Player::getBoundingBoxMin() {
	return posPlayer + glm::ivec2(-HITBOX_X, -HITBOX_Y);
}

int Player::getLives() {
	return lives;
}

void Player::setLives(int newLives) {
	lives = newLives;
}

bool Player::isGodMode() {
	return godMode;
}




