#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <math.h>


#include "model.h"
#include "extra_functions.h"

using namespace std;
using namespace glm;

class Enemigo{
protected:
  float m_tiempo_disparar;
  vec3 m_color;

public:
  Model*  m_modelo;
  vec3 m_direccion;

  vec3 m_posicion_inicial;
  vec3 m_velocidad;
  vec3 m_posicion;

  int vida;

  Enemigo(vec3);
  Enemigo();

  virtual ~Enemigo();

  void restart();
  void cargar(float);
  void set_position(vec3);

  virtual void dibujar(vec3, vec3, bool);
  virtual int colision(vec3, float);
  virtual void mover(vec3, vec3, vec3, float) = 0;
  virtual void disparar(vec3, float) = 0;
  virtual float get_size(float) = 0;
};


float eno_emit[] = {1.0, 1.0, 1.0, 1.0};

Enemigo::Enemigo(){}
Enemigo::Enemigo(vec3 _pos){
  this->m_posicion = _pos;
}
Enemigo::~Enemigo(){}

void Enemigo::restart(){
  //this->m_direccion = RandomVect();
}
void Enemigo::cargar(float _dt){
  this->m_tiempo_disparar += _dt;
}
void Enemigo::set_position(vec3 _pos){
  this->m_posicion = _pos;
}

void Enemigo::dibujar(vec3 _dim, vec3 _centro, bool _col){
  glPushMatrix();
    float angley = orientedAngle( vec2(this->m_direccion.x, this->m_direccion.z), vec2(this->m_modelo->m_dir.x, this->m_modelo->m_dir.z)  ) * 180 / 3.141681;
    glTranslatef(this->m_posicion.x, this->m_posicion.y, this->m_posicion.z);
    glRotatef(angley, 0.0, 1.0, 0.0);
    if(_col){
      float emit[] = {0.0, 1.0, 0.0, 1.0};
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emit);
        glColor3f(0, 1, 0);
        glutWireSphere(this->m_modelo->m_dim / 2.0, 8, 8);
      glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, eno_emit);
    }
    this->m_modelo->dibujar();
  glPopMatrix();
}
int Enemigo::colision(vec3 _pos, float _r){
  int ty = -1;
	float dis = distance(_pos, m_posicion);
	if(dis < (m_modelo->m_dim/2.0f + _r)){
		ty = 1;
		this->vida--;

		if(this->vida <= 0){
			ty = 2;
		}
	}
	return ty;
}

#endif
