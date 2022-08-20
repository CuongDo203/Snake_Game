#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall
{
	private:
		RectangleShape wallShape;
		Texture wall_background;
	public:
		Wall(Vector2f position, Vector2f size);
		RectangleShape getWallShape();
};

