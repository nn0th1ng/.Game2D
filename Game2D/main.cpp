#include <SFML/Graphics.hpp>
#include <chrono>

using namespace sf;

bool onGround = true;

float velocityY = 0.0;

auto now = std::chrono::system_clock::now();
time_t Time1 = std::chrono::system_clock::to_time_t(now);

int main()
{
    RenderWindow window(VideoMode(800, 600), L"Game", Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    RectangleShape player(sf::Vector2f(15, 25));
    player.setFillColor(sf::Color::Magenta);
    player.setPosition(200, 200);

    CircleShape coin(10, 8);
    coin.setFillColor(sf::Color::Yellow);
    coin.setPosition(300, 180);

    sf::Clock clock; 

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        player.move(0.f, velocityY);

        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds() * 60.0f;

        if (player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
            coin.setPosition(-200, -200);
        }

        //ground
        if (player.getPosition().y < 200.f) {
            onGround = false;
        }
        else if (player.getPosition().y >= 200.f){
            player.setPosition(player.getPosition().x, 200.f);
            onGround = true;
            velocityY = 0.0f;
        }

        //gravity
        if (!onGround) {
            velocityY += 0.5f;
            //player.setPosition(player.getPosition().x, player.getPosition().y + 1);
        }

        //move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.setPosition(player.getPosition().x - 5, player.getPosition().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.setPosition(player.getPosition().x + 5, player.getPosition().y);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
            onGround = false;
            velocityY = -7.0f;
            
            /*
            auto now2 = std::chrono::system_clock::now();
            time_t Time2 = std::chrono::system_clock::to_time_t(now2);
            if (Time2 - Time1 >= 1) {
                if (!jumped) {
                    player.setPosition(player.getPosition().x, player.getPosition().y - 50);
                    jumped = true;
                    Time1 = Time2;
                }
            }
            */
        }

        window.clear(Color::Blue);
        window.draw(player);
        window.draw(coin);
        window.display();
    }
    return 0;
}