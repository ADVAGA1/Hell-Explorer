#include "StaticSprite.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>


StaticSprite* StaticSprite::createSprite(const glm::vec2& quadSize, const glm::vec2& sizeInStaticSpritesheet, Texture* StaticSpritesheet, ShaderProgram* program)
{
	StaticSprite* quad = new StaticSprite(quadSize, sizeInStaticSpritesheet, StaticSpritesheet, program);

	return quad;
}


StaticSprite::StaticSprite(const glm::vec2& quadSize, const glm::vec2& sizeInSpritesheet, Texture* StaticSpritesheet, ShaderProgram* program)
{
	float vertices[24] = { 0.f, 0.f, 0.f, 0.f,
												quadSize.x, 0.f, sizeInSpritesheet.x, 0.f,
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y,
												0.f, 0.f, 0.f, 0.f,
												quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y,
												0.f, quadSize.y, 0.f, sizeInSpritesheet.y };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	texture = StaticSpritesheet;
	shaderProgram = program;
	position = glm::vec2(0.f);
}

void StaticSprite::render() const
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void StaticSprite::free()
{
	glDeleteBuffers(1, &vbo);
}

void StaticSprite::setPosition(const glm::vec2& pos)
{
	position = pos;
}
