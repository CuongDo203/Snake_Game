#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

class Food
{
	private:
		RectangleShape prey;

	public:
		Food();
		void setPosition(Vector2f(newPosition));
		RectangleShape getPrey();
};

