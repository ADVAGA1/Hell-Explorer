#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Scene.h"


#define SCREEN_X 32
#define SCREEN_Y 32


#define DMG_TIME 3
#define TIME 61
#define CHRONO_TIME 5


Scene::Scene()
{
	map = NULL;
	player = NULL;
	floorSprite = NULL;
	coin = NULL;
	key = NULL;
	door = NULL;
	chrono = NULL;
	background = NULL;
	heart = NULL;
	clock = NULL;

	for (auto& l : lavas) l = NULL;

	keyTaken = false;
	openDoor = false;
	coinTaken = false;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	for (auto& e : enemies) {
		if (e != NULL) delete e;
	}
	if (floorSprite != NULL) {
		floorSprite->free();
		delete floorSprite;
	}
	if (coin != NULL) delete coin;
	if (door != NULL) delete door;
	if (key != NULL) delete key;
	if (chrono != NULL) delete chrono;
	if (clock != NULL) delete clock;
	if (heart != NULL) {
		heart->free();
		delete heart;
	}
	for (auto& l : lavas) {
		if (l != NULL) delete l;
	}
	if (background != NULL) delete background;
}

void Scene::cleanScene() {

	map = NULL;
	player = NULL;
	floorSprite = NULL;
	coin = NULL;
	key = NULL;
	door = NULL;
	chrono = NULL;
	background = NULL;
	heart = NULL;
	clock = NULL;

	for (auto& l : lavas) l = NULL;
	for (auto& e : enemies) e = NULL;

	keyTaken = false;
	openDoor = false;
	coinTaken = false;
}

