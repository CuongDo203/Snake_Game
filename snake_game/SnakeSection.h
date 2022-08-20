#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class SnakeSection
{
private:
	Vector2f position;
	RectangleShape section;
public:
	SnakeSection(Vector2f startPosition);

	Vector2f getPos();
	void setPos(Vector2f newPosition);

	RectangleShape getShape();

	void updateSnake();
};

