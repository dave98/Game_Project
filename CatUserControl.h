#ifndef CATUSERCONTROL_H
#define  CATUSERCONTROL_H

#include <iostream>
#include "Cat3DGeometry.h"
#include "Cat3DUnit.h"

using namespace std;

class CatUserControl{
public:
  float mouse_x; //Position of mouse
  float mouse_y;
  Cat3DUnit<float> camera_position; //Posicion del ojo en el mundo -> DEBE DE SER INICIALIZADO
  Cat3DUnit<float> camera_reference; //Posicion al punto de referencia de la camara
  Cat3DUnit<float> camera_up; //Posicion de como apuntas.


  bool mouse_left_down; // Mouse left button down?
  bool mouse_right_down; // Same up

  bool parameter_0; //Draw dona
  bool parameter_1; //Axis;
  bool parameter_2; //Cuadrado
  bool parameter_3; //Cuadrado
  bool parameter_4; //Cuadrado
  bool parameter_5; //Cuadrado
  bool parameter_6; //Cuadrado
  bool parameter_7; //Cuadrado
  bool parameter_8; //Cuadrado
  bool parameter_9; //
  bool parameter_10;
  bool parameter_11;
  bool parameter_12;
  bool parameter_13; //Cuadrado
  bool parameter_14; //Cuadrado
  bool parameter_15; //Cuadrado

  int keys;
  plane_figure<float>* geometry; // Able to be used with any format
  Circle<float>* c_circle;

  CatUserControl();
  ~CatUserControl();

  char identifier(char);
  char keys_interpreter(char);
  void initial_camera_configuration(float, float, float, float, float, float, float, float, float);//NECESITA DEFINIRSE ANTES DE LA EJECUCION PRINCIPAL

};

CatUserControl::CatUserControl(){
  this->mouse_x = 0.0;
  this->mouse_y = 0.0;
  this->camera_position = Cat3DUnit<float>(); //Start everything at zero
  this->camera_reference = Cat3DUnit<float>();
  this->camera_up = Cat3DUnit<float>();
  this->mouse_left_down = false;
  this->mouse_right_down = false;
  this->keys = 0;

  this->parameter_0 = false;
  this->parameter_1 = false;
  this->parameter_2 = false;
  this->parameter_3 = false;
  this->parameter_4 = false;
  this->parameter_5 = false;
  this->parameter_6 = false;
  this->parameter_7 = false;
  this->parameter_8 = false;
  this->parameter_9 = false;
  this->parameter_10 = false;
  this->parameter_11 = false;
  this->parameter_12 = false;
  this->parameter_13 = false;
  this->parameter_14 = false;
  this->parameter_15 = true;


  this->geometry =  NULL;
  this->c_circle = NULL;
}

CatUserControl::~CatUserControl(){}

//Just works for letters
char CatUserControl::identifier(char _key){
  if((int)_key >= 97 || (int)_key <= 122){
      return this->keys_interpreter(_key);
  }
  else{
    return _key;
  }
}

char CatUserControl::keys_interpreter(char _key){
    cout<<"Entrada: "<<(char)_key<<endl;
    cout<<"Salida: "<<(char)(_key - 32)<<endl;
    return (_key - 32);
}

void CatUserControl::initial_camera_configuration(float pos_x, float pos_y, float pos_z, float ref_x, float ref_y, float ref_z, float vec_x, float vec_y, float vec_z){
  this->camera_position.x = pos_x;
  this->camera_position.y = pos_y;
  this->camera_position.z = pos_z;

  this->camera_reference.x = ref_x;
  this->camera_reference.y = ref_y;
  this->camera_reference.z = ref_z;

  this->camera_up.x = vec_x;
  this->camera_up.y = vec_y;
  this->camera_up.z = vec_z;
}

#endif
