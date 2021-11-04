#include "components.hpp"

Controllable::Controllable() 
{
    key_mapping[sf::Keyboard::W] = Action::move_up;
    key_mapping[sf::Keyboard::S] = Action::move_down;
    key_mapping[sf::Keyboard::D] = Action::move_right;
    key_mapping[sf::Keyboard::A] = Action::move_left;
    key_mapping[sf::Keyboard::Space] = Action::shoot;
};

Action Controllable::getAction(sf::Keyboard::Key key)
{
    auto search =  key_mapping.find(key);
    if (search == key_mapping.end())
    {
    return Action::noop;
    }
    return key_mapping[key];
};