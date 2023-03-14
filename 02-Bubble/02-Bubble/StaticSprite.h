#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"

class StaticSprite
{

private:
	StaticSprite(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program);

public:
	// Textured quads can only be created inside an OpenGL context
	static StaticSprite* createSprite(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* spritesheet, ShaderProgram* program);

	void render() const;
	void free();

	void setPosition(const glm::vec2& pos);

private:
	Texture* texture;
	ShaderProgram* shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 position;
	glm::vec2 texCoordDispl;
};

