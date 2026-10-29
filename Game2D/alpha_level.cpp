#include <SFML/Graphics.hpp>
#include <iostream>
#include "Controller.h"
#include "enemy.h"
#include "Objects.h"
#include "Game.h"

using namespace sf;

bool level1()
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
    enemy_view.setPosition(enemy.getPosition().x - enemy_view.getRadius() +
        enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().top - enemy.getGlobalBounds().height);
    enemy_views.push_back(enemy_view);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (money >= 2) {
            money = 0;
            return true;
        }

        controller(player);
        checkCoins(player);
        AI(enemy_views, player, enemies);

        player.move(0.f, velocityY);
        checkY(player);
        player.move(velocityX, 0.f);
        checkX(player);

        checkGround(player);

        //check position
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            std::cout << sf::Mouse::getPosition(window).x << "   " << sf::Mouse::getPosition(window).y << std::endl;
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