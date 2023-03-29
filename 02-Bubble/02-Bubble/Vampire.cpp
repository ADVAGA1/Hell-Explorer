#include "Vampire.h"
#include <iostream>

#define SLIME_HITBOX_X 24
#define SLIME_HITBOX_Y 24
#define BAT_HITBOX_X 16
#define BAT_HITBOX_Y 16
#define TIME 5  //en segundos
#define LAVA 20

enum VampireState {
    VAMPIRE, BAT, CHANGE
};

enum VampireAnims {
    MOVE_LEFT, MOVE_RIGHT, FLY_RIGHT, FLY_LEFT, TRANSFORM
};

Vampire::Vampire(bool left) {
    goLeft = left;
}

void Vampire::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
    spritesheet.loadFromFile("images/vampire.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0f / 5.0f, 1.0f / 5.0f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(4);

    sprite->setAnimationSpeed(MOVE_RIGHT, 8);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.0f / 5.0f, 1.0f / 5.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1.0f / 5.0f, 1.0f / 5.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2.0f / 5.0f, 1.0f / 5.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3.0f / 5.0f, 1.0f / 5.0f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4.0f / 5.0f, 1.0f / 5.0f));

    sprite->setAnimationSpeed(MOVE_LEFT, 8);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.0f / 5.0f, 0.0f / 5.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(1.0f / 5.0f, 0.0f / 5.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(2.0f / 5.0f, 0.0f / 5.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(3.0f / 5.0f, 0.0f / 5.0f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(4.0f / 5.0f, 0.0f / 5.0f));

    sprite->setAnimationSpeed(FLY_LEFT, 8);
    sprite->addKeyframe(FLY_LEFT, glm::vec2(0.0f / 5.0f, 2.0f / 5.0f));
    sprite->addKeyframe(FLY_LEFT, glm::vec2(1.0f / 5.0f, 2.0f / 5.0f));
    sprite->addKeyframe(FLY_LEFT, glm::vec2(2.0f / 5.0f, 2.0f / 5.0f));
    sprite->addKeyframe(FLY_LEFT, glm::vec2(3.0f / 5.0f, 2.0f / 5.0f));

    sprite->setAnimationSpeed(FLY_RIGHT, 8);
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(0.0f / 5.0f, 3.0f / 5.0f));
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(1.0f / 5.0f, 3.0f / 5.0f));
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(2.0f / 5.0f, 3.0f / 5.0f));
    sprite->addKeyframe(FLY_RIGHT, glm::vec2(3.0f / 5.0f, 3.0f / 5.0f));

    sprite->setAnimationSpeed(TRANSFORM, 8);
    sprite->addKeyframe(TRANSFORM, glm::vec2(0.0f / 5.0f, 3.0f / 5.0f));
    sprite->addKeyframe(TRANSFORM, glm::vec2(1.0f / 5.0f, 3.0f / 5.0f));
    sprite->addKeyframe(TRANSFORM, glm::vec2(2.0f / 5.0f, 3.0f / 5.0f));
    sprite->addKeyframe(TRANSFORM, glm::vec2(3.0f / 5.0f, 3.0f / 5.0f));


    if (goLeft) sprite->changeAnimation(MOVE_LEFT);
    else sprite->changeAnimation(MOVE_RIGHT);
    tileMapDispl = tileMapPos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
    isBat = false;
    goUp = true;
    isLanding = false;
    timer = TIME * 1000;
    transformTimer = 200;
    currentState = VAMPIRE;
}

