#ifndef UTILS
#define UTILS

#include <iostream>
#include <math.h>
#include <sfml/Graphics.hpp>

inline float r(int a, float b = 0) {
  return static_cast<float>(std::rand() % (a * 1000) + b * 1000) / 1000.0;
}

template<typename T>
float dot(T vec1, T vec2)
{
  return static_cast<float>(vec1.x*vec2.x + vec1.y * vec2.y);
}

template<typename T>
float norm(T vec)
{
  return static_cast<float>(std::sqrt(dot(vec,vec)));
}

template<typename T>
inline float angle_vec(T vec1, T vec2)
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