void Scene::init(int level, int score)
{
	initShaders();
	cleanScene();

	scene = level;
	this->score = score;

	switch (scene) {
	case 1:
		map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

		enemies = vector<Enemy*>(4);

		enemies[0] = new Skeleton(true);
		enemies[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[0]->setPosition(glm::vec2(6 * map->getTileSize(), 24 * map->getTileSize()));
		enemies[0]->setTileMap(map);

		enemies[1] = new Skeleton(false);
		enemies[1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[1]->setPosition(glm::vec2(28 * map->getTileSize(), 24 * map->getTileSize()));
		enemies[1]->setTileMap(map);

		enemies[2] = new Vampire(true);
		enemies[2]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[2]->setPosition(glm::vec2(26 * map->getTileSize(), 12 * map->getTileSize()));
		enemies[2]->setTileMap(map);

		enemies[3] = new Vampire(false);
		enemies[3]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[3]->setPosition(glm::vec2(8 * map->getTileSize(), 12 * map->getTileSize()));
		enemies[3]->setTileMap(map);

		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2(6 * map->getTileSize(), 4 * map->getTileSize()));
		player->setTileMap(map);

		backgroundTexture.loadFromFile("images/background1.png", TEXTURE_PIXEL_FORMAT_RGBA);
		background = Sprite::createSprite(glm::vec2(16 * 36, 16 * 28), glm::vec2(1, 1), &backgroundTexture, &texProgram);
		background->setPosition(glm::vec2(SCREEN_X, SCREEN_Y));

		door = new Door();
		door->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		door->setPosition(glm::vec2(20 * map->getTileSize(), 3 * map->getTileSize()));
		door->setTileMap(map);
		break;
	case 2:
		map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

		enemies = vector<Enemy*>(7);

		enemies[0] = new Skeleton(true);
		enemies[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[0]->setPosition(glm::vec2(11 * map->getTileSize(), 12 * map->getTileSize()));
		enemies[0]->setTileMap(map);

		enemies[1] = new Skeleton(false);
		enemies[1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[1]->setPosition(glm::vec2(2 * map->getTileSize(), 16 * map->getTileSize()));
		enemies[1]->setTileMap(map);

		enemies[2] = new Skeleton(false);
		enemies[2]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[2]->setPosition(glm::vec2(24 * map->getTileSize(), 12 * map->getTileSize()));
		enemies[2]->setTileMap(map);

		enemies[3] = new Skeleton(true);
		enemies[3]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[3]->setPosition(glm::vec2(33 * map->getTileSize(), 16 * map->getTileSize()));
		enemies[3]->setTileMap(map);

		enemies[4] = new Ghost(false);
		enemies[4]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[4]->setPosition(glm::vec2(4 * map->getTileSize(), 3 * map->getTileSize()));
		enemies[4]->setTileMap(map);

		enemies[5] = new Ghost(true);
		enemies[5]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[5]->setPosition(glm::vec2(30 * map->getTileSize(), 3 * map->getTileSize()));
		enemies[5]->setTileMap(map);

		enemies[6] = new Vampire(false);
		enemies[6]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[6]->setPosition(glm::vec2(12 * map->getTileSize(), 4 * map->getTileSize()));
		enemies[6]->setTileMap(map);

		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2(4 * map->getTileSize(), 24 * map->getTileSize()));
		player->setTileMap(map);

		backgroundTexture.loadFromFile("images/background2.png", TEXTURE_PIXEL_FORMAT_RGBA);
		background = Sprite::createSprite(glm::vec2(16 * 36, 16 * 28), glm::vec2(1, 1), &backgroundTexture, &texProgram);
		background->setPosition(glm::vec2(SCREEN_X, SCREEN_Y));

		door = new Door();
		door->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		door->setPosition(glm::vec2(15 * map->getTileSize(), 3 * map->getTileSize()));
		door->setTileMap(map);
		break;
	case 3:
		map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

		enemies = vector<Enemy*>(4);

		enemies[0] = new Skeleton(true);
		enemies[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[0]->setPosition(glm::vec2(17 * map->getTileSize(), 8 * map->getTileSize()));
		enemies[0]->setTileMap(map);

		enemies[1] = new Skeleton(false);
		enemies[1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[1]->setPosition(glm::vec2(18 * map->getTileSize(), 16 * map->getTileSize()));
		enemies[1]->setTileMap(map);

		enemies[2] = new Vampire(false);
		enemies[2]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[2]->setPosition(glm::vec2(11 * map->getTileSize(), 20 * map->getTileSize()));
		enemies[2]->setTileMap(map);

		enemies[3] = new Vampire(true);
		enemies[3]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		enemies[3]->setPosition(glm::vec2(26 * map->getTileSize(), 20 * map->getTileSize()));
		enemies[3]->setTileMap(map);

		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2(9 * map->getTileSize(), 4 * map->getTileSize()));
		player->setTileMap(map);

		backgroundTexture.loadFromFile("images/background3.png", TEXTURE_PIXEL_FORMAT_RGBA);
		background = Sprite::createSprite(glm::vec2(16 * 36, 16 * 28), glm::vec2(1, 1), &backgroundTexture, &texProgram);
		background->setPosition(glm::vec2(SCREEN_X, SCREEN_Y));

		door = new Door();
		door->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		door->setPosition(glm::vec2(9 * map->getTileSize(), 23 * map->getTileSize()));
		door->setTileMap(map);

		break;
	default:
		break;
	}

	

	spritesheet.loadFromFile("images/tileset.png", TEXTURE_PIXEL_FORMAT_RGBA);
	floorSprite = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(0.1, 0.1), &spritesheet, &texProgram);

	floorSprite->setNumberAnimations(1);
	floorSprite->setAnimationSpeed(0, 8);
	floorSprite->addKeyframe(0, glm::vec2(0.2f, 0.f));
	floorSprite->changeAnimation(0);
	
	coin = new Coin();
	coin->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	coin->setTileMap(map);
	
	key = new Key();
	key->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	key->setTileMap(map);

	chrono = new Chrono();
	chrono->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	chrono->setTileMap(map);

	clock = new Clock();
	clock->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	clock->setTileMap(map);

	heartTexture.loadFromFile("images/heart.png", TEXTURE_PIXEL_FORMAT_RGBA);
	heart = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(1, 1), &heartTexture, &texProgram);
	heart->setNumberAnimations(1);
	heart->setAnimationSpeed(0, 8);
	heart->addKeyframe(0, glm::vec2(0, 0));
	heart->changeAnimation(0);

	vector<pair<int, int>> lavaMap = map->getLavaMap();
	lavas.clear();

	for (auto& coord : lavaMap) {
		Lava* l = new Lava();
		l->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		l->setPosition(glm::vec2(coord.first * map->getTileSize(), coord.second * map->getTileSize()));
		l->setTileMap(map);
		lavas.push_back(l);
	}



	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	if (!text.init("fonts/Minecraft.ttf")) cout << "Could not load font!!!" << endl;

	keyTaken = false;
	openDoor = false;
	coinTaken = false;
	keySpawn = false;
	coinSpawn = false;
	chronoSpawn = false;
	isStoped = false;
	chronoTaken = false;
	clockTaken = false;
	coinSpawn = false;
	chronoSpawn = false;
	clockSpawn = false;
	hasBeenDamaged = false;
	damaged = false;
	win = false;
	lose = false;
	chronoTimer = CHRONO_TIME * 1000;
	timer = TIME * 1000;
	lastTime = timer;

	auto& floor = map->getFloor();
	floorCheck = vector<pair<pair<int,int>, bool>>(floor.size());

	int i = 0;
	for (auto& f : floor) {
		floorCheck[i] = { {f.first.first,f.first.second},false };
		++i;
	}

}

bool Scene::collisionPlayerEnemy(Player* player, Enemy* enemy) {

	glm::ivec2 boundingBoxMaxPlayer = player->getBoundingBoxMax();
	glm::ivec2 boundingBoxMinPlayer = player->getBoundingBoxMin();
	glm::ivec2 boundingBoxMaxEnemy = enemy->getBoundingBoxMax();
	glm::ivec2 boundingBoxMinEnemy = enemy->getBoundingBoxMin();

	
	if (boundingBoxMinPlayer.x < boundingBoxMaxEnemy.x && boundingBoxMinEnemy.x < boundingBoxMaxPlayer.x && boundingBoxMinPlayer.y < boundingBoxMaxEnemy.y && boundingBoxMinEnemy.y < boundingBoxMaxPlayer.y) return true;
	return false;
}

bool Scene::collisionPlayerItem(Player* player, Item* item) {
	glm::ivec2 boundingBoxMaxPlayer = player->getBoundingBoxMax();
	glm::ivec2 boundingBoxMinPlayer = player->getBoundingBoxMin();
	glm::ivec2 boundingBoxMaxItem = item->getBoundingBoxMax();
	glm::ivec2 boundingBoxMinItem = item->getBoundingBoxMin();


	if (boundingBoxMinPlayer.x < boundingBoxMaxItem.x && boundingBoxMinItem.x < boundingBoxMaxPlayer.x && boundingBoxMinPlayer.y < boundingBoxMaxItem.y && boundingBoxMinItem.y < boundingBoxMaxPlayer.y) return true;
	return false;
}

void Scene::update(int deltaTime)
{

	currentTime += deltaTime;

	if(!isStoped) timer -= deltaTime;

	//Coin timer
	if (!coinSpawn && timer <= (TIME - 5) * 1000) {
		switch (scene)
		{
		case 1:
			coin->setPosition(glm::vec2(12 * map->getTileSize(), 24 * map->getTileSize()));
			break;
		case 2:
			coin->setPosition(glm::vec2(10 * map->getTileSize(), 16 * map->getTileSize()));
			break;
		case 3:
			coin->setPosition(glm::vec2(28 * map->getTileSize(), 24 * map->getTileSize()));
			break;
		default:
			break;
		}
		coinSpawn = true;
	}

	if (coinSpawn && timer <= (TIME - 25) * 1000) {
		coinTaken = true;
		coin->setPosition(glm::vec2(0, 0));
	}

	//Chrono timer
	if (timer <= (TIME - 10) * 1000 && !chronoSpawn) {
		switch (scene)
		{
		case 1:
			chrono->setPosition(glm::vec2(8 * map->getTileSize(), 12 * map->getTileSize()));
			break;
		case 2:
			chrono->setPosition(glm::vec2(28 * map->getTileSize(), 16 * map->getTileSize()));
			break;
		case 3:
			chrono->setPosition(glm::vec2(23 * map->getTileSize(), 16 * map->getTileSize()));
			break;
		default:
			break;
		}
		chronoSpawn = true;
	}

	if (chronoSpawn && timer <= (TIME - 30) * 1000) {
		chronoTaken = true;
		chrono->setPosition(glm::vec2(0, 0));
	}

	//Clock timer
	if (timer <= (TIME - 30) * 1000 && !clockSpawn) {
		switch (scene)
		{
		case 1:
			clock->setPosition(glm::vec2(23 * map->getTileSize(), 24 * map->getTileSize()));
			break;
		case 2:
			clock->setPosition(glm::vec2(28 * map->getTileSize(), 24 * map->getTileSize()));
			break;
		case 3:
			clock->setPosition(glm::vec2(22 * map->getTileSize(), 4 * map->getTileSize()));
			break;
		default:
			break;
		}
		clockSpawn = true;
	}

	if (clockSpawn && timer <= (TIME - 45) * 1000) {
		clockTaken = true;
		clock->setPosition(glm::vec2(0, 0));
	}

	//1 second decrement
	if (lastTime - timer >= 1000) {
		lastTime = timer;
	}

	//time over
	if (timer <= 0) lose = true;

	//got damaged
	if (damaged) {
		damageTimer = DMG_TIME * 1000;
		damaged = false;
		hasBeenDamaged = true;
		player->changeInvulnerable(true);
	}

	if(hasBeenDamaged) damageTimer -= deltaTime;

	if (hasBeenDamaged && damageTimer <= 0) {
		hasBeenDamaged = false;
		player->changeInvulnerable(false);
	}

	if (isStoped) chronoTimer -= deltaTime;

	if (chronoTimer <= 0) {
		isStoped = false;
		chronoTimer = CHRONO_TIME * 1000;
	}

	//collision with enemies
	for (auto& enemy : enemies) {
		if (collisionPlayerEnemy(player, enemy) && !player->isGodMode()) {
			if (!hasBeenDamaged) {
				if (player->getLives() == 1) {
					lose = true;
				}
				else player->setLives(player->getLives() - 1);
				damaged = true;
			}
		}
	}

	//collision with lava
	for (auto& lava: lavas) {
		if (collisionPlayerEnemy(player, lava) && !player->isGodMode()) {
			if (!hasBeenDamaged) {
				if (player->getLives() == 1) {
					lose = true;
				}
				else player->setLives(player->getLives() - 1);
				damaged = true;
			}
			break;
		}
	}

	//collision with key
	if (keySpawn && collisionPlayerItem(player, key)) {
		keyTaken = true;
		door->openDoor();
		key->setPosition(glm::ivec2(0, 0));
	}

	//collision with chrono
	if (chronoSpawn && collisionPlayerItem(player, chrono)) {
		isStoped = true;
		chronoTaken = true;
		chrono->setPosition(glm::ivec2(0, 0));
	}

	//collision with coin
	if (coinSpawn && collisionPlayerItem(player, coin)) {
		coinTaken = true;
		score += 500;
		coin->setPosition(glm::vec2(0, 0));
	}

	//collision with clock
	if (clockSpawn && collisionPlayerItem(player, clock)) {
		clockTaken = true;
		timer += 30 * 1000;
		clock->setPosition(glm::vec2(0, 0));
	}

	//collision with door
	if (keyTaken && collisionPlayerItem(player, door)) {
		win = true;
	}

	player->update(deltaTime);

	if (!isStoped) {
		for (auto& enemy : enemies)
			enemy->update(deltaTime);
	}
	
	if(!coinTaken) coin->update(deltaTime);

	door->update(deltaTime);

	for (auto& l : lavas) {
		l->update(deltaTime);
	}

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

	background->render();

	for (int i = 0; i < player->getLives(); ++i) {
		heart->setPosition(glm::ivec2(16+20*i,8));
		heart->render();
	}

	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();

	for (auto& l : lavas) {
		l->render();
	}

	door->render();

	if (coinSpawn && !coinTaken) coin->render();

	if (chronoSpawn && !chronoTaken) chrono->render();

	if (clockSpawn && !clockTaken) clock->render();
	
	auto& floor = map->getFloor();
	int changedFloors = floor.size();

	int i = 0;
	for (auto it = floor.begin(); it != floor.end() && changedFloors > 0 ; ++it) {
		if (it->second) {

			if (!floorCheck[i].second && floorCheck[i].first.first == it->first.first && floorCheck[i].first.second == it->first.second) {
				floorCheck[i].second = true;
				score += 10;
			}

			floorSprite->setPosition(glm::vec2(it->first.first * map->getTileSize() + SCREEN_X, it->first.second * map->getTileSize() + SCREEN_Y));
			floorSprite->render();
			--changedFloors;
		}
		++i;
	}

	if (changedFloors == 0) keySpawn = true;

	if (keySpawn && !keyTaken) {
		key->render();
		switch (scene) {
		case 1:
			key->setPosition(glm::vec2(4 * map->getTileSize(), 24 * map->getTileSize()));
			break;
		case 2:
			key->setPosition(glm::vec2(17 * map->getTileSize(), 11 * map->getTileSize()));
			break;
		case 3:
			key->setPosition(glm::vec2(25 * map->getTileSize(), 24 * map->getTileSize()));
			break;
		}
	}

	for (auto& enemy : enemies)
		enemy->render();

	player->render();
	
	text.render(to_string(timer/1000), glm::vec2(640 / 2, 8 + 16), 24, glm::vec4(1, 1, 1, 1));
	text.render(to_string(score), glm::vec2(640 / 2 - 180, 8 + 16), 24, glm::vec4(1, 1, 1, 1));
	text.render("Stage  " + to_string(scene), glm::vec2(640 / 2 + 180, 8 + 16), 24, glm::vec4(1, 1, 1, 1));
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

void Scene::reset() {
	init(scene, score);
}

void Scene::changeGodMode() {
	if (player->isGodMode()) {
		player->setGodMode(false);
		cout << "God mode disabled" << endl;
	}
	else {
		player->setGodMode(true);
		cout << "God mode enabled" << endl;
	}
}

void Scene::spawnKey() {
	if (!keySpawn) cout << "Key Spawned" << endl;
	keySpawn = true;
}


