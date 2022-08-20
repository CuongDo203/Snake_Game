#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <deque>
#include <fstream>
#include "SnakeSection.h"
#include "Food.h"
#include "Wall.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;
/*
	Class acts as the game engine
	Wrapper class.
*/

class Game
{
private:
	//Variables
	//window
	RenderWindow* window;	//main window
	Event ev;
	VideoMode videoMode;
	static const Time timePerFrame;
	
	//Game objects
	vector<SnakeSection> snake;
	Food food;
	vector<Wall> wallSections;

	//private function
	void initWindow();

	//property
	int snakeDirection;
	deque<int> directionQueue;	//queue for direction key presses
	int speed;
	int sectionsToAdd;  //how many parts to add to the snake
	unsigned long long score;  //stored score
	unsigned long long totalScore;

	Time timeSinceLastMove;

	int currentGameState;
	int lastGameState; //Store game state when paused

	//Font and text
	Font mainFont;
	Text titleText;
	Font subFont;
	Text scoreText;
	Text totalScoreText;
	Text gameOverText;
	Text pressToRestartText;

	RectangleShape background;
	Texture background_texture;
public:
	enum direction { UP, LEFT, DOWN, RIGHT };
	enum gameState {RUNNING, PAUSED, GAMEOVER, MAINMENU};
	//constructors / destructors
	Game();
	virtual ~Game();

	//Function

	void input();
	void input1();
	void update();
	void drawTheGame();
	void run();		//the main loop will be in the run function
	
	void newSnake();
	void addSnakeSection();
	void addDirection(int newDirection);
	void moveFood();
	void createWall();

	static void setUpText(Text *textItem, const Font &font, const string &value, int size, Color color);

	void togglePause();
	void startGame();
};

