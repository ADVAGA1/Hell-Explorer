#include "Ghost.h"

#define FLY_STEP 2
#define HITBOX_X 16
#define HITBOX_Y 16

enum GhostAnims {
    MOVE_UP, MOVE_DOWN,MOVE_LEFT,MOVE_RIGHT
};

void Ghost::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
    spritesheet.loadFromFile("images/ghost.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.0 / 4.0, 1.0 / 2.0), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(2);

    sprite->setAnimationSpeed(MOVE_DOWN, 8);
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.0 / 2.0));
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 1.0 / 2.0));
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(1.0 / 4.0, 0.0 / 2.0));
    sprite->addKeyframe(MOVE_DOWN, glm::vec2(1.0 / 4.0, 1.0 / 2.0));

    sprite->setAnimationSpeed(MOVE_UP, 8);
    sprite->addKeyframe(MOVE_UP, glm::vec2(2.0 / 4.0, 0.0 / 2.0));
    sprite->addKeyframe(MOVE_UP, glm::vec2(2.0 / 4.0, 1.0 / 2.0));
    sprite->addKeyframe(MOVE_UP, glm::vec2(3.0 / 4.0, 0.0 / 2.0));
    sprite->addKeyframe(MOVE_UP, glm::vec2(3.0 / 4.0, 1.0 / 2.0));

    sprite->changeAnimation(0);
    tileMapDispl = tileMapPos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}

void Ghost::update(int deltaTime) {
    sprite->update(deltaTime);

    if (goLeft) {
        if (!map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32))) {
            if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
            posEnemy.x -= 1;
        }
        else goLeft = !goLeft;
    }
    if (goUp) {
        if (!map->collisionMoveLeft(posEnemy, glm::ivec2(32, 32))) {
            if (sprite->animation() != MOVE_UP) sprite->changeAnimation(MOVE_UP);
            posEnemy.y -= 1;
        }
        else goUp = !goUp;
    }

    glm::ivec2 posNextx;
    glm::ivec2 posNexty;
    if (goLeft) posNextx = posEnemy + glm::ivec2(-24, 0);
    else posNextx = posEnemy + glm::ivec2(24, 0);
    if (goUp) posNexty = posEnemy + glm::ivec2(0, -24);
    else posNexty = posEnemy + glm::ivec2(0, 24);

    if (!map->collisionMoveDown(posNextx, glm::ivec2(32, 32), &posEnemy.y))
    {
        if (goLeft) {
            posEnemy.x += 0;
        }
        else {
            posEnemy.x -= 0;
        }
        goLeft = !goLeft;
    }
    if (!map->collisionMoveDown(posNexty, glm::ivec2(32, 32), &posEnemy.y))
    {
        if (goUp) {
            posEnemy.y += 0;
        }
        else {
            posEnemy.y -= 0;
        }
        goUp = !goUp;
    }
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x), float(tileMapDispl.y + posEnemy.y)));
}


glm::ivec2 Ghost::getBoundingBoxMax() {
    return posEnemy + glm::ivec2(HITBOX_X, HITBOX_Y);
}
glm::ivec2 Ghost::getBoundingBoxMin() {
    return posEnemy + glm::ivec2(-HITBOX_X, -HITBOX_Y);
}
