#include "game.h"

void Game::input() {
	//Poll event
	while (this->window->pollEvent(this->ev)) {
		//window closed
		if (ev.type == Event::Closed) {
			window->close();
		}


		//Handle Keyboard input
		if (ev.type == Event::KeyPressed) {
			//Quit
			if (ev.key.code == Keyboard::Escape) {
				this->window->close();
			}

			//Pause
			if (ev.key.code == Keyboard::P) {
				togglePause();
			}

			//new game

			if (currentGameState == gameState::GAMEOVER) {
				if (ev.key.code == Keyboard::N) {
					startGame();
				}
			}

			//Direction
			if (ev.key.code == Keyboard::W) {
				addDirection(direction::UP);
			}
			else if (ev.key.code == Keyboard::S) {
				addDirection(direction::DOWN);
			}
			else if (ev.key.code == Keyboard::A) {
				addDirection(direction::LEFT);
			}
			else if (ev.key.code == Keyboard::D) {
				addDirection(direction::RIGHT);
			}
		}
	}
}