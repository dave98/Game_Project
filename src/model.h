#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "TextureManager.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <GL/glut.h>
#include <GL/glext.h>

using namespace std;
using namespace glm;

class Model{
public:
  //Data en torno al modelo 3d y texturas
  int m_type;
  int m_texture;

  vector<vec3> m_vertice;
  vector<vec2> m_uv;
  vector<vec3> m_normal;

  vector<unsigned> m_vertice_idx;
  vector<unsigned> m_uv_idx;
  vector<unsigned> m_normal_idx;

  //Despliegue del modelo
  vec3 m_dir;
  float m_dim;
  Model(int, string, string, int, int);
  Model();
  ~Model();

  void dibujar();
  Model get_small();
};


Model::Model(){
}

Model::~Model(){}

Model::Model(int _type, string filename, string textures, int _BGR_EXT, int _RGB){
  ifstream file(filename);

  this->m_texture = TextureManager::Inst()->LoadTexture(textures.c_str(), _BGR_EXT, _RGB);
  if(file.bad()){cout<<"No puede abrirse el archivo del modelo"<<endl; return;}

  this->m_type = _type;
  string cabezera;
  string svertice;

  vec3 gvertice;
  vec2 guv;
  vec3 gnorma;

  unsigned i;
  unsigned iv;
  unsigned iuv;
  unsigned inorma;

  float tmin[3] = {9999, 9999, 9999};
  float tmax[3] = {-9999, -9999, -9999};

  while(true){
    file >> cabezera;

    if(file.eof()){ break; }

    if(cabezera == "v"){
      file >> gvertice.x >> gvertice.y >> gvertice.z;
      this->m_vertice.push_back(gvertice);
      for(int i = 0; i < 3; i++){
        if(gvertice[i] < tmin[i]){
          tmin[i] = gvertice[i];
        }
        if(gvertice[i] > tmax[i]){
          tmax[i] = gvertice[i];
        }
      }
    }
    else if(cabezera == "vt"){
      file >> guv.x >> guv.y;
      this->m_uv.push_back(guv);
    }
    else if(cabezera == "vn"){
      file >> gnorma.x >> gnorma.y >> gnorma.z;
      this->m_normal.push_back(gnorma);
    }
    else if(cabezera == "f"){
      for(int i = 0; i < this->m_type; i++){
        file >> svertice;

        sscanf(svertice.c_str(), "%d/%d/%d", &iv, &iuv, &inorma);
        m_vertice_idx.push_back(iv - 1);
        m_uv_idx.push_back(iuv - 1);
        m_normal_idx.push_back(inorma - 1);
      }
    }
  }

  for(unsigned int i = 0; i < m_vertice.size(); i++){
    m_vertice[i].y -= (tmin[1] + (tmax[1] - tmin[1])/ 2.0f);
  }

  this->m_dim = 0.0f;
  for(i = 0; i < 3; i++){
    m_dim += (tmax[i] - tmin[i]);
  }

  this->m_dim = (float)m_dim / 3;
  this->m_dir = vec3(0, 0, 1);
}


void Model::dibujar(){
  vec3 tvertice;
  vec3 tnormal;
  vec2 ttextures;

  glBindTexture(GL_TEXTURE_2D, this->m_texture);

  if(this->m_type == 3) glBegin(GL_TRIANGLES);
  if(this->m_type == 4) glBegin(GL_QUADS);

  for(unsigned int i = 0; i < this->m_vertice_idx.size(); i++){
    tvertice = m_vertice[m_vertice_idx[i]];
    tnormal  = m_normal[m_normal_idx[i]];
    ttextures = m_uv[m_uv_idx[i]];

    glTexCoord2f(ttextures.x, ttextures.y);
    glNormal3f(tnormal.x, tnormal.y, tnormal.z);
    glVertex3f(tvertice.x, tvertice.y, tvertice.z);
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
}

Model Model::get_small(){
  Model tmp = *this;
  tmp.m_dim = m_dim*0.75f;
  for(unsigned i=0; i<tmp.m_vertice.size(); i++){
    tmp.m_vertice[i] *= 0.75f;;
  }
  return tmp;
}

#endif
