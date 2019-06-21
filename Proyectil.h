#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <iostream>
#include <GL/glut.h>
#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp "
#include "glm/glm/gtx/rotate_vector.hpp"

using namespace std;

class proyectil{
public:
  glm::vec3 p_position;
  glm::vec3 p_direction;
  float p_velocity;
  float p_damage;
  bool is_alive;

  proyectil(glm::vec3, glm::vec3, float, float);
  ~proyectil();

  void p_update();
  void p_render();
};

proyectil::proyectil(glm::vec3 _pos, glm::vec3 _dir, float _vel, float _dam){
  this->is_alive = true;
  this->p_position = _pos;
  this->p_velocity = _vel;
  this->p_damage = _dam;
  this->p_direction = _dir;

  this->p_direction = glm::normalize(this->p_direction);
  this->p_direction.x = this->p_direction.x * this->p_velocity;
  this->p_direction.y = this->p_direction.y * this->p_velocity;
  this->p_direction.z = this->p_direction.z * this->p_velocity;
}


proyectil::~proyectil(){}

void proyectil::p_update(){
  this->p_position = this->p_position + this->p_direction;
  if(this->p_position.x >= 500){
    this->is_alive = false;
  }
}

void proyectil::p_render(){
  this->p_update();
  if(this->is_alive){
    glPushMatrix();
      glTranslatef(this->p_position.x, this->p_position.y, this->p_position.z);
      glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
  }
}

#endif
