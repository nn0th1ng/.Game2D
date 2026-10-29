#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

bool onGround = true;
bool onFloor = false;

std::vector<RectangleShape> boxes;
std::vector<CircleShape> coins;
std::vector<RectangleShape> enemies;
std::vector<CircleShape> enemy_views;
std::vector<RectangleShape> grounds;
//std::vector<RectangleShape> entities;

float velocityY = 0.0;
float velocityX = 0.0;
int speed = 2.5;

bool directionX = 0;
bool directionY = 0;

int main()
{
    RenderWindow window(VideoMode(800, 600), L"Game", Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    RectangleShape player(sf::Vector2f(15, 25));
    player.setFillColor(sf::Color::Magenta);
    player.setPosition(270, 200);

    RectangleShape ground(sf::Vector2f(800, 500));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0, 225);
    grounds.push_back(ground);

    RectangleShape box(sf::Vector2f(15, 15));
    box.setFillColor(sf::Color::White);
    box.setPosition(250, 210);
    boxes.push_back(box);

    RectangleShape box2(sf::Vector2f(100, 50));
    box2.setFillColor(sf::Color::White);
    box2.setPosition(450, 140);
    boxes.push_back(box2);

    CircleShape coin(10, 8);
    coin.setFillColor(sf::Color::Yellow);
    coin.setPosition(300, 180);
    coins.push_back(coin);

    CircleShape coin1(10, 8);
    coin1.setFillColor(sf::Color::Yellow);
    coin1.setPosition(100, 180);
    coins.push_back(coin1);

    RectangleShape enemy(sf::Vector2f(25, 30));
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(465, 100);
    enemies.push_back(enemy);
    CircleShape enemy_view(50, 10);
    enemy_view.setFillColor(sf::Color::White);
    enemy_view.setPosition(enemy.getPosition().x - enemy_view.getRadius() + enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().top - enemy.getGlobalBounds().height);
    enemy_views.push_back(enemy_view);

    sf::Clock clock; 

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //enemy
        for (auto& view : enemy_views) {
            for (const auto& box : boxes) {
                if (player.getGlobalBounds().intersects(view.getGlobalBounds())) {
                    if (view.getPosition().x + view.getRadius() < player.getPosition().x) {
                       for (auto& e : enemies) {
                           e.move(0.9, 0.f);
                           view.move(0.7, 0.f);
                       }
                    }
                    else {
                        for (auto& e : enemies) {
                            e.move(-0.9, 0.f);
                            view.move(-0.9, 0.f);
                        }
                    }

                    if (view.getPosition().y + view.getRadius() < player.getPosition().y) {
                        for (auto& e : enemies) {
                            e.move(0.f, 0.9);
                            view.move(0.f, 0.9);
                        }
                    }
                    else {
                        for (auto& e : enemies) {
                            e.move(0.f, -0.9);
                            view.move(0.f, -0.9);
                        }
                    }
                }
            }
        }

        //check position
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::cout << sf::Mouse::getPosition(window).x << "   " << sf::Mouse::getPosition(window).y << std::endl;
        }

        //move and collisions
        player.move(0.f, velocityY);

        for (const auto& box : boxes) {
            if (player.getGlobalBounds().intersects(box.getGlobalBounds())) {
                onFloor = true;
                if (directionY == 0) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x, box.getGlobalBounds().top - player.getGlobalBounds().height);
                }
                else if (directionY == 1) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x,box.getGlobalBounds().top+box.getGlobalBounds().height+player.getGlobalBounds().height);
                }
            }
        }

        player.move(velocityX, 0.f);

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

        //coins
        for (auto& coin : coins) {
            if (player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
                coin.setPosition(-200, -200);
            }
        }

        //ground
        if (player.getPosition().y < 200.f) {
            onGround = false;
        }
        if (player.getPosition().y >= 200.f){
            player.setPosition(player.getPosition().x, 200.f);
            onGround = true;
            onFloor = false;
            velocityY = 0.0f;
        }

        //gravity
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
        else{
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

        window.clear(Color::Blue);
        window.draw(player);
        for (const auto& box : boxes) {
            window.draw(box);
        }
        for (const auto& coin : coins) {
            window.draw(coin);
        }
        for (const auto& e : enemies) {
            window.draw(e);
        }
        for (const auto& g : grounds) {
            window.draw(g);
        }
        window.display();
    }
    return 0;
}