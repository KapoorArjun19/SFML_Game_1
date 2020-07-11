#include "Game.h"

//Private Functions
void Game::initVariables() {
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.0f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}

void Game::initWindow() {
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arjun!");
	this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
	this->enemy.setPosition(10.0f, 10.0f);
	this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
	this->enemy.setFillColor(sf::Color::Cyan);
}


//Constructor / Destructor
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game() {
	delete this->window;
}

//Accessors
const bool Game::running() const {
	return this->window->isOpen();
}

const bool Game::getEndGame() const {
	return this->endGame;
}

//Functions

void Game::spawnEnemy() {
	this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0);

	this->enemy.setFillColor(sf::Color::Cyan);

	this->enemies.push_back(this->enemy);


}

void Game::pollEvents() {
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		default:
			break;
		}
	}
}

void Game::updateMousePosition() {
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->spawnEnemy();
			this->enemySpawnTimer = 0.0f;
		}
		else
			this->enemySpawnTimer += 1.0f;
	}

	//moving and updating enemies
	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].move(0.0f, 3.0f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);

			//lose health
			this->health -= 1;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (this->mouseHeld == false) {
			this->mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++) {

				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//gain points
					this->points += 1;
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}

void Game::update() {
	this->pollEvents();

	if (this->endGame == false) {
		this->updateMousePosition();
		this->updateEnemies();
	}
	
	//end game condition
	if (this->health <= 0)
		this->endGame = true;
}

void Game::renderEnemies() {
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}
}

void Game::render() {
	this->window->clear();

	//Draw game objects
	this->renderEnemies();

	this->window->display();
}