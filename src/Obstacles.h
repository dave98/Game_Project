#ifndef OBSTACLES_H
#define OBSTACLES_H


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <map>

#include "model.h"

using namespace std;

//Semi automático

class obstacles{
public:
  glm::vec3 o_position;
  glm::vec3 o_direction;
  glm::vec3 o_rotation;

  float velocity;
  int radio_generation;
  int scale;

  map<string, Model*> asteroid_list;

  obstacles(float, int);
  ~obstacles();

  void update();
  void render();
};

obstacles::obstacles(float _vel, int _ratio){
  this->o_position = glm::vec3(500 + (rand()%500), (rand() % 300) - 150, (rand() % 300) - 150);
  this->o_direction = glm::vec3(-1 *  _vel, 0, 0);
  this->o_rotation = glm::vec3(rand()%360, rand()%360, rand()%360);

  this->velocity = _vel;
  this->radio_generation = _ratio;
  this->scale = rand()%7 + 3;


  this->asteroid_list["asteroid_1"] = new Model(4, "data/asteroids/asteroid OBJ.obj", "data/asteroids/Map__4_Mix.tga", GL_BGR_EXT, GL_RGB);
  //this->asteroid_list["asteroid_1"] = new Model();
  //this->asteroid_list["asteroid_1"] = new Model();
  //this->asteroid_list["asteroid_1"] = new Model();

}

void obstacles::update(){
  if(this->o_position.x > -100){
    this->o_position = this->o_position + this->o_direction;
  }
  else{
    this->o_position = glm::vec3(500, (rand() % 300) - 150, (rand() % 300) - 150);
    this->scale = rand()%7 + 3;
  }
}

void obstacles::render(){
  this->update();
  glPushMatrix();
    glTranslatef(this->o_position.x, this->o_position.y, this->o_position.z);
    glRotatef(this->o_rotation.x, 1.0, 0.0, 0.0);
    glRotatef(this->o_rotation.y, 0.0, 1.0, 0.0);
    glRotatef(this->o_rotation.z, 0.0, 0.0, 1.0);
    glutSolidCube(this->scale);
    //this->asteroid_list["asteroid_1"]->dibujar();
  glPopMatrix();
}

#endif
