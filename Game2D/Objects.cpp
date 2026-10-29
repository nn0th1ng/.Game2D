#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Game.h"

using namespace sf;

std::vector<RectangleShape> boxes;
std::vector<CircleShape> coins;
std::vector<RectangleShape> enemies;
std::vector<CircleShape> enemy_views;
std::vector<RectangleShape> grounds;

//
//enemy_view.setPosition(enemy.getPosition().x - enemy_view.getRadius() +
//enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().top - enemy.getGlobalBounds().height);
//

void checkX(RectangleShape& player) {
    for (const auto& box : boxes) {
        if (player.getGlobalBounds().intersects(box.getGlobalBounds())) {
            onFloor = true;
            if (directionX == 1) {
                velocityX = 0;
                player.setPosition(box.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
            }
            else if (directionX == 0) {
                velocityX = 0;
                player.setPosition(box.getGlobalBounds().left + box.getGlobalBounds().width, player.getPosition().y);
            }
        }
    }
}

void checkY(RectangleShape& player) {
    for (const auto& box : boxes) {
        if (player.getGlobalBounds().intersects(box.getGlobalBounds())) {
            onFloor = true;
            if (directionY == 0) {
                velocityY = 0;
                player.setPosition(player.getPosition().x, box.getGlobalBounds().top - player.getGlobalBounds().height);
            }
            else if (directionY == 1) {
                velocityY = 0;
                player.setPosition(player.getPosition().x, box.getGlobalBounds().top + box.getGlobalBounds().height + player.getGlobalBounds().height);
            }
        }
    }
}

void checkGround(RectangleShape& player) {
    for (const auto& g : grounds) {
        if (player.getGlobalBounds().intersects(g.getGlobalBounds())) {
            onGround = true;
            onFloor = false;
            velocityY = 0;
            player.setPosition(player.getPosition().x, g.getGlobalBounds().top - player.getGlobalBounds().height);
        }
    }
}

void checkCoins(RectangleShape& player) {
    for (auto& coin : coins) {
        if (player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
            coin.setPosition(-1488, -1488);
            money++;
        }
    }
}