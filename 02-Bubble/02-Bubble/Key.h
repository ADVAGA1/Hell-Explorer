#pragma once
#include "Item.h"
class Key : public Item
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) override;

	glm::ivec2 getBoundingBoxMax() override;
	glm::ivec2 getBoundingBoxMin() override;
};

