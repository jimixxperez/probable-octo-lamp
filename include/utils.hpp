#ifndef UTILS
#define UTILS

#include <iostream>
#include <math.h>
#include <sfml/Graphics.hpp>

inline float r(int a, float b = 0) {
  return static_cast<float>(std::rand() % (a * 1000) + b * 1000) / 1000.0;
}

inline float norm(sf::Vector2i vec)
{
  return (float)std::sqrt(vec.x*vec.x + vec.y * vec.y);
}

inline float angle_vec(sf::Vector2i vec1, sf::Vector2i vec2)
{
  return 57.0f * std::acos(
    (
      (vec1.x * vec2.x) + (vec1.y * vec2.y)
    ) / 
    (
      norm(vec1) * norm(vec2)
    )
  );
}
#endif