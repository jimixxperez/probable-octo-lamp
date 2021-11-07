#include <iostream>
#include <map>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

#include "app.hpp"

namespace ex = entityx;


int main(int argc, const char* argv[]) 
{
    Application app(2000,1500);
    app.run();
    return 0;
}