#include <SFML/Graphics.hpp>
#include "Controller.h"

using namespace sf;

void AI(std::vector<CircleShape>& enemy_views, RectangleShape& player, std::vector<RectangleShape>& enemies) {
    for (auto& view : enemy_views) {
        if (player.getGlobalBounds().intersects(view.getGlobalBounds())) {
            if (view.getPosition().x + view.getRadius() < player.getPosition().x) {
                for (auto& e : enemies) {
                    e.move(0.9, 0.f);
                    view.move(0.9, 0.f);
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