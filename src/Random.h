#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

using namespace std;
using namespace glm;

inline float P_Random()
{
  return rand() / (float)RAND_MAX;
}

inline float RandRange( float fMin, float fMax )
{
  if ( fMin > fMax ) std::swap( fMin, fMax );
  return ( P_Random() * ( fMax - fMin ) ) + fMin;
}

inline glm::vec3 RandUnitVec()
{
  float x = ( P_Random() * 2.0f ) - 1.0f;
  float y = ( P_Random() * 2.0f ) - 1.0f;
  float z = ( P_Random() * 2.0f ) - 1.0f;

  return normalize( vec3(x,y,z) );
}

#endif
