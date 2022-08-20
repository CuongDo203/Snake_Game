#include "Food.h"

Food::Food() {
	Vector2f startingPosition(400, 300);
	prey.setSize(Vector2f(20.f, 20.f));
	prey.setFillColor(Color::Red);
	prey.setPosition(startingPosition);
}

void Food::setPosition(Vector2f(newPosition)) {
	prey.setPosition(newPosition);
}

RectangleShape Food::getPrey() {
	return this->prey;
}