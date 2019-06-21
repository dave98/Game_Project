#ifndef CANNON_H
#define CANNON_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "glm/glm/vec3.hpp"
#include "glm/glm/glm.hpp "
#include "Proyectil.h"

using namespace std;

int MAX_DISTANCE_FROM_CANNON = 100;

class cannon{
public:
  bool is_active;
  float damage;
  glm::vec3 cannon_position;
  glm::vec3 cannon_direction;

  vector<proyectil* > shoot_list;

  cannon();
  cannon(float, glm::vec3, glm::vec3);
  ~cannon();

  void update_cannon_direction(glm::vec3);
  void render();
  void cannon_shoot();
};

cannon::cannon(){
  this->is_active = false; //Sin mas datos el cañon queda deshabilitado
  this->damage = 0.0;
  this->cannon_position = glm::vec3(0); //Por defecto en el eje circle_control_1_traslation
  this->cannon_direction = glm::vec3(0);
}

cannon::~cannon(){
}

cannon::cannon(float _damage, glm::vec3 _pos, glm::vec3 _dir){
  this->is_active = true; //Con datos completos lo activamos
  this->damage = _damage;
  this->cannon_position = _pos;
  this->cannon_direction = _dir;
}

void cannon::update_cannon_direction(glm::vec3 _dir){
  this->cannon_direction = _dir;
}

void cannon::cannon_shoot(){
  proyectil* temp = new proyectil(this->cannon_position, this->cannon_direction, 0.9, this->damage);
  this->shoot_list.push_back(temp);
}

void cannon::render(){
  for(unsigned int i = 0; i < this->shoot_list.size(); i++){
    if( distance(this->cannon_position, this->shoot_list[i]->p_position) > MAX_DISTANCE_FROM_CANNON){ //glm core function, distancia entre la posicion del canno y el proyectil
      this->shoot_list.erase(this->shoot_list.begin() + i);

    }
    else{
      this->shoot_list[i]->p_render();
    }
  }

  glPushMatrix();
    glTranslatef(this->cannon_position.x, this->cannon_position.y, this->cannon_position.z);
    glRotatef(this->cannon_direction.y, 0.0, 0.0, 1.0);
    glRotatef(-this->cannon_direction.z, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glutSolidCone(0.3, 4.0, 20, 20);
  glPopMatrix();
}

#endif
