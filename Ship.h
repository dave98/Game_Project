#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "glm/glm/glm.hpp "
#include "glm/glm/vec3.hpp"
#include "glm/glm/gtx/rotate_vector.hpp"

#include "extra_functions.h"
#include "Cannon.h"


float MOVEMENT_FACTOR = 0.05;
float MOVEMENT_LIMIT = 10.0;
float MAX_ACCELERATION = 5.0;
float ACCELERATION_PROGRESS = 0.02;

using namespace std;

class my_ship{
public:
  glm::vec3 s_position;
  glm::vec3 s_direction;
  glm::vec3 s_rotation;  //Rota solo en XY y en XZ, YZ no se usa
  glm::vec3 s_acceleration;

  glm::vec3 s_position_original;
  bool is_alive;
  float s_life;
  float s_velocity;
  int s_gun_number;
  vector<cannon* > cannon_list;

  my_ship();
  ~my_ship();

  void render_ship();
  void set_ship_position(glm::vec3);
  void set_ship_direction(glm::vec3);

  void ship_movement_up();
  void ship_movement_down();
  void ship_movemente_right();
  void ship_movement_left();
  void ship_movement_stop();

  void ship_shoot();
};


my_ship::my_ship(){
    this->s_position = glm::vec3(0); //Dinamico, cambia conforme recibe entradas del usario
    this->s_direction = glm::vec3(0);
    this->s_rotation = glm::vec3(0);
    this->s_acceleration = glm::vec3(0);

    this->s_position_original = glm::vec3(0); //Etern
    this->is_alive = true;
    this->s_life = 100;
    this->s_velocity = 10;
    this->s_gun_number = 1;
}

my_ship::~my_ship(){
}


void my_ship::render_ship(){
  //Actualizamos las direcciones de los cañones en cada rendering
  for(unsigned int i = 0; i < this->cannon_list.size(); i++){
    cannon_list[i]->update_cannon_direction(this->s_direction);
    cannon_list[i]->render(); //Renderizamos los cañones;
  }

  glPushMatrix(); //Creamos nuevo ambiente de dibujo
    glBegin(GL_LINES);
      glVertex3f(this->s_position.x, this->s_position.y, this->s_position.z);
      glVertex3f(this->s_position.x + this->s_direction.x, this->s_position.y + this->s_direction.y, this->s_position.z + this->s_direction.z);
    glEnd();

    glTranslatef( this->s_position.x, this->s_position.y, this->s_position.z);
    glRotatef(-this->s_rotation.z, 0.0, 0.0, 1.0);
    glRotatef(this->s_rotation.y, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 1.0, 0.0); //Ponemos la nave en posicion
    glutSolidCone(1.0, 8.0, 20, 20);
  glPopMatrix();
}

void my_ship::set_ship_position(glm::vec3 _new_pos){
  this->s_position = _new_pos;
  this->s_position_original = this->s_position;
}

//Este parametro depende fuertemente del anterior, ordenar
void my_ship::set_ship_direction(glm::vec3 _direction_point){
  this->s_direction = _direction_point - this->s_position;
  this->s_direction = glm::normalize(this->s_direction);

  this->s_direction.x = 10 * this->s_direction.x; //20 means the size of the vector
  this->s_direction.y = 10 * this->s_direction.y; //20 means the size of the vector
  this->s_direction.z = 10 * this->s_direction.z; //20 means the size of the vector

  //////////////BEWARE///////////////
  //CREAMOS LOS CAÑONES
  cannon* c_1 = new cannon(20, glm::vec3(this->s_position.x, this->s_position.y - 2, this->s_position.z - 2), glm::vec3(this->s_direction.x, this->s_direction.y, this->s_direction.z)); this->cannon_list.push_back(c_1);
  cannon* c_2 = new cannon(20, glm::vec3(this->s_position.x, this->s_position.y - 2, this->s_position.z + 2), glm::vec3(this->s_direction.x, this->s_direction.y, this->s_direction.z)); this->cannon_list.push_back(c_2);
  cannon* c_3 = new cannon(20, glm::vec3(this->s_position.x, this->s_position.y + 2, this->s_position.z - 2), glm::vec3(this->s_direction.x, this->s_direction.y, this->s_direction.z)); this->cannon_list.push_back(c_3);
  cannon* c_4 = new cannon(20, glm::vec3(this->s_position.x, this->s_position.y + 2, this->s_position.z + 2), glm::vec3(this->s_direction.x, this->s_direction.y, this->s_direction.z)); this->cannon_list.push_back(c_4);
}

void my_ship::ship_movement_up(){
  if( (this->s_position.z - this->s_position_original.z) < MOVEMENT_LIMIT){
      this->s_position.z += MOVEMENT_FACTOR;
      for(unsigned int i = 0; i < this->cannon_list.size(); i++){
        this->cannon_list[i]->cannon_position.z += MOVEMENT_FACTOR;
      }
    }
    return;
}

void my_ship::ship_movement_down(){
  if( (this->s_position.z - this->s_position_original.z) > -MOVEMENT_LIMIT){
    this->s_position.z -= MOVEMENT_FACTOR;
    for(unsigned int i = 0; i < this->cannon_list.size(); i++){
      this->cannon_list[i]->cannon_position.z -= MOVEMENT_FACTOR;
    }
  }
  return;
}

void my_ship::ship_movement_left(){
  if( (this->s_position.y - this->s_position_original.y) < MOVEMENT_LIMIT){
    this->s_position.y += MOVEMENT_FACTOR;
    for(unsigned int i = 0; i < this->cannon_list.size(); i++){
      this->cannon_list[i]->cannon_position.y += MOVEMENT_FACTOR;
    }
  }
  return;
}

void my_ship::ship_movemente_right(){
  if( (this->s_position.y - this->s_position_original.y) > -MOVEMENT_LIMIT){
    this->s_position.y -= MOVEMENT_FACTOR;
    for(unsigned int i = 0; i < this->cannon_list.size(); i++){
      this->cannon_list[i]->cannon_position.y -= MOVEMENT_FACTOR;
    }
  }
  return;
}


void my_ship::ship_movement_stop(){
  if(this->s_acceleration.x > 0.0){
    this->s_acceleration.x -= ACCELERATION_PROGRESS;
  }
  else if(this->s_acceleration.x < 0.0){
    this->s_acceleration.x += ACCELERATION_PROGRESS;
  }

  if(this->s_acceleration.y > 0.0){
    this->s_acceleration.y -= ACCELERATION_PROGRESS;
  }
  else if(this->s_acceleration.y < 0.0){
    this->s_acceleration.y += ACCELERATION_PROGRESS;
  }

}

void my_ship::ship_shoot(){
  for(unsigned int i = 0; i < this->cannon_list.size(); i++){
    this->cannon_list[i]->cannon_shoot();
  }
  return;
}




#endif
