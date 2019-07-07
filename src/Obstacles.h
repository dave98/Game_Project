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
float velocidad = 1; //A VALUE BETWEEN 0.5 AND 1.5;
int MAX_MODEL_NUMBER = 2;
int MAX_INTENSITY_ROTATION = 2;
float INITIAL_X_POSITION = 1000;
//Semi automático

class obstacles{
public:
  glm::vec3 o_position;
  glm::vec3 o_direction;
  glm::vec3 o_rotation;
  glm::vec3 o_intensity_rotation;

  float velocity;
  int radio_generation;
  int scale;

  map<string, Model*> asteroid_list;
  int model_number = 1;

  obstacles(float, int);
  ~obstacles();

  void update();
  void render();
  void rebuild();
};

obstacles::obstacles(float _vel, int _ratio){
  this->o_position = glm::vec3(INITIAL_X_POSITION + (rand()%500), (rand() % 300) - 150, (rand() % 300) - 150);
  this->o_direction = glm::vec3(-1 *  _vel, 0, 0);
  this->o_rotation = glm::vec3(rand()%360, rand()%360, rand()%360);

  float agregated_rotation = (rand()%10) / 10;
  MAX_INTENSITY_ROTATION += agregated_rotation;
  this->o_intensity_rotation = glm::vec3(0, rand()%MAX_INTENSITY_ROTATION, rand()%MAX_INTENSITY_ROTATION);

  this->velocity = _vel;
  this->radio_generation = _ratio;
  this->scale = ((rand()%3) + 1) + ( (rand()%10) / 10);


  this->asteroid_list["asteroid_1"] = new Model(3, "data/asteroids/Rock01_OBJ.obj", "data/asteroids/Rock01_BaseColor.png", GL_BGR_EXT, GL_RGB);
  this->asteroid_list["asteroid_2"] = new Model(3, "data/asteroids/Rock.obj", "data/asteroids/Rock_LowPoly_Diffuse.png", GL_BGR_EXT, GL_RGB);
}

void obstacles::update(){
  if(this->o_position.x > -100){
    this->o_position = this->o_position + this->o_direction;
    this->o_rotation += this->o_intensity_rotation;
  }
  else{
    this->rebuild();
  }
}

void obstacles::rebuild(){
    int new_velocity_in_x = (rand()%10) +  5;
    this->o_position = glm::vec3(INITIAL_X_POSITION, (rand() % 300) - 150, (rand() % 300) - 150);
    this->o_direction = glm::vec3(-1 * ( (float)(new_velocity_in_x) / 10.0f), 0, 0);
    this->o_rotation = glm::vec3(rand()%360, rand()%360, rand()%360);

    float agregated_rotation = (rand()%10) / 10;
    MAX_INTENSITY_ROTATION += agregated_rotation;
    this->o_intensity_rotation = glm::vec3(0, rand()%MAX_INTENSITY_ROTATION, rand()%MAX_INTENSITY_ROTATION);

    this->scale = rand()%7 + 3;
    this->model_number = (rand()%MAX_MODEL_NUMBER) + 1;
    this->scale = ((rand()%3) + 1) + ( (rand()%10) / 10);;
}

void obstacles::render(){
  this->update();
  glPushMatrix();
    glTranslatef(this->o_position.x, this->o_position.y, this->o_position.z);
    glRotatef(this->o_rotation.x, 1.0, 0.0, 0.0);
    glRotatef(this->o_rotation.y, 0.0, 1.0, 0.0);
    glRotatef(this->o_rotation.z, 0.0, 0.0, 1.0);
    glScalef((float)(this->scale), (float)(this->scale), (float)(this->scale));
    //glutSolidCube(this->scale);
    if(this->model_number == 1){
      this->asteroid_list["asteroid_1"]->dibujar();
    }
    else{
      this->asteroid_list["asteroid_2"]->dibujar();
    }
  glPopMatrix();
}

#endif
