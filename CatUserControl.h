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
  float camera_x; // Position of my camera
  float camera_y;
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

  int keys;
  plane_figure<float>* geometry; // Able to be used with any format
  Circle<float>* c_circle;

  CatUserControl();
  ~CatUserControl();

  char identifier(char);
  char keys_interpreter(char);

};

CatUserControl::CatUserControl(){
  this->mouse_x = 0.0;
  this->mouse_y = 0.0;
  this->camera_x = 0.0;
  this->camera_y = 0.0;
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
#endif
