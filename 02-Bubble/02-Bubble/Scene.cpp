#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 24

#define INIT_ENEMY_X_TILES 20
#define INIT_ENEMY_Y_TILES 24


Scene::Scene()
{
	map = NULL;
	player = NULL;
	enemy = NULL;
	floorSprite = NULL;
	bprintFloor = false;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if (enemy != NULL)
		delete enemy;
	if (floorSprite != NULL) {
		floorSprite->free();
		delete floorSprite;
	}
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	enemy = new Skeleton();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize(), INIT_ENEMY_Y_TILES * map->getTileSize()));
	enemy->setTileMap(map);
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	
	spritesheet.loadFromFile("images/tileset.png", TEXTURE_PIXEL_FORMAT_RGBA);
	floorSprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(0.1, 0.1), &spritesheet, &texProgram);
	
	floorSprite->setNumberAnimations(1);
	floorSprite->setAnimationSpeed(0, 8);
	floorSprite->addKeyframe(0, glm::vec2(0.2f, 0.f));
	floorSprite->changeAnimation(0);
	

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

bool Scene::collisionPlayerEnemy(Player* player, Enemy* enemy) {

	glm::ivec2 boundingBoxMaxPlayer = player->getBoundingBoxMax();
	glm::ivec2 boundingBoxMinPlayer = player->getBoundingBoxMin();
	glm::ivec2 boundingBoxMaxEnemy = enemy->getBoundingBoxMax();
	glm::ivec2 boundingBoxMinEnemy = enemy->getBoundingBoxMin();

	
	if (boundingBoxMinPlayer.x < boundingBoxMaxEnemy.x && boundingBoxMinEnemy.x < boundingBoxMaxPlayer.x && boundingBoxMinPlayer.y < boundingBoxMaxEnemy.y && boundingBoxMinEnemy.y < boundingBoxMaxPlayer.y) return true;
	return false;
}

void Scene::update(int deltaTime)
{

	currentTime += deltaTime;

	if (collisionPlayerEnemy(player, enemy)) player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));

	player->update(deltaTime);
	enemy->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();
	player->render();
	enemy->render();
	
	auto& floor = map->getFloor();
	
	for (auto it = floor.begin(); it != floor.end(); ++it) {
		if (it->second) {
			floorSprite->setPosition(glm::vec2(it->first.first * map->getTileSize() + SCREEN_X, it->first.second * map->getTileSize() + SCREEN_Y));
			floorSprite->render();
		}
	}

}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



