#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <iostream>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "model.h"
using namespace std;

class proyectil{
public:
  glm::vec3 p_position;
  glm::vec3 p_direction;
  glm::vec3  p_rotation;
  float p_velocity;
  float p_damage;

  Model* p_model;

  proyectil(glm::vec3, glm::vec3, float, float);
  ~proyectil();

  void reset_proyectil(glm::vec3, glm::vec3, float, float);
  void p_update();
  void p_render();
};

proyectil::proyectil(glm::vec3 _pos, glm::vec3 _dir, float _vel, float _dam){
  this->p_position = _pos;
  this->p_velocity = _vel;
  this->p_damage = _dam;
  this->p_direction = _dir;

  this->p_direction = glm::normalize(this->p_direction);
  this->p_rotation =  p_direction;
  this->p_direction.x = this->p_direction.x * this->p_velocity;
  this->p_direction.y = this->p_direction.y * this->p_velocity;
  this->p_direction.z = this->p_direction.z * this->p_velocity;

  this->p_model = new Model(4, "data/MLRS_Rocket.obj", "data/MLRS_Rocket_MLRS_Rocket_Mat_BaseColor.png", GL_BGR_EXT, GL_RGB);
}

proyectil::~proyectil(){}

void proyectil::reset_proyectil(glm::vec3 _pos, glm::vec3 _dir, float _vel, float _dam){
  this->p_position = _pos;
  this->p_velocity = _vel;
  this->p_damage = _dam;
  this->p_direction = _dir;

  this->p_direction = glm::normalize(this->p_direction);
  this->p_direction.x = this->p_direction.x * this->p_velocity;
  this->p_direction.y = this->p_direction.y * this->p_velocity;
  this->p_direction.z = this->p_direction.z * this->p_velocity;
}

void proyectil::p_update(){
  this->p_position = this->p_position + this->p_direction;
}

void proyectil::p_render(){
  this->p_update();

  glPushMatrix();
    glTranslatef(this->p_position.x, this->p_position.y, this->p_position.z);
    //glutSolidSphere(0.5, 10, 10);
    glRotatef(this->p_direction.y, 0.0, 0.0, 1.0);
    glRotatef(this->p_direction.z, 0.0, 1.0, 1.0);
    this->p_model->dibujar();
  glPopMatrix();
}

#endif
