#ifndef playercomponent
#define playercomponent

#include <iostream>
#include <string>
#include <sfml/Graphics.hpp>

class Player {
    public:
        Player();
        std::map<std::string, sf::Sprite> sprites;
    private:
        sf::Texture tex;
};


struct Projectile {
    Projectile(sf::Vector2f position, sf::Vector2f velocity, uint16_t ttl=50) : 
    position(position), velocity(velocity), ttl(ttl) {};
    sf::Vector2f position;
    sf::Vector2f velocity;
    uint16_t ttl;
};
#endif