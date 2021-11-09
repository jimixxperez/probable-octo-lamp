#include <iostream>
#include <map>
#include <math.h>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "app.hpp"
#include "systems.hpp"
#include "components.hpp"
#include "player/component.hpp"
#include "utils.hpp"

namespace ex = entityx;


std::unique_ptr<GameState> Application::gamestate;

void init_player (sf::RenderTarget &target, ex::EntityManager &es)
{
    auto player = es.create();
    player.assign<Controllable>();
    player.assign<Body>(sf::Vector2f(20,20), sf::Vector2f(10,10));
    player.assign<Particle>(sf::Color::Green, 40.0f, 2);
    player.assign<Player>();
    player.assign<CollisionShape>(100);
}

void init_columns(sf::RenderTarget &target, ex::EntityManager &es)
{
  auto target_center = sf::Vector2f(target.getSize()) / 2.0f;
  auto angles = {60,120,180,240,300,360};
  float radius = (target_center.y - 350) / degree_to_rad(30);
  //float radius = 500.0f;
  ex::Entity col;
  for (auto const &angle : angles) {
    col = es.create();
    auto rad = degree_to_rad(angle);
    auto x = target_center.x + radius * std::cos(rad);
    auto y = target_center.y + radius * std::sin(rad);
    col.assign<Body>(sf::Vector2f(x,y), sf::Vector2f(10,10));
    col.assign<StaticObject>();
    col.assign<CollisionShape>(50);
  }
}

void init_components (sf::RenderTarget &target, ex::EntityManager &es) 
{
  init_player(target, es);
  init_columns(target, es);
}

Application::Application() : window()
{
  Application::gamestate = std::unique_ptr<GameState>(std::move(new GameState()));
  window.create(sf::VideoMode(800, 800), "Guaca");
  init_systems();
  init_components(window, entities);

}

Application::Application(uint16_t width, uint16_t height) : window()
{
  Application::gamestate = std::unique_ptr<GameState>(std::move(new GameState()));
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  window.create(sf::VideoMode(width, height), "Guaca", sf::Style::Default, settings);
  init_systems();
  init_components(window, entities);

}

void Application::init_systems() 
{
  systems.add<PlayerRenderSystem>(window);
  systems.add<ProjectileSystem>(window);
  systems.add<ColumnRenderSystem>(window);
  systems.add<ControllableSystem>();
  systems.add<CollisionSystem>();
  systems.configure();
}

void Application::handleEvent()
{
    sf::Event event;
    while(window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          std::cout << "window closed" << std::endl;
          window.close();
        case sf::Event::KeyPressed:
          Application::gamestate->keyboard[event.key.code] = true;
          break;
        case sf::Event::KeyReleased:
          Application::gamestate->keyboard[event.key.code] = false;
          break;
        case sf::Event::MouseButtonPressed:
          std::cout << "Mouse button pressed" << std::endl;
          Application::gamestate->keyboard[sf::Keyboard::Space] = true;
          events.emit<Action>(Action::shoot);
        
        //case sf::Event::MouseButtonReleased:
        //  Application::gamestate->keyboard[sf::Keyboard::Space] = false;

        default:
          break;
      }
    }
    Application::gamestate->curr_mouse_pos = sf::Mouse::getPosition(window);
}

void Application::run()
{
  sf::Clock clock;
  const float rate = 60.0f;
  std::cout << "run" << std::endl;
  std::cout << "window open " << window.isOpen() <<std::endl;
  while(window.isOpen())
  {
    handleEvent();
    window.clear(sf::Color(255,255,255,255));
    sf::Time elapsed = clock.restart();
    sf::Int64 delay = (sf::Int64)(1000 / rate) - elapsed.asMilliseconds();
    if (delay > 0) sf::sleep(sf::milliseconds(delay));
    update(elapsed.asSeconds());
    window.display();
  }
}

void Application::update(ex::TimeDelta dt)
{
  systems.update_all(dt); 
}
