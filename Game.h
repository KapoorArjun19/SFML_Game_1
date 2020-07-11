#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private Functions
	void initVariables();
	void initWindow();
	void initEnemies();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Member Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePosition();
	void updateEnemies();
	void update();

	void renderEnemies();
	void render();
};