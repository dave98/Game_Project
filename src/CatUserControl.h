#ifndef CATUSERCONTROL_H
#define  CATUSERCONTROL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <map>

#include "Ship.h"
#include "Obstacles.h"
#include "enemy.h"
#include "ene_1.h"


using namespace std;

//Some global varibles for this document (AND ONLY THIS DOCUMENT)
float MOUSE_ANGLE = 15.0; //Angulo limite hasta donde puede girar la nave (impide que se voltee completamente)
float MOUSE_SENSIBILITY = 0.05; //Recepción del mouse frente a los movimientos
float MOUSE_RELATION = 0.2; //Ni idea de para que sirve pero util

int NUMERO_METEORITOS = 15;
int NUMERO_ENEMIES_1 = 1;

class CatUserControl{
public:
  //Extra implementation
  glm::mat4 matRoll;  // Gira en torno al eje z
  glm::mat4 matPitch; // Gira en torno al eje x , lado de las orejas en la imagen
  glm::mat4 matYaw; // Gira en torno al eje y, frente
  glm::mat4 resultant_rotate; //Resultante final
  glm::vec3 eyesPos;


  glm::vec3 cam_position;
  glm::vec3 cam_reference;
  glm::vec3 cam_normal;
  glm::vec3 cam_direction; // Define el vector que relaciona la posicion de la camara con su punto de vista
  glm::vec2 mouse_pos;
    float mouse_max_angle;
    float mouse_sensibility;
    float mouse_relation;

  vector<bool> all_keys;
  my_ship* player_ship;
  vector<obstacles* > game_obstacles;


//Enemy description
  map<string, Model*> enemies_list;
//Enemy types:
  vector<Enemy_1* > enemy_1_list;



  CatUserControl();
  ~CatUserControl();

  void initial_camera_configuration(glm::vec3, glm::vec3, glm::vec3);
  void set_direction();

  void set_new_ship();
  void global_rendering();
    void global_enemy_rendering();

  void mouse_interpreter(int, int); //Traduce todos los movimientos detectados en SleepingCatEngine
  void key_interpreter_normal_pressed(int); //Recibe la tecla que se ha presionado y la mantiene en true mientras dure presionada
  void key_interpreter_normal_up(int); //Pone en false la tecla indicada si se suelta
  void key_interpreter_special_pressed(int); //Igual que key_interpreter_normal_pressed pero trabaja con las direccionales
  void key_interpreter_special_up(int); //Igual a key_interpreter_normal_up pero con las direccionales
  void key_effect_operation(); //Analiza las teclas descritas previamente, y si están en verdadero ejecutan la operacion asociada a ellas
};

CatUserControl::CatUserControl(){
  this->cam_position = glm::vec3(0);
  this->cam_reference = glm::vec3(0);
  this->cam_normal = glm::vec3(0);
  this->mouse_pos = glm::vec2(0);
    this->mouse_max_angle = MOUSE_ANGLE;
    this->mouse_sensibility = MOUSE_SENSIBILITY;
    this->mouse_relation = MOUSE_RELATION;
  this->all_keys = vector<bool>(256, false); //Todas las tecals al inicio están desactivadas

  this->matRoll = glm::mat4(1.0f);  // Gira en torno al eje z
  this->matPitch = glm::mat4(1.0f); // Gira en torno al eje x , lado de las orejas en la imagen
  this->matYaw = glm::mat4(1.0f); // Gira en torno al eje y, frente
  this->resultant_rotate = glm::mat4(1.0f); //Resultante final
  this->eyesPos = glm::vec3(0);

//  LAST ATRIBUTTION
  this->player_ship = NULL;
  this->game_obstacles = vector<obstacles*>(NUMERO_METEORITOS, NULL);
    for(unsigned int i = 0; i < game_obstacles.size(); i++){
      game_obstacles[i] = new obstacles(1, 100);
    }

//Inicializando modelos
  this->enemies_list["enemy_1"] = new Model(4, "data/enemy_ship.obj", "data/enemy_ship.tga", GL_BGR_EXT, GL_RGB);
  //this->enemies_list["raptor"] = new Model(4, "data/raptor.obj", "data/raptor.png", GL_BGR_EXT, GL_RGB);
  this->enemies_list["player_ship"] = new Model(4, "data/Sample_Ship.obj", "data/sh3.jpg", GL_BGR_EXT, GL_RGB);
//Setting Up Enemies
  Enemy_1* temp_enemy = new Enemy_1( vec3(-50, 0, 5), this->enemies_list["enemy_1"]); //Postion model

  this->enemy_1_list.push_back(temp_enemy);

}


CatUserControl::~CatUserControl(){}

void CatUserControl::initial_camera_configuration(glm::vec3 _pos, glm::vec3 _ref, glm::vec3 _norm){
  this->cam_position = _pos;
  this->cam_reference = _ref;
  this->cam_normal = _norm;
}

