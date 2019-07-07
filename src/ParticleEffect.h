#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Particle.h"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/compatibility.hpp>
#include "soil/SOIL.h"

#include <GL/gl.h>
#include "Camera.h"
#include "ParticleEmitter.h"
#include "Random.h"

using namespace std;

float my_max(float x, float z){
  return (x < z) ? z : x;
}

float my_min(float x, float z){
  return (x > z) ? z : x;
}


float my_clamp(float x, float y, float z){
  return( my_min(my_max(x, y), z) );
}

class ParticleEffect{
public:
    struct Vertex{
      Vertex()
              : m_Pos(0)
              , m_Diffuse(0)
              , m_Tex0(0)
      {}
        glm::vec3 m_Pos;
        glm::vec4 m_Diffuse;
        glm::vec2 m_Tex0;
    };

    typedef vector<Vertex> VertexBuffer; // Definimos un vector con  la clase Vertex
    ParticleEffect(unsigned int numParticles = 0); //DONE
    ~ParticleEffect(); //DONE

    void SetCamera(Camera*  pCamera); // DONE Permite definir la posicion de la camera haciendo que las particulas miren en esa direcccion "Billboarding"
    void SetParticleEmitter(ParticleEmitter* pEmitter); // DONE Se instancia y define la clase  que determina la velocidad y posicion de nuevas particulas.
    //INTERPOLACION 39

    void RandomizeParticles(); //DONE Modificar el comportamiento de movimiento de las particulas describiendo un comportamiento aleatorio. Se utiliza si no actua la instanciacion de  m_ParticleEmitter
    void EmitParticles(); // DONE Si se hace una instanciacion de m_pParticleEmitter entonces esta función dicta que comportamiento necesitan las particulas.

    virtual void Update( float fDeltaTime); // DONE Actualizar las constantes de posicionamiento del vector de particulas ademas de su color y su velocidad  durante cada paso de la ejecución
    virtual void Render(); //Renderiza la particula en Opengl
    void Render_v2();

    bool LoadTexture(const string& fileName); // DONE Cargar texturas
    void Resize(unsigned int numParticles); // Modifica la cantidad de particulas  relizadas durante la ejecución ya sea aumentando o disminuyendo el numero


    void RandomizeParticle(Particle& particle); // DONE Altera el movimiento de una particula en singular
    void EmitParticle(Particle& particle); //DONE

    void BuildVertexBuffer(); //DONE Loop que recorre el buffer de particulas para asociar cada particula con el vertexbuffer.

    Camera* m_pCamera;
    ParticleEmitter* m_pParticleEmitter;
    //INTERPOLACION 62

    ParticleBuffer m_Particles;
    VertexBuffer m_VertexBuffer;
    glm::mat4x4  m_LocalToWorldMatrix;
    GLuint m_TextureID; // GL Data Type

    glm::vec3 m_Force;
};


ParticleEffect::ParticleEffect(unsigned int numParticles)
  //Describiendo valores por defecto
  : m_pCamera(NULL)
  , m_pParticleEmitter(NULL)
  // INTERPOLACION 3 -10
  , m_LocalToWorldMatrix(1)
  , m_TextureID(0)
  , m_Force( 0, 0 , -9.81 )//Gravity force
  {
      this->Resize(numParticles); // Definimos la cantidad de particulas con el constructor
}


ParticleEffect::~ParticleEffect(){
  if(m_TextureID != 0){
    glDeleteTextures(1, &m_TextureID);
    m_TextureID = 0;
  }
}

void ParticleEffect::SetCamera(Camera* pCamera){
  this->m_pCamera = pCamera;
}

void ParticleEffect::SetParticleEmitter(ParticleEmitter* pEmitter){
    this->m_pParticleEmitter = pEmitter;
}


bool ParticleEffect::LoadTexture(const string& fileName){
  if(this->m_TextureID != 0){
    glDeleteTextures(1, &m_TextureID);
  }

  m_TextureID = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

  return (m_TextureID != 0);
}
//INTERPOLACION 3 - 37

void ParticleEffect::RandomizeParticles(){
  for(unsigned int i = 0; i < this->m_Particles.size(); i++){
    this->RandomizeParticle(this->m_Particles[i]);
  }
}

void ParticleEffect::RandomizeParticle(Particle& particle){
  particle.m_fAge = 0.0f;
  particle.m_fLifeTime = RandRange(3, 5);

  glm::vec3 unitVec = RandUnitVec();
  particle.m_Position = unitVec * 1.0f;
  particle.m_Velocity = unitVec * RandRange(10, 20);
}

void ParticleEffect::EmitParticles(){
  if(this->m_pParticleEmitter == NULL){
    RandomizeParticles();
  }
  else{
    for(unsigned int i = 0; i < this->m_Particles.size(); i++){
      this->EmitParticle(this->m_Particles[i]);
    }
  }
}

void ParticleEffect::EmitParticle(Particle& particle){
  if(this->m_pParticleEmitter != NULL){
    this->m_pParticleEmitter->EmitParticle(particle);
  }
  else{
    cout<<"No se ha implementado un Emisor de Particulas"<<endl;
  }
}

