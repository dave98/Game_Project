#ifndef ENE_1_H
#define ENE_1_H

#include <iostream>
#include "model.h"
#include "enemy.h"
#include "extra_functions.h"

using namespace std;
using namespace glm;


class Enemy_1 : public Enemigo{
public:
  Enemy_1();
  Enemy_1(vec3, Model*);
  ~Enemy_1(){};

  void mover(vec3, vec3, vec3, float);
  void dibujar(vec3, vec3, bool);
  void disparar(vec3, float);
  float get_size(float);
};

 float rcol = 40;

 Enemy_1::Enemy_1(vec3 _pos, Model* _model) : Enemigo(_pos){
   this->vida = 10;
   this->m_direccion = 10.0f * RandomVect();
   this->m_modelo = _model;
   this->m_tiempo_disparar = 0.0;
   this->m_posicion += (this->m_modelo->m_dim / 2);

   this->m_color = vec3(1.0f, 0.0f, 1.0f);
 }

 void Enemy_1::mover(vec3 _jug, vec3 _dim, vec3 _centro, float dt){
   this->m_direccion = normalize((_jug - vec3(this->m_posicion.x, _jug.y, m_posicion.z)));
   vec3 _pos = m_posicion + (m_direccion * dt * 3.0f);
   //Realizando movimiento
   this->m_posicion = _pos;
 }


 void Enemy_1::dibujar(vec3 _dim, vec3 _centro, bool _col){
   glPushMatrix();
    glTranslatef(this->m_posicion.x, this->m_posicion.y - 2.0, this->m_posicion.z);
    if(_col){
      float emit[] = {0.0, 0.0, 1.0, 1.0};
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
      glColor3f(0, 0, 1);
    }
   glPopMatrix();
   Enemigo::dibujar(_dim, _centro, _col);
 }

void Enemy_1::disparar(vec3 _pos, float _dt){
  cout<<"Disparando el enemigo1"<<endl;
}


float Enemy_1::get_size(float _size){
  return (_size/ (float)10) * this->vida;
}


#endif
