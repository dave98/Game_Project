#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>
#include "glm/glm/vec3.hpp"
#include "glm/glm/vec4.hpp"

using namespace std;

struct Particle{

  Particle(): m_Position(0)
            , m_Velocity(0)
            , m_Color(0)
            , m_fRotate(0)
            , m_fAge(0)
            , m_fLifeTime(0) {}

  glm::vec3 m_Position;
  glm::vec3 m_Velocity;
  glm::vec3 m_Color;
  float m_fRotate;
  float m_fSize;
  float m_fAge;
  float m_fLifeTime;


};

  typedef vector<Particle> ParticleBuffer;


#endif
