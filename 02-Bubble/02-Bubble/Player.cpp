#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 80
#define FALL_STEP 4

#define HITBOX_X 32
#define HITBOX_Y 32


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMPING_UP_R, JUMPING_DOWN_R, JUMPING_UP_L, JUMPING_DOWN_L, DAMAGED_RIGHT, DAMAGED_LEFT, DAMAGED_MOVE_RIGHT, DAMAGED_MOVE_LEFT, SPAWN, KILLED
};

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int nLives)
{
	lives = nLives;
	bJumping = false;
	godMode = false;
	invulnerable = false;
	goLeft = false;
	spritesheet.loadFromFile("images/player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0/8.0, 0.20), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(14);
	
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

		sprite->setAnimationSpeed(DAMAGED_RIGHT, 10);
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(1.0f / 8.0f, 0.f));
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(2.0f / 8.0f, 0.f));
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(3.0f / 8.0f, 0.f));
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(4.0f / 8.0f, 0.f));
		sprite->addKeyframe(DAMAGED_RIGHT, glm::vec2(5.0f / 8.0f, 0.f));

		sprite->setAnimationSpeed(DAMAGED_LEFT, 10);
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(0.f, 0.2f));
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(1.0f / 8.0f, 0.2f));
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(2.0f / 8.0f, 0.2f));
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(3.0f / 8.0f, 0.2f));
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(4.0f / 8.0f, 0.2f));
		sprite->addKeyframe(DAMAGED_LEFT, glm::vec2(5.0f / 8.0f, 0.2f));

		sprite->setAnimationSpeed(DAMAGED_MOVE_RIGHT, 10);
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(0.f, 0.4f));
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(1.0f / 8.0f, 0.4f));
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(2.0f / 8.0f, 0.4f));
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(3.0f / 8.0f, 0.4f));
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(4.0f / 8.0f, 0.4f));
		sprite->addKeyframe(DAMAGED_MOVE_RIGHT, glm::vec2(5.0f / 8.0f, 0.4f));

		sprite->setAnimationSpeed(DAMAGED_MOVE_LEFT, 10);
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(0.f, 0.6f));
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(1.0f / 8.0f, 0.6f));
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(2.0f / 8.0f, 0.6f));
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(3.0f / 8.0f, 0.6f));
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(7.0f / 8.0f, 0.8f));
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(4.0f / 8.0f, 0.6f));
		sprite->addKeyframe(DAMAGED_MOVE_LEFT, glm::vec2(5.0f / 8.0f, 0.6f));

		sprite->setAnimationSpeed(SPAWN, 10);
		sprite->addKeyframe(SPAWN, glm::vec2(0.0f / 8.0f, 0.8f));
		sprite->addKeyframe(SPAWN, glm::vec2(1.0f / 8.0f, 0.8f));
		sprite->addKeyframe(SPAWN, glm::vec2(2.0f / 8.0f, 0.8f));
		sprite->addKeyframe(SPAWN, glm::vec2(3.0f / 8.0f, 0.8f));
		sprite->addKeyframe(SPAWN, glm::vec2(4.0f / 8.0f, 0.8f));
		sprite->addKeyframe(SPAWN, glm::vec2(7.0f / 8.0f, 0.8f));

		sprite->setAnimationSpeed(KILLED, 6);
		sprite->addKeyframe(KILLED, glm::vec2(6.0f / 8.0f, 0.6f));
		sprite->addKeyframe(KILLED, glm::vec2(7.0f / 8.0f, 0.6f));
		sprite->addKeyframe(KILLED, glm::vec2(0.0f / 8.0f, 0.8f));
		sprite->addKeyframe(KILLED, glm::vec2(1.0f / 8.0f, 0.8f));
		sprite->addKeyframe(KILLED, glm::vec2(2.0f / 8.0f, 0.8f));
		sprite->addKeyframe(KILLED, glm::vec2(3.0f / 8.0f, 0.8f));
		sprite->addKeyframe(KILLED, glm::vec2(4.0f / 8.0f, 0.8f));
		sprite->addKeyframe(KILLED, glm::vec2(7.0f / 8.0f, 0.8f));

		
	sprite->changeAnimation(SPAWN);
	spawning = true;
	ending = false;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	runTimer = 350;
	spawnTimer = 1000;
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (spawning && spawnTimer > 0) spawnTimer -= deltaTime;

	if (spawning && spawnTimer <= 0) {
		spawning = false;
		sprite->changeAnimation(STAND_RIGHT);
	}

	if (!spawning && !ending) {

		runTimer -= deltaTime;

		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{

			goLeft = true;
			if (invulnerable) {
				if (sprite->animation() != DAMAGED_MOVE_LEFT) sprite->changeAnimation(DAMAGED_MOVE_LEFT);
			}
			else {
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
			}

			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(HITBOX_X, HITBOX_Y), bJumping))
			{
				posPlayer.x += 2;

				if (invulnerable) sprite->changeAnimation(DAMAGED_LEFT);
				else sprite->changeAnimation(STAND_LEFT);
			}
			else {

				if (!bJumping && runTimer <= 0) {
					Game::instance().playSound("sound/run.wav");
					runTimer = 350;
				}
			}

		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{

			goLeft = false;
			if (invulnerable) {
				if (sprite->animation() != DAMAGED_MOVE_RIGHT) sprite->changeAnimation(DAMAGED_MOVE_RIGHT);
			}
			else {
				if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
			}
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(HITBOX_X, HITBOX_Y), bJumping))
			{
				posPlayer.x -= 2;

				if (invulnerable) sprite->changeAnimation(DAMAGED_RIGHT);
				else sprite->changeAnimation(STAND_RIGHT);
			}
			else {

				if (!bJumping && runTimer <= 0) {
					Game::instance().playSound("sound/run.wav");
					runTimer = 350;
				}
			}

		}
		else
		{
			if (sprite->animation() == MOVE_LEFT) sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT) sprite->changeAnimation(STAND_RIGHT);

			if (invulnerable) {
				if (sprite->animation() == DAMAGED_MOVE_LEFT) sprite->changeAnimation(DAMAGED_LEFT);
				else if (sprite->animation() == DAMAGED_MOVE_RIGHT) sprite->changeAnimation(DAMAGED_RIGHT);
			}

		}

		if (bJumping)
		{
			if (map->collisionMoveUp(glm::ivec2(posPlayer.x,posPlayer.y), glm::ivec2(HITBOX_X, 1), bJumping)) {
				bJumping = false;
				posPlayer.y = startY;
			}

			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				//posPlayer.y = startY;
			}
			else
			{
				posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90) {
					bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(HITBOX_X, HITBOX_Y), &posPlayer.y, true);
				}
			}

		}
		else
		{
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(HITBOX_X, HITBOX_Y), &posPlayer.y, true))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					Game::instance().playSound("sound/jump.wav");
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
			else {
				runTimer = 200;
			}
		}
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
	
}

void Player::updateSprite(int deltaTime) {
	sprite->updateLoopless(deltaTime);
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
	return posPlayer + glm::ivec2(0, 0);
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

void Player::changeInvulnerable(bool inv) {
	this->invulnerable = inv;
	if (inv == false) {
		if (goLeft) sprite->changeAnimation(STAND_LEFT);
		else sprite->changeAnimation(STAND_RIGHT);
	}
	else {
		if (goLeft) sprite->changeAnimation(DAMAGED_LEFT);
		else sprite->changeAnimation(DAMAGED_RIGHT);
	}
}

void Player::setGodMode(bool b) {
	godMode = b;
}

void Player::end(bool dead) {
	if (dead) sprite->changeAnimation(KILLED);
	else sprite->changeAnimation(SPAWN);
	ending = true;
}


