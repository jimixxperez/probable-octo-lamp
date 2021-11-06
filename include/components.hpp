#ifndef COMPONENTS
#define COMPONENTS

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

namespace ex = entityx;

enum Action {
  move_left,
  move_right,
  move_up,
  move_down,
  shoot,
  noop
};

class Controllable 
{
  public:
    explicit Controllable();
    Action getAction(sf::Keyboard::Key key);
    std::map<sf::Keyboard::Key, Action> key_mapping;
};

struct Body {
  Body(const sf::Vector2f &position, const sf::Vector2f &direction, float rotationd = 0.0)
    : position(position), direction(direction), rotationd(rotationd), alpha(0.0) {}
  sf::Vector2f position;
  sf::Vector2f direction;
  float rotation = 0.0;
  float rotationd;
  float alpha;
};

struct Particle {
  explicit Particle(sf::Color colour, float radius, float duration)
      : colour(colour), radius(radius), alpha(colour.a), d(colour.a / duration) {}

  sf::Color colour;
  float radius, alpha, d;
};

struct CollisionShape {
  CollisionShape(float radius) : radius(radius) {};
  float radius;
  std::set<ex::Entity::Id> in_collision_with;
};

struct StaticObject {
    bool is_static = true;
};

using Renderable = std::shared_ptr<sf::Shape>;
using Sprite = std::shared_ptr<sf::Sprite>;

#endif