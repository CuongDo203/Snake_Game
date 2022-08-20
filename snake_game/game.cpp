#include "game.h"

const Time Game::timePerFrame = seconds(1.f / 60.f);

//private function
void Game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "Game snake", Style::Default);
	this->window->setFramerateLimit(60);
}

//constuctors / destructors
Game::Game() {
	this->initWindow();
	startGame();
	mainFont.loadFromFile("Fonts/slant_regular.ttf");
	setUpText(&titleText, mainFont, "SNAKE", 28, Color::Yellow);
	FloatRect titleTextBounds = titleText.getLocalBounds();
	titleText.setPosition(Vector2f(this->window->getSize().x / 2 - titleTextBounds.width / 2, -9));

	subFont.loadFromFile("Fonts/PixellettersFull.ttf");
	setUpText(&scoreText, subFont, to_string(score), 28, Color::Yellow);
	FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(this->window->getSize().x - scoreTextBounds.width - 15, -9));

	//game over console
	setUpText(&gameOverText, mainFont, "GAME OVER!", 72, Color::Cyan);
	FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
	gameOverText.setPosition(Vector2f(this->window->getSize().x / 2 - gameOverTextBounds.width / 2, 100));
	gameOverText.setOutlineColor(Color::Black);
	gameOverText.setOutlineThickness(2);

	setUpText(&totalScoreText, mainFont, "Total score: " + to_string(totalScore), 38, Color::Green);
	FloatRect totalScoreTextBounds = totalScoreText.getLocalBounds();
	totalScoreText.setPosition(Vector2f(this->window->getSize().x / 2 - totalScoreTextBounds.width / 2, 200));
	totalScoreText.setOutlineColor(Color::Black);
	totalScoreText.setOutlineThickness(2);

	setUpText(&pressToRestartText, mainFont, "Press N to try again!", 38, Color::Green);
	FloatRect pressToRestartTextBounds = pressToRestartText.getLocalBounds();
	pressToRestartText.setPosition(Vector2f(this->window->getSize().x / 2 - pressToRestartTextBounds.width / 2, 300));
	pressToRestartText.setOutlineColor(Color::Black);
	pressToRestartText.setOutlineThickness(2);

	//set background
	background.setSize(Vector2f(800, 600));
	background_texture.loadFromFile("Texture/grass_background.jpg");
	background.setTexture(&background_texture);
}

Game::~Game() {
	delete this->window;
}


//function

void Game::addDirection(int newDirection) {
	if (directionQueue.empty()) {
		directionQueue.emplace_back(newDirection);
	}
	else {
		if (directionQueue.back() != newDirection) {
			directionQueue.emplace_back(newDirection);
		}
	}
}

void Game::moveFood() {
	//find a place to put food that is not inside the snake

	//divide the screen into small squares with side 20, tru 2 de loai bo tuong
	Vector2f foodResolution = Vector2f(this->window->getSize().x / 20 - 2, this->window->getSize().y / 20 - 2);
	Vector2f newFoodLocation;
	bool badLocation = false;  //vi tri sai
	srand(time(nullptr));
	
	//reduplicate until find a suitable position
	do {
		badLocation = false;
		//generate random location
		newFoodLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.x)) * 20;
		newFoodLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)foodResolution.y)) * 20;

		//ckeck if food is created in the snake section
		for (auto& x : snake) {
			if (x.getShape().getGlobalBounds().intersects(Rect<float>(newFoodLocation.x, newFoodLocation.y, 20, 20))) {
				badLocation = true;
				break;
			}
		}
		
		//check if food is created in the wall section
		for (auto& w : wallSections) {
			if (w.getWallShape().getGlobalBounds().intersects(Rect<float>(newFoodLocation.x, newFoodLocation.y, 20, 20))) {
				badLocation = true;
				break;
			}
		}

	} while (badLocation);
	food.setPosition(newFoodLocation);
}


void Game::createWall()
{
	for (float y = 0; y < this->window->getSize().y; y++) {
		for (float x = 0; x < this->window->getSize().x; x++) {
			if (y == 0 || x == 0) {
				wallSections.emplace_back(Wall(Vector2f(x, y), Vector2f(20.f, 20.f)));
			}
			if (y == this->window->getSize().y - 20 || x == this->window->getSize().x - 20) {
				wallSections.emplace_back(Wall(Vector2f(x, y), Vector2f(20.f, 20.f)));
			}
		}
	}
}

void Game::setUpText(Text* textItem, const Font& font, const string& value, int size, Color color)
{
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(color);
}


//handle game status
void Game::togglePause() {
	if (currentGameState == gameState::RUNNING) {
		lastGameState = currentGameState;
		currentGameState = gameState::PAUSED;
	}
	else if (currentGameState == gameState::PAUSED) {
		currentGameState = lastGameState;
	}
}

void Game::startGame() {
	score = 0;
	totalScore = 0;
	speed = 2;
	snakeDirection = direction::RIGHT;
	timeSinceLastMove = Time::Zero;
	directionQueue.clear();
	sectionsToAdd = 0;
	newSnake();
	moveFood();
	createWall();
	currentGameState = gameState::RUNNING;
	lastGameState = currentGameState;

	scoreText.setString(to_string(score));
	FloatRect scoreTextBounds = scoreText.getLocalBounds();
	scoreText.setPosition(Vector2f(this->window->getSize().x - scoreTextBounds.width - 15, -9));
	
	totalScoreText.setString("Total Score: " + to_string(totalScore));
	FloatRect totalScoreTextBounds = totalScoreText.getLocalBounds();
	totalScoreText.setPosition(Vector2f(this->window->getSize().x / 2 - totalScoreTextBounds.width / 2, 200));
}

void Game::drawTheGame() {
	this->window->clear();
	this->window->draw(background);

	//draw food
	this->window->draw(food.getPrey());

	//draw snake
	for (auto& x : snake) {
		this->window->draw(x.getShape());
	}

	//draw wall
	for (auto& w : wallSections) {
		this->window->draw(w.getWallShape());
	}

	//draw text
	this->window->draw(titleText);
	this->window->draw(scoreText);

	//draw gameOver
	if (currentGameState == gameState::GAMEOVER) {
		this->window->clear();
		this->window->draw(gameOverText);
		this->window->draw(totalScoreText);
		this->window->draw(pressToRestartText);
	}

	this->window->display();
}

void Game::run()
{
	Clock clock;
	//Game loop
	while (this->window->isOpen()) {
		Time dt = clock.restart();

		if (currentGameState == gameState::PAUSED || currentGameState == gameState::GAMEOVER) {
			//if paused, check input(possibly un-paused), then do continue to next loopo
			input();

			//draw the game_over screen
			if (currentGameState == gameState::GAMEOVER) {
				drawTheGame();
			}

			sleep(milliseconds(2));
			continue;
		}

		this->timeSinceLastMove += dt;
		
		input();
		update();
		drawTheGame();
	}

}

//This is the initial snake 
void Game::newSnake() {
	snake.clear();
	snake.emplace_back(Vector2f(100.f, 100.f));
	snake.emplace_back(Vector2f(80.f, 100.f));
	snake.emplace_back(Vector2f(60.f, 100.f));
}

void Game::addSnakeSection()
{
	//add the section at the same position as the last section of snake, it will follow normally
	Vector2f newSectionPos = snake[snake.size() - 1].getPos();
	snake.emplace_back(newSectionPos);
}
