#include <SFML/Graphics.hpp>

using namespace sf;

bool onGround = true;
bool onFloor = false;

float velocityY = 0.0;
float velocityX = 0.0;
int speed = 2.5;

bool directionX = 0;
bool directionY = 0;

void controller(sf::RectangleShape player) {
    if (!onGround) {
        velocityY += 0.5f;
    }

    //move
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocityX = -speed;
        directionX = 0;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocityX = speed;
        directionX = 1;
    }
    else {
        velocityX = 0;
    }

    //check directionY
    if (velocityY > 0) {
        directionY = 0;
    }
    else if (velocityY < 0) {
        directionY = 1;
    }

    //jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onFloor) {
        onGround = false;
        onFloor = false;
        velocityY = -7.0f;
    }
}