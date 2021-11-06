#ifndef SYSTEMS
#define SYSTEMS

#include <iostream>
#include <deque>
#include <map>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "components.hpp"
#include "player/component.hpp"

namespace ex = entityx;

class ColumnRenderSystem: public ex::System<ColumnRenderSystem>
{
  public:
    explicit ColumnRenderSystem(sf::RenderTarget &target) : target(target){};
    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override;
  private:
    sf::RenderTarget &target;
};

class ControllableSystem: public ex::System<ControllableSystem>
{
  public:
    explicit ControllableSystem(){};
    void configure(entityx::EventManager &es) override;
    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override;
    //void handleAction(std::map<sf::Keyboard::Key, bool> &keyboard);
   // void receive(const Action action);
};

class PlayerRenderSystem : public ex::System<PlayerRenderSystem> {
    public:
        explicit PlayerRenderSystem(sf::RenderTarget &target) : target(target) {};
        void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override;
    private:
        sf::RenderTarget &target;
};

class ProjectileSystem : public ex::System<ProjectileSystem>, public ex::Receiver<ProjectileSystem>
{
    public:
      explicit ProjectileSystem(sf::RenderTarget &target) : target(target) {};
      void configure(entityx::EventManager &events) override;
      void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override;
      void receive(const Projectile &projectile);
    private:
      std::deque<Projectile> projectile_queue;
      sf::RenderTarget &target;
      
        
};

class CollisionSystem : public ex::System<CollisionSystem>
{
  public:
    explicit CollisionSystem(){};
    void update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) override;
  private:
    std::map<uint64_t, std::vector<uint64_t> > current_collisions;
};

#endif