#pragma once
#include "Enemy.h"
class Vampire : public Enemy
{
public:

	Vampire(bool left);

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;

	glm::ivec2 getBoundingBoxMax() override;
	glm::ivec2 getBoundingBoxMin() override;

	void setPosition(const glm::vec2& pos) override;

private:
	bool isBat, goLeft, goUp, isLanding;
	int timer, transformTimer, currentState;
};

