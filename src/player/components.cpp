#include <vector>
#include "player/component.hpp"

Player::Player(){
    tex = sf::Texture();
    tex.loadFromFile("../assets/player.png");
    std::vector<std::string> parts({"hat", "body", "right_arm", "left_arm"});
    for (const auto &part : parts) {
        auto sprite = sf::Sprite();
        sprite.setTexture(tex);

        sf::Rect<int> texRect; 
        if (part == "hat") texRect = {0,0,100,140};
        else if (part == "right_arm" || part == "left_arm") texRect = {101,0,50,140};
        else texRect = {0,0,200,100};

        sprite.setTextureRect(texRect);
        sprites[part] = sprite;
    }
}