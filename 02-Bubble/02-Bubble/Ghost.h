#pragma once

#include "Enemy.h"

class Ghost : public Enemy
{
public:

	Ghost(bool left);

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;

	glm::ivec2 getBoundingBoxMax() override;
	glm::ivec2 getBoundingBoxMin() override;

private:
	bool goLeft;
	bool goUp = true;
};

