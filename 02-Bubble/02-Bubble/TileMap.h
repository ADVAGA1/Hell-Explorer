#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <map>
#include <vector>


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size, bool jumping) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, bool jumping) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY, bool player);
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, bool jumping);

	int getCollisionBlock(const glm::ivec2& pos, const glm::ivec2& size);

	std::map<pair<int, int>, bool>& getFloor();
	vector<pair<int, int>>& getLavaMap();
	
private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);
	void checkFloor(int x, int y);
	bool collidable(int tile, bool jumping) const;

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;
	std::map<pair<int, int>, bool> floor;
	std::vector<pair<int, int>> lavaMap;

};


#endif // _TILE_MAP_INCLUDE


