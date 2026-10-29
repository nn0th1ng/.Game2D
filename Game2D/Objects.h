#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

extern std::vector<RectangleShape> boxes;
extern std::vector<CircleShape> coins;
extern std::vector<RectangleShape> enemies;
extern std::vector<CircleShape> enemy_views;
extern std::vector<RectangleShape> grounds;

void checkX(RectangleShape&);
void checkY(RectangleShape&);
void checkGround(RectangleShape&);
void checkCoins(RectangleShape&);