void ParticleEffect::Update(float fDeltaTime){
  for(unsigned int i = 0; i < this->m_Particles.size(); i++){
    Particle& particle = this->m_Particles[i];

    particle.m_fAge += fDeltaTime;
    if(particle.m_fAge > particle.m_fLifeTime){
      if(this->m_pParticleEmitter != NULL){
        EmitParticle(particle);
      }
      else{
        RandomizeParticle(particle);
      }
    }

    //float lifeRatio = glm::saturate(particle.m_fAge / particle.m_fLifeTime);
    //float lifeRatio = glm::clamp( (particle.m_fAge / particle.m_fLifeTime), 0, 1);
    float lifeRatio = my_clamp(particle.m_fAge / particle.m_fLifeTime, 0.0, 1.0);
    particle.m_Velocity += (m_Force * fDeltaTime);
    particle.m_Position += (particle.m_Velocity * fDeltaTime);
    //INTERPOLACION
    //particle.m_fRotate = glm::lerp<float>(0.0f, 720.0f, lifeRatio);
    //particle.m_fSize = glm::lerp<float>(5.0f, 0.0f, lifeRatio);
  }
  //Bu1ildVertexBuffer();
}

void ParticleEffect::BuildVertexBuffer(){
  const glm::vec3 X(0.5, 0.0, 0.0);
  const glm::vec3 Y(0.0, 0.5, 0.0);
  const glm::vec3 Z(0.0, 0.0, 1.0);

  glm::quat cameraRotation;
  if(this->m_pCamera != NULL){
    cameraRotation = glm::quat(glm::radians(this->m_pCamera->GetRotation()));
  }
  m_VertexBuffer.resize(this->m_Particles.size() * 4, Vertex());

  for ( unsigned int i = 0; i < m_Particles.size(); ++i )
  {
      Particle& particle = m_Particles[i];
      glm::quat rotation = glm::angleAxis( particle.m_fRotate, Z );

      unsigned int vertexIndex = i * 4;
      Vertex& v0 = m_VertexBuffer[vertexIndex + 0];   // Bottom-left
      Vertex& v1 = m_VertexBuffer[vertexIndex + 1];   // Bottom-right
      Vertex& v2 = m_VertexBuffer[vertexIndex + 2];   // Top-right
      Vertex& v3 = m_VertexBuffer[vertexIndex + 3];   // Top-left

      // Bottom-left
      v0.m_Pos = particle.m_Position + ( rotation * ( -X - Y ) * particle.m_fSize ) * cameraRotation;
      v0.m_Tex0 = glm::vec2( 0, 1 );
      v0.m_Diffuse = glm::vec4(0);

      // Bottom-right
      v1.m_Pos = particle.m_Position + ( rotation * ( X - Y ) * particle.m_fSize ) * cameraRotation;
      v1.m_Tex0 = glm::vec2( 1, 1 );
      v1.m_Diffuse = glm::vec4(0);

      // Top-right
      v2.m_Pos = particle.m_Position + ( rotation * ( X + Y ) * particle.m_fSize ) * cameraRotation;
      v2.m_Tex0 = glm::vec2( 1, 0 );
      v2.m_Diffuse = glm::vec4(0);

      // Top-left
      v3.m_Pos = particle.m_Position + ( rotation * ( -X + Y ) * particle.m_fSize ) * cameraRotation;
      v3.m_Tex0 = glm::vec2( 0, 0 );
      v3.m_Diffuse = glm::vec4(0);
  }

}

void ParticleEffect::Resize( unsigned int numParticles ){
    m_Particles.resize( numParticles,  Particle() );
    m_VertexBuffer.resize( numParticles * 4, Vertex() );
}

void ParticleEffect::Render_v2(){
  for(unsigned int i; i < m_Particles.size(); i++){
    glBegin(GL_POINTS);
      glVertex3f(m_Particles[i].m_Position.x, m_Particles[i].m_Position.y, m_Particles[i].m_Position.z);
    glEnd();
  }
  return;
}

void ParticleEffect::Render(){
  glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

  glDepthMask( GL_FALSE );            // Disable depth writes
  glEnable(GL_BLEND);                 // Enable Blending
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );   // Type Of Blending To Perform
  glEnable(GL_TEXTURE_2D);            // Enable textures

  glPushMatrix();
  glMultMatrixf( glm::value_ptr(m_LocalToWorldMatrix) );

  glBindTexture( GL_TEXTURE_2D, m_TextureID );

  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );
  glEnableClientState( GL_COLOR_ARRAY );

  glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Pos) );
  glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Tex0) );
  glColorPointer( 4, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Diffuse) );

  glDrawArrays( GL_QUADS, 0, m_VertexBuffer.size() );

  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
  glDisableClientState( GL_COLOR_ARRAY );

  glBindTexture( GL_TEXTURE_2D, 0 );

  glPopAttrib();

  if ( m_pParticleEmitter != NULL )
  {
      m_pParticleEmitter->DebugRender();
  }

  glPopMatrix();

}

#endif
