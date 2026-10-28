#include <SFML/Graphics.hpp>
#include <chrono>

using namespace sf;

bool onGround = true;
bool onFloor = false;

std::vector<RectangleShape> boxes;
std::vector<CircleShape> coins;

float velocityY = 0.0;
float velocityX = 0.0;

bool directionX = 0;
bool directionY = 0;

int main()
{
    RenderWindow window(VideoMode(800, 600), L"Game", Style::Default);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    RectangleShape player(sf::Vector2f(15, 25));
    player.setFillColor(sf::Color::Magenta);
    player.setPosition(200, 200);

    RectangleShape ground(sf::Vector2f(800, 500));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0, 225);

    RectangleShape box(sf::Vector2f(15, 15));
    box.setFillColor(sf::Color::White);
    box.setPosition(250, 210);
    boxes.push_back(box);

    RectangleShape box2(sf::Vector2f(15, 50));
    box2.setFillColor(sf::Color::White);
    box2.setPosition(450, 175);
    boxes.push_back(box2);

    CircleShape coin(10, 8);
    coin.setFillColor(sf::Color::Yellow);
    coin.setPosition(300, 180);
    coins.push_back(coin);

    sf::Clock clock; 

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //move
        player.move(velocityX, velocityY);

        //collisions
        for (const auto& box : boxes) {
            if (player.getGlobalBounds().intersects(box.getGlobalBounds())) {
                onFloor = true;
                if (directionY == 0) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x, box.getGlobalBounds().top - player.getGlobalBounds().height);
                }
                else if (directionY == 1) {
                    velocityY = 0;
                    player.setPosition(player.getPosition().x, box.getGlobalBounds().top + player.getGlobalBounds().height);
                }
            }
            else {
                onFloor = false;
            }
        }
        for (const auto& box : boxes) {
            if (player.getGlobalBounds().intersects(box.getGlobalBounds())) {
                onFloor = true;
                if (directionX == 1) {
                    velocityX = 0;
                    player.setPosition(box.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                }
                else if (directionX == 0) {
                    velocityX = 0;
                    player.setPosition(box.getGlobalBounds().left + player.getGlobalBounds().width, player.getPosition().y);
                }
                else {
                    player.setPosition(box.getGlobalBounds().left - player.getGlobalBounds().width, player.getPosition().y);
                }
            }
            else {
                onFloor = false;
            }
        }


        //coins
        if (player.getGlobalBounds().intersects(coin.getGlobalBounds())) {
            coin.setPosition(-200, -200);
        }

        //ground
        if (player.getPosition().y < 200.f) {
            onGround = false;
        }
        if (player.getPosition().y >= 200.f){
            player.setPosition(player.getPosition().x, 200.f);
            onGround = true;
            velocityY = 0.0f;
        }

        //gravity
        if (!onGround) {
            velocityY += 0.5f;
        }

        //move
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocityX = -5;
            directionX = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocityX = 5;
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
            velocityY = -7.0f;
        }

        window.clear(Color::Blue);
        window.draw(player);
        for (const auto& box : boxes) {
            window.draw(box);
        }
        window.draw(ground);
        window.draw(coin);
        window.display();
    }
    return 0;
}