void Vampire::update(int deltaTime) {
    sprite->update(deltaTime);

    timer -= deltaTime;

    if (timer <= 0) {

        if (isBat) {
            isLanding = true;
        }
        else {
            if (transformTimer <= 0) {
                isBat = true;
                timer = TIME * 1000;
                transformTimer = 200;
            }
            
            transformTimer -= deltaTime;
            sprite->changeAnimation(TRANSFORM);

        }
    }

    glm::ivec2 posNext;
    

    if (!isBat) {

        if (goLeft) posNext = posEnemy + glm::ivec2(0, SLIME_HITBOX_Y);
        else posNext = posEnemy + glm::ivec2(SLIME_HITBOX_X, SLIME_HITBOX_Y);

        int nextTile = map->checkTile(posNext.x / map->getTileSize(), posNext.y / map->getTileSize());

        if (!map->collidable(nextTile,false))
        {
            goLeft = !goLeft;
        }
        
        if (goLeft) {
            if (!map->collisionMoveLeft(posEnemy, glm::ivec2(SLIME_HITBOX_X, SLIME_HITBOX_Y), false)) {
                if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
                posEnemy.x -= 1;
            }
            else {
                goLeft = !goLeft;
                posEnemy.x += 1;
            }
        }
        else {
            if (!map->collisionMoveRight(posEnemy, glm::ivec2(SLIME_HITBOX_X, SLIME_HITBOX_Y), false)) {
                if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
                posEnemy.x += 1;
            }
            else {
                goLeft = !goLeft;
                posEnemy.x -= 1;
            }
        }

    }
    else {
        
        if (isLanding)
        {
            posNext = posEnemy + glm::ivec2(BAT_HITBOX_X/2, BAT_HITBOX_Y);
            int nextTile = map->checkTile(posNext.x / map->getTileSize(), posNext.y / map->getTileSize());

            if (nextTile == 2) {
                isLanding = false;
                isBat = false;
                sprite->changeAnimation(TRANSFORM);
                posEnemy.y -= SLIME_HITBOX_Y - BAT_HITBOX_Y;
                timer = TIME * 1000;
            }
            else {
                if (goLeft) {
                    if (!map->collisionMoveLeft(posEnemy, glm::ivec2(BAT_HITBOX_X+1, BAT_HITBOX_Y), false)) {
                        if (sprite->animation() != FLY_LEFT) sprite->changeAnimation(FLY_LEFT);
                        posEnemy.x -= 1;
                    }
                    else {
                        goLeft = !goLeft;
                        posEnemy.x += 1;
                    }
                }
                else {
                    if (!map->collisionMoveRight(posEnemy, glm::ivec2(BAT_HITBOX_X+1, BAT_HITBOX_Y), false)) {
                        if (sprite->animation() != FLY_RIGHT) sprite->changeAnimation(FLY_RIGHT);
                        posEnemy.x += 1;
                    }
                    else {
                        goLeft = !goLeft;
                        posEnemy.x -= 1;
                    }
                }

                if (nextTile == LAVA) goUp = true;

                if (map->collisionMoveUp(glm::ivec2(posEnemy.x,posEnemy.y-1), glm::ivec2(BAT_HITBOX_X, BAT_HITBOX_Y), false)) goUp = false;

                if (goUp) posEnemy.y -= 1;
                else posEnemy.y += 1;

            }

        }
        else {
            if (!goUp) {
                if (!map->collisionMoveDown(posEnemy, glm::ivec2(BAT_HITBOX_X, BAT_HITBOX_Y + 1), &posEnemy.y, false)) {
                    posEnemy.y += 1;
                }
                else goUp = !goUp;
            }
            else {
                if (!map->collisionMoveUp(posEnemy, glm::ivec2(BAT_HITBOX_X, BAT_HITBOX_Y), false)) {
                    posEnemy.y -= 1;
                }
                else {
                    goUp = !goUp;
                }
            }

            if (goLeft) {
                if (!map->collisionMoveLeft(posEnemy, glm::ivec2(BAT_HITBOX_X+1, BAT_HITBOX_Y), false)) {
                    if (sprite->animation() != FLY_LEFT) sprite->changeAnimation(FLY_LEFT);
                    posEnemy.x -= 1;
                }
                else {
                    goLeft = !goLeft;
                    posEnemy.x += 1;
                }
            }
            else {
                if (!map->collisionMoveRight(posEnemy, glm::ivec2(BAT_HITBOX_X + 1, BAT_HITBOX_Y), false)) {
                    if (sprite->animation() != FLY_RIGHT) sprite->changeAnimation(FLY_RIGHT);
                    posEnemy.x += 1;
                }
                else {
                    goLeft = !goLeft;
                    posEnemy.x -= 1;
                }
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

void Vampire::setPosition(const glm::vec2& pos)
{
    posEnemy = pos;
    posEnemy += glm::ivec2(0, 32 - SLIME_HITBOX_Y);
    startY = int(posEnemy.y);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}