#pragma once
#include "Enemy.h"
class Vampire : public Enemy
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;
	void update(int deltaTime) override;

	glm::ivec2 getBoundingBoxMax() override;
	glm::ivec2 getBoundingBoxMin() override;

private:
	bool isBat, goLeft, goUp, isLanding;
	int timer;
};

