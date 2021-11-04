#include "app.hpp"
#include "components.hpp"
#include "systems.hpp"
#include "utils.hpp"
#include "player/component.hpp"

#include <typeinfo>


void PlayerRenderSystem::update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt) {
    es.each<Player, Body>([this](ex::Entity entity, Player &player, Body &body){

        auto angle = angle_vec(sf::Vector2i(0,-1), sf::Vector2i(body.direction));
        auto pos = Application::gamestate->curr_mouse_pos - sf::Vector2i(body.position);
        auto arm_angle = angle_vec(sf::Vector2i(0,-1), pos);

        if (Application::gamestate->curr_mouse_pos.x < body.position.x) arm_angle = 360 - arm_angle;
        if (body.direction.x < 0) angle = 360 - angle;

        auto body_sprite = player.sprites["hat"];
        body_sprite.setOrigin(50,70);
        body_sprite.setRotation(angle);
        body_sprite.setPosition(body.position);

        auto left_arm_sprite = player.sprites["left_arm"];
        left_arm_sprite.setOrigin(50,150);
        left_arm_sprite.setRotation(arm_angle);
        left_arm_sprite.setPosition({body.position.x - body.direction.y*50, body.position.y-50*body.direction.x});

        auto right_arm_sprite = player.sprites["right_arm"];
        right_arm_sprite.setOrigin(50,150);
        right_arm_sprite.setRotation(arm_angle);
        right_arm_sprite.setPosition({body.position.x + body.direction.y*50, body.position.y+50*body.direction.x});

        target.draw(left_arm_sprite);
        target.draw(right_arm_sprite);
        target.draw(body_sprite);

    });
}

void ProjectileSystem::update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt)
{
    while(!projectile_queue.empty())
    {
        auto projectile = projectile_queue.back();
        auto entity = es.create();
        entity.assign<Body>(Body(projectile.position, projectile.position));
        auto dir = sf::Vector2i(projectile.position) - Application::gamestate->curr_mouse_pos;
        auto acc = - sf::Vector2f(dir) / norm(dir);
        entity.assign<Projectile>(projectile.position, acc);
        entity.assign<CollisionShape>(20);
        std::cout << "emit Projectile" << std::endl;
        projectile_queue.pop_back();
    }
    es.each<Body,Projectile>(
        [this, &es, &dt] (ex::Entity entity, Body &body, Projectile &projectile)
        {
            if (projectile.ttl < 1)
            {
                es.destroy(entity.id());
                return;
            }
            projectile.ttl -= 1;

            body.position += (100000.0f * projectile.velocity * (float) dt * (float) dt);
            sf::CircleShape shape(20);
            shape.setFillColor(sf::Color(100, 250, 50));
            shape.setPosition(body.position);
            target.draw(shape);
        }
    );
}

void ProjectileSystem::configure(entityx::EventManager &events)
{
    std::cout << "subscribe to projectile event!" << std::endl;
    events.subscribe<Projectile>(*this);
}

void ProjectileSystem::receive(const Projectile &projectile)
{
    projectile_queue.push_front(Projectile(projectile)); 
}

void ControllableSystem::configure(entityx::EventManager &event_manager)
{
    //event_manager.subscribe<Action>(*this);
}

///void ControllableSystem::receive(const Action action)
//{
    //event_manager_.emit<Projectile>({0,0}, {0,0});
//}

void ControllableSystem::update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt)
{
    std::map<sf::Keyboard::Key, bool> &keyboard = Application::gamestate->keyboard;
    es.each<Body,Controllable>(
        [&events, &keyboard, &dt](
            ex::Entity entity,
            Body &body,
            const Controllable &controllable
        ){
        sf::Vector2f acc(0,0);
        for (auto const& v: controllable.key_mapping)
        {
            auto key = v.first;
            auto action = v.second;

            if (!keyboard[key]) continue;

            switch(action)
            {
                case Action::move_up:
                    acc += sf::Vector2f(0,-1);
                    break;
                case Action::move_down:
                    acc += sf::Vector2f(0,1);
                    break;
                case Action::move_right:
                    acc += sf::Vector2f(1,0);
                    break;
                case Action::move_left:
                    acc += sf::Vector2f(-1,0);
                    break;
                case Action::shoot:
                    keyboard[sf::Keyboard::Space] = false;
                    events.emit<Projectile>(body.position, body.direction);
                    break;
                default:
                    std::cout << "Unknown Action" << std::endl;
                    break;
            }
            body.position += (10000.0f * acc * (float) dt * (float) dt);
            body.direction = acc;
        }

    });
}

void CollisionSystem::update(ex::EntityManager &es , ex::EventManager &events, ex::TimeDelta dt)
{
    ex::ComponentHandle<CollisionShape> coll1, coll2;
    ex::ComponentHandle<Projectile> pro1;
    ex::ComponentHandle<Body> body1, body2;
    for (ex::Entity entity1 : es.entities_with_components(coll1, body1, pro1)) {
        for (ex::Entity entity2 : es.entities_with_components(coll2, body2)) {
            //std::cout << coll1->radius;
            if (entity1.id() == entity2.id()) continue;
            auto body_distance = norm(sf::Vector2i(body1->position) - sf::Vector2i(body2->position));
            if (body_distance <= (coll1->radius + coll2->radius)) {
                std::cout << "collision" << std::endl;
                pro1->velocity.x = 0.5;
                pro1->velocity.y = 0.5;
            }
        }
    }
}

void ColumnRenderSystem::update(ex::EntityManager &es, ex::EventManager &events, ex::TimeDelta dt)
{
    es.each<Body,CollisionShape,StaticObject>(
        [this](ex::Entity entity, Body &body, CollisionShape &coll, StaticObject &so) {
            sf::CircleShape shape(coll.radius);
            shape.setFillColor(sf::Color(0, 0, 0));
            shape.setPosition(body.position);
            target.draw(shape);
        }
    );
};