void CatUserControl::set_new_ship(){
  this->player_ship = new my_ship; //Creando la nave del jugador

  this->player_ship->set_ship_position(glm::vec3(-20, 0, 0)); //Posicion  de la nave durante la primera iteraccion
  this->player_ship->set_ship_direction(glm::vec3(0, 0, 0)); //Direccion de la nave durante la primera iteraccion, lo que se envia es el punto a donde apuntaremos inicialmente
}

void CatUserControl::global_enemy_rendering(){
  for(unsigned int i = 0; i < this->enemy_1_list.size(); i++){
    this->enemy_1_list[i]->dibujar(vec3(0, 0, 0), vec3(0, 0, 0), false);
  }
}

void CatUserControl::global_rendering(){ //Funcion que permite renderizar todos los objetos de la pantalla
  //cout<<"Player position: "<<this->player_ship->s_position.x<<", "<<this->player_ship->s_position.y<<", "<<this->player_ship->s_position.z<<endl;

  this->player_ship->render_ship();
  for(unsigned int i = 0; i < this->game_obstacles.size(); i++){
    this->game_obstacles[i]->render();
  }
  //this->global_enemy_rendering();
  return;
}



void CatUserControl::mouse_interpreter(int _x, int _y){
  float x_diference = fabs(this->mouse_pos.x - _x); //fbas develve el valor absoluto de un flotante (Lo vuelve positivo)
  float y_diference = fabs(this->mouse_pos.y - _y);

  if(this->mouse_pos.x < _x){ //Se ha movido a la derecha
    if(this->player_ship->s_rotation.z < this->mouse_max_angle){
      this->player_ship->s_rotation.z += (x_diference*this->mouse_sensibility);
      this->player_ship->s_direction.y -= (x_diference*this->mouse_sensibility*this->mouse_relation);
    }
  }
  else if(this->mouse_pos.x > _x){ //Se ha movido a la izquierda
    if(this->player_ship->s_rotation.z > -this->mouse_max_angle){
      this->player_ship->s_rotation.z -= (x_diference*this->mouse_sensibility);
      this->player_ship->s_direction.y += (x_diference*this->mouse_sensibility*this->mouse_relation);
    }
  }

  if(this->mouse_pos.y < _y){ //Se ha movido a abajo
    if(this->player_ship->s_rotation.y < this->mouse_max_angle){
      this->player_ship->s_rotation.y += (y_diference*this->mouse_sensibility);
      this->player_ship->s_direction.z -= (y_diference*this->mouse_sensibility*this->mouse_relation);
    }
  }
  else if(this->mouse_pos.y > _y){ //Se ha movido para arriba
    if(this->player_ship->s_rotation.y > -this->mouse_max_angle){
      this->player_ship->s_rotation.y -= (y_diference*this->mouse_sensibility);
      this->player_ship->s_direction.z += (y_diference*this->mouse_sensibility*this->mouse_relation);
    }
  }

  this->mouse_pos.x = _x;
  this->mouse_pos.y = _y;
  return;

}

void CatUserControl::key_interpreter_normal_pressed(int key){ //Recibe la tecla que se ha presionado y la mantiene en true mientras dure presionada
  this->all_keys[key] = true;
}

void CatUserControl::key_interpreter_normal_up(int key){ //Pone en false la tecla indicada si se suelta
  this->all_keys[key] = false;
}

void CatUserControl::key_interpreter_special_pressed(int key){ //Igual que key_interpreter_normal_pressed pero trabaja con las direccionales
  switch (key) {
    case GLUT_KEY_UP:
      this->all_keys[(int)'w'] = true;
      break;
    case GLUT_KEY_DOWN:
      this->all_keys[(int)'s'] = true;
      break;
    case GLUT_KEY_LEFT:
      this->all_keys[(int)'a'] = true;
      break;
    case GLUT_KEY_RIGHT:
      this->all_keys[(int)'d'] = true;
      break;
  }
}

void CatUserControl::key_interpreter_special_up(int key){ //Igual a key_interpreter_normal_up pero con las direccionales
  switch (key) {
    case GLUT_KEY_UP:
      this->all_keys[(int)'w'] = false;
      break;
    case GLUT_KEY_DOWN:
      this->all_keys[(int)'s'] = false;
      break;
    case GLUT_KEY_LEFT:
      this->all_keys[(int)'a'] = false;
      break;
    case GLUT_KEY_RIGHT:
      this->all_keys[(int)'d'] = false;
      break;
  }
}

void CatUserControl::key_effect_operation(){
    if(this->all_keys[(int)'w']){
      this->player_ship->ship_movement_up();
    }

    if(this->all_keys[(int)'s']){
      this->player_ship->ship_movement_down();
    }

    if(this->all_keys[(int)'a']){
      this->player_ship->ship_movement_left();
    }

    if(this->all_keys[(int)'d']){
      this->player_ship->ship_movemente_right();
    }

}



#endif
