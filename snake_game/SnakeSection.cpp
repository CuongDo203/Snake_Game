#include "SnakeSection.h"

SnakeSection::SnakeSection(Vector2f startPosition)
{
	section.setSize(Vector2f(20.f, 20.f));
	section.setFillColor(Color::Green);
	section.setPosition(startPosition);
	position = startPosition;
}

Vector2f SnakeSection::getPos()
{
	return this->position;
}

 void SnakeSection::setPos(Vector2f newPosition)
{
	position = newPosition;
}

 RectangleShape SnakeSection::getShape()
 {
	 return this->section;
 }

 void SnakeSection::updateSnake()
 {
	 section.setPosition(position);
 }
