#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

extern bool onGround;
extern bool onFloor;

extern float velocityY;
extern float velocityX;
extern int speed;

extern bool directionX;
extern bool directionY;

void controller(sf::RectangleShape);