#include "Wall.h"

Wall::Wall(Vector2f position, Vector2f size)
{
	wallShape.setSize(size);
	//wall_background.loadFromFile
	wallShape.setFillColor(Color::Blue);
	wallShape.setPosition(position);
}

RectangleShape Wall::getWallShape()
{
	return this->wallShape;
}
