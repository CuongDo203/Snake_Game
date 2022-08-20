#include "game.h"

void Game::update() {
	//update snake position
	if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
		Vector2f thisSectionPosition = snake[0].getPos();
		Vector2f lastSectionPosition = thisSectionPosition;

		//Is there anything in queue
		if (!directionQueue.empty()) {
			// don't reverse direction
			switch (snakeDirection) {
				case direction::UP:
					if (directionQueue.front() != direction::DOWN) {
						snakeDirection = directionQueue.front();
					}
					break;
				case direction::DOWN:
					if (directionQueue.front() != direction::UP) {
						snakeDirection = directionQueue.front();
					}
					break;
				case direction::LEFT:
					if (directionQueue.front() != direction::RIGHT) {
						snakeDirection = directionQueue.front();
					}
					break;
				case direction::RIGHT:
					if (directionQueue.front() != direction::LEFT) {
						snakeDirection = directionQueue.front();
					}
					break;
			}
			directionQueue.pop_front();
		}
		
		//Update score


		//grow the snake
		if (sectionsToAdd) {
			addSnakeSection();
			sectionsToAdd--;
		}

		//update head position
		switch (snakeDirection) {
			case direction::RIGHT:
				snake[0].setPos(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
				break;
			case direction::DOWN:
				snake[0].setPos(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
				break;
			case direction::LEFT:
				snake[0].setPos(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
				break;
			case direction::UP:
				snake[0].setPos(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
				break;
		}

		//update tail position
		for (int i = 1; i < snake.size(); i++) {
			thisSectionPosition = snake[i].getPos();
			snake[i].setPos(lastSectionPosition);
			lastSectionPosition = thisSectionPosition;
		}

		//run snake section update function
		for (auto& x : snake) {
			x.updateSnake();
		}

		//kiem tra va cham giua ran va thuc an
		if (snake[0].getShape().getGlobalBounds().intersects(food.getPrey().getGlobalBounds())) {
			//di chuyen thuc an, them phan vao con ran, tang toc do va di chuyen thuc an, tang diem		
			score += 10;
			totalScore = score;
			scoreText.setString(to_string(score));
			FloatRect scoreTextBounds = scoreText.getLocalBounds();
			scoreText.setPosition(Vector2f(this->window->getSize().x - scoreTextBounds.width - 15, -9));

			totalScoreText.setString("Total score: " + to_string(totalScore));
			FloatRect totalScoreTextBounds = totalScoreText.getLocalBounds();
			totalScoreText.setPosition(Vector2f(this->window->getSize().x / 2 - totalScoreTextBounds.width / 2, 200));

			sectionsToAdd += 2;
			speed++;
			moveFood();
		}

		//phat hien va cham voi than ran
		for (int i = 1; i < snake.size(); i++) {
			if (snake[0].getShape().getGlobalBounds().intersects(snake[i].getShape().getGlobalBounds())) {
				//Game over
				currentGameState = gameState::GAMEOVER;
			}
		}

		//phat hien va cham voi tuong
		for (auto& w : wallSections) {
			if (snake[0].getShape().getGlobalBounds().intersects(w.getWallShape().getGlobalBounds())) {
				currentGameState = gameState::GAMEOVER;
			}
		}

		//reset the last time move timer
		timeSinceLastMove = Time::Zero;
	}	//End update position
}