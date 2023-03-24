#include "Vampire.h"
#include <iostream>

#define SLIME_HITBOX_X 24
#define SLIME_HITBOX_Y 24
#define BAT_HITBOX_X 31
#define BAT_HITBOX_Y 26
#define TIME 2  //en segundos
#define LAVA 20

enum VampireAnims {
    MOVE_LEFT, MOVE_RIGHT, FLY_RIGHT, FLY_LEFT
};

void Vampire::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
    spritesheet.loadFromFile("images/vampire.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0f / 5.0f, 1.0f / 4.0f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(4);

    sprite->setAnimationSpeed(MOVE_RIGHT, 8);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f / 5.0f, 1.0f / 4.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0f / 5.0f, 1.0f / 4.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.0f / 5.0f, 1.0f / 4.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3.0f / 5.0f, 1.0f / 4.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.0f / 5.0f, 1.0f / 4.0f));

    sprite->setAnimationSpeed(MOVE_LEFT, 8);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f / 5.0f, 0.0f / 4.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(1.0f / 5.0f, 0.0f / 4.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0f / 5.0f, 0.0f / 4.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.0f / 5.0f, 0.0f / 4.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(4.0f / 5.0f, 0.0f / 4.0f));

    sprite->setAnimationSpeed(FLY_LEFT, 8);
    sprite->addKeyframe(FLY_LEFT, glm::vec2(0.0f / 5.0f, 2.0f / 4.0f));
    sprite->addKeyframe(FLY_LEFT, glm::vec2(1.0f / 5.0f, 2.0f / 4.0f));
    sprite->addKeyframe(FLY_LEFT, glm::vec2(2.0f / 5.0f, 2.0f / 4.0f));
    sprite->addKeyframe(FLY_LEFT, glm::vec2(3.0f / 5.0f, 2.0f / 4.0f));

    sprite->setAnimationSpeed(FLY_RIGHT, 8);
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(0.0f / 5.0f, 3.0f / 4.0f));
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(1.0f / 5.0f, 3.0f / 4.0f));
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(2.0f / 5.0f, 3.0f / 4.0f));
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(3.0f / 5.0f, 3.0f / 4.0f));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
    isBat = false;
    goLeft = true;
    goUp = true;
    isLanding = false;
    timer = TIME * 1000;
}

void Vampire::update(int deltaTime) {
    sprite->update(deltaTime);

    timer -= deltaTime;

    if (timer <= 0) {
        if (isBat) {
            isLanding = true;
        }
        else {
            isBat = true;
            timer = TIME * 1000;
        }
    }

    if (!isBat) {
        if (goLeft) {
            if (!map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32), false)) {
                if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
                posEnemy.x -= 1;
            }
            else {
                goLeft = !goLeft;
                posEnemy.x += 1;
            }
        }
        else {
            if (!map->collisionMoveRight(posEnemy, glm::ivec2(32, 32), false)) {
                if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
                posEnemy.x += 1;
            }
            else {
                goLeft = !goLeft;
                posEnemy.x -= 1;
            }
        }

        posEnemy.y += 4;

        glm::ivec2 posNext;
        if (goLeft) posNext = posEnemy + glm::ivec2(-SLIME_HITBOX_X, 0);
        else posNext = posEnemy + glm::ivec2(SLIME_HITBOX_X, 0);

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

    }
    else {

        if (goUp) {
            if (!map->collisionMoveDown(posEnemy, glm::ivec2(BAT_HITBOX_X, 32 + 1), &posEnemy.y, false)) {
                posEnemy.y += 1;
            }
            else {
                goUp = !goUp;
                startY = posEnemy.y;
                int bloque = map->getCollisionBlock(posEnemy, glm::ivec2(32, 32));
                if (isLanding && bloque != LAVA)
                {
                    isLanding = !isLanding;
                    isBat = !isBat;
                    timer = TIME * 1000;
                }
            }
        }
        else {
            if (!map->collisionMoveUp(posEnemy, glm::ivec2(32, 32), false)) {
                posEnemy.y -= 1;
            }
            else {
                goUp = !goUp;
            }
        }

        if (goLeft) {
            if (!map->collisionMoveLeft(posEnemy, glm::ivec2(32+1, 32), false)) {
                if (sprite->animation() != FLY_LEFT) sprite->changeAnimation(FLY_LEFT);
                posEnemy.x -= 1;
            }
            else {
                goLeft = !goLeft;
                posEnemy.x += 1;
            }
        }
        else {
            if (!map->collisionMoveRight(posEnemy, glm::ivec2(32+1, 32), false)) {
                if (sprite->animation() != FLY_RIGHT) sprite->changeAnimation(FLY_RIGHT);
                posEnemy.x += 1;
            }
            else {
                goLeft = !goLeft;
                posEnemy.x -= 1;
            }
        }
    }

    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}


glm::ivec2 Vampire::getBoundingBoxMax() {
    if(isBat) return posEnemy + glm::ivec2(BAT_HITBOX_X, BAT_HITBOX_Y);
    return posEnemy + glm::ivec2(SLIME_HITBOX_X, SLIME_HITBOX_Y);
}
glm::ivec2 Vampire::getBoundingBoxMin() {
    return posEnemy;
}