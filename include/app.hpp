#ifndef APP
#define APP

#include <iostream>
#include <map>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "systems.hpp"


namespace ex = entityx;

class GameState
{
  public:
    std::map<sf::Keyboard::Key, bool> keyboard;
    sf::Vector2i curr_mouse_pos;
};

// encode is running
class Application : public ex::EntityX {
  public:
    static std::unique_ptr<GameState> gamestate;
    explicit Application();
    explicit Application(uint16_t width, uint16_t height);
    void handleEvent();
    void update(ex::TimeDelta dt);
    void run();
  private:
    void init_systems();
    sf::RenderWindow window;
};

//static std::unique_ptr<GameState> gamestate;